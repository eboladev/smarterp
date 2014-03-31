#include "mailerparent.h"
#include "QDebug"
#include "smtpclient/smtpclient.h"
#include "smtpclient/SmtpMime"
MailerParent::MailerParent(QObject *parent) :
	QObject(parent)
{
	table_name = "test_emails";
}

void MailerParent::startParent()
{
	count = 0;
	startTime = QDateTime::currentDateTime();
	openDatabase();
	QTimer *tmr = new QTimer(this);
	connect (tmr, SIGNAL(timeout()), SLOT(onTimer()));
	tmr->start(2000);
}

void MailerParent::onTimer()
{
	count ++;
	if (QString::number(count).right(1) == "0") {
		qDebug() << "Running since " << startTime.toString("dd-MMM hh:mm:ss")
			 << " for a total of " << startTime.secsTo(QDateTime::currentDateTime()) / 60
			 << " minutes";
	}
	if (db.isOpen()) {
		qDebug() << "Checking for unsent emails: ";
		QSqlQuery cntQu = db.exec("SELECT Count(`EntryID`) as 'cnt' FROM `" + table_name +"` WHERE status = 'Pending'");
		if (!cntQu.lastError().isValid()) {
			cntQu.first();
			int cnt = cntQu.record().value("cnt").toInt();
			if (cnt > 0)
				qDebug() << "======Found " + QString::number(cnt) + " unsent emails.==========";
		}
		QSqlQuery qu = db.exec("SELECT * FROM `" + table_name +"` WHERE status = 'Pending'");
		if (qu.lastError().isValid()) {
			qWarning() << "Database query error: " << qu.lastError().text();
		} else {
			//Query OK
			while (qu.next()) {
				QString queue_type = qu.record().value("QueueType").toString();
				QString fk = qu.record().value("FK").toString();
				QString id = qu.record().value("EntryID").toString();

				bool sent = false;

				if (queue_type == "OC") {
					sent = sendOc(fk);
				}

				if (sent) {
					db.exec("UPDATE " + table_name + " SET Status = 'Sent' WHERE EntryID = '" + id + "'");
				} else {
					qDebug() << "Email failed to send";
				}
			}
		}
	} else {
		qWarning() << "Database not open. Starting new connection...";
		openDatabase();
	}
}

void MailerParent::openDatabase()
{
	db = QSqlDatabase::addDatabase("QMYSQL", "mailerConnection");
	db.setHostName("192.168.0.8");
	db.setUserName("root");
	db.setPassword("pledge");
	db.setDatabaseName("cartons");
	if (db.open()) {
		qDebug() << "Database successfully open";
	} else {
		qWarning() << "Database connection failed:\n\n" << db.lastError().text();
	}
}


bool MailerParent::sendOc(QString ocNo)
{
	QSqlQuery ocQuery = db.exec("SELECT * FROM newreport WHERE TicketNo = '" + ocNo + "'");
	if (ocQuery.lastError().isValid())
		return false;

	ocQuery.first();

	QString customerName = ocQuery.record().value("Client").toString();
	QString productName = ocQuery.record().value("Product").toString();

	QStringList recpients;
	recpients << "Joseph W Joshua <joshua@megvel.me.ke>";

	QString msg = customerName + "\n" + productName;
	QString subject = "New OC: " + ocNo + ". Customer: " + customerName;
	return sendEmail(subject, msg, recpients);
}

bool MailerParent::sendEmail(QString subject, QString messageText, QStringList recepients, QStringList attachments)
{
	qDebug() << "Starting email sender...";
	QString host = "192.168.0.246";
	int port = 25;
	bool ssl = false;
	EmailAddress *sender = new EmailAddress("erp@megvel.me.ke", "Megvel Cartons Ltd ERP");

	SmtpClient smtp (host, port, ssl ? SmtpClient::SslConnection : SmtpClient::TcpConnection);
	MimeMessage message;

	message.setSender(sender);
	message.setSubject(subject);

	for (int i = 0; i < recepients.size(); ++i)
		message.addRecipient(getEmailFromString(recepients.at(i)));

	MimeHtml content;
	content.setHtml(messageText);

	message.addPart(&content);

	for (int i = 0; i < attachments.count(); ++i) {
		message.addPart(new MimeAttachment(new QFile(attachments.at(i))));
	}

	if (!smtp.connectToHost()) {
		//errorMessage = "SMTP error";
		//emit errorOccurred(tr("Unable to connect to the mail server at %1 .").arg(host));
		//emit failed();
		smtp.quit();
		return false;
	}

	if (!smtp.sendMail(message)) {
		//errorMessage = "Sendmail failed.";
		//emit errorOccurred("An error occurrent while sending the email " + smtp.getResponseText());
		//emit failed();
		smtp.quit();
		return false;
	} else {
		//Email sent
		//emit messageStatus("Message successfully sent");
		smtp.quit();
		return true;
	}

	smtp.quit();
	return false;
}

EmailAddress *MailerParent::getEmailFromString(QString email)
{
	EmailAddress *address;
	if (email.contains("<") && email.contains(">")) {
		QStringList lst = email.split("<");
		QString name = lst.at(0);
		QString email_address = lst.at(1).left(lst.at(1).length() - 1);
		address = new EmailAddress(email_address, name);
	} else {
		address = new EmailAddress(email, email);
	}
	return address;
}
