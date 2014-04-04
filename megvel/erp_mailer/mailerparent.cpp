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
				} else if (queue_type == "Requisition") {
					sent = sendRequisition(fk);
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
	QString qty = ocQuery.record().value("qty").toString();
	QString tons = ocQuery.record().value("tons").toString();

	QStringList recpients;
	recpients << "Joseph W Joshua <joshua@megvel.me.ke>";

	QString msg =  "<h3>New Order Generated (" + ocNo + ")</h3><br/>"
			"<b>Customer Name</b>: " + customerName +
			"<br/>" +
			"<b>Product Name</b>: " + productName +
			"<br/>"
			"<b>Qty</b>: " + qty + "(" + tons + ") tons";
	QString subject = "New OC: " + ocNo + ". Customer: " + customerName;
	return sendEmail(subject, msg, recpients);
}

bool MailerParent::sendRequisition(QString rqnNo)
{
	qDebug() << "Unsent requisition (" + rqnNo + ")...fetching requisition details.";
	QSqlQuery master =
			db.exec(" SELECT "
				" store_requisition_master.EntryID AS 'RqnNo'"
				", store_requisition_master.RequisitionDate "
				", store_requisition_master.DateRequired "
				", store_requisition_master.RequestedBy "
				", store_requisition_master.Department "
				", suppliers.SupplierName "
				"FROM "
				" cartons.suppliers "
				" INNER JOIN cartons.store_requisition_master  "
				" ON (suppliers.SupplierID = store_requisition_master.SupplierID) WHERE store_requisition_master.EntryID = '" + rqnNo + "'");
	if (!master.lastError().isValid()) {
		//No error on master
		master.first();
		QString supplierName = master.record().value("SupplierName").toString();
		QString reqnDate = QDate::fromString(master.record().value("RequisitionDate").toString(), "yyyy-Mm-dd").toString("dd-MMM-yy");
		QString dateRequired = QDate::fromString(master.record().value("DateRequired").toString(), "yyyy-Mm-dd").toString("dd-MMM-yy");
		QString requestedBy = master.record().value("RequestedBy").toString() + "("
				+ master.record().value("Department").toString() + ")";

		QString headerHtml = "<a href='http://www.megvel.me.ke/stores/requisition.php?id="  + rqnNo +  "'><h3>Approve Requisition</h3></a>"
				"<br/><b>Requested By: </b> " + requestedBy
				+ "<br/><b>Supplier: </b> " + supplierName
				+ "<br/><b>Requisition Date: </b> " + reqnDate
				+ "<br/><b>Date Required: </b> " + dateRequired
				;

		QString detailHtml = "<h3>Requisition Detail</h3><br/>"
				"<table width=100% border=1 cellspacing=1 cellpadding=1>"
				"<tr>"
				"<td><b>Item Name</b></td>"
				"<td><b>Qty</b></td>"
				"<td><b>Unit Price</b></td>"
				"<td><b>Sub Total</b></td>"
				"<td><b>VAT</b></td>"
				"<td><b>Total</b></td>"
				"</tr>"
				;
		QSqlQuery detail = db.exec(""
					   " SELECT "
					   "    store_requisition_detail.ItemName"
					   "    , store_requisition_detail.Qty"
					   "    , store_requisition_detail.UnitPrice"
					   "    , store_requisition_detail.Total"
					   "    , store_requisition_detail.VAT"
					   "   , store_requisition_detail.SubTotal"
					   "  FROM"
					   "    cartons.inventory"
					   "    INNER JOIN cartons.store_requisition_detail "
					   "       ON (inventory.ItemID = store_requisition_detail.ItemID)"
					   "       "
					   "      WHERE store_requisition_detail.MasterID = '" + rqnNo  + "'"
					   );
		QLocale loc(QLocale::English, QLocale::Kenya);
		double total_qty = 0;
		double total_total = 0;
		double total_vat = 0;
		double total_subtotal = 0;
		if (!detail.lastError().isValid()) {
			while (detail.next()) {
				QString itemName = detail.record().value("ItemName").toString();
				double qty  =detail.record().value("Qty").toDouble();
				double unit_price = detail.record().value("UnitPrice").toDouble();
				double sub_total = detail.record().value("Total").toDouble();
				double vat = detail.record().value("VAT").toDouble();
				double total = detail.record().value("SubTotal").toDouble();

				total_qty += qty;
				total_total += total;
				total_vat += vat;
				total_subtotal += sub_total;

				QString html = "<tr>";

				html += "<td>" + itemName + "</td>";

				html += "<td>" + QString::number(qty) + "</td>";
				html += "<td>" + loc.toCurrencyString(unit_price) + "</td>";
				html += "<td>" + loc.toCurrencyString(sub_total) + "</td>";
				html += "<td>" + loc.toCurrencyString(vat) + "</td>";
				html += "<td>" + loc.toCurrencyString(total) + "</td>";

				html += "</tr>";

				detailHtml += html;
			}
			QString totals_html = "<tr>";

			totals_html += "<td><b>Totals:</b></td>";

			totals_html += "<td><b>" + QString::number(total_qty) + "</b></td>";
			totals_html += "<td>-</td>";
			totals_html += "<td><b>" + loc.toCurrencyString(total_total) + "</b></td>";
			totals_html += "<td><b>" + loc.toCurrencyString(total_vat) + "</b></td>";
			totals_html += "<td><b>" + loc.toCurrencyString(total_subtotal) + "</b></td>";

			totals_html += "</tr>";
			detailHtml += totals_html;
		} else {
			qDebug() << "Requisition detail error: " + detail.lastError().text();
		}
		detailHtml += "</table></br>";

		QStringList recpients;
		recpients << "Joseph W Joshua <joshua@megvel.me.ke>";
		QString html = headerHtml + "<br/><br/>" + detailHtml;
		QString subject = "Requisition " + rqnNo + " (" + supplierName + ")";
		sendEmail(subject, html, recpients);
	} else {
		qDebug() << "Requisition master error: " + master.lastError().text();
	}
	return false;
}

bool MailerParent::sendEmail(QString subject, QString messageText, QStringList recepients, QStringList attachments)
{
	qDebug() << "Starting email sender...";
	QString host = "192.168.0.246";
	int  port = 25;
	bool ssl = false;
	EmailAddress *sender = new EmailAddress("erp@megvel.me.ke", "Megvel Cartons Ltd ERP");

	SmtpClient smtp (host, port, ssl ? SmtpClient::SslConnection : SmtpClient::TcpConnection);
	//	smtp.setAuthMethod(SmtpClient::AuthPlain);
	//	smtp.setUser("primaxof");
	//	smtp.setPassword("Kg674vSck1");
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
		qDebug() << QString("Unable to connect to the mail server at %1").arg(host);
		//emit failed();
		smtp.quit();
		return false;
	}

	if (!smtp.sendMail(message)) {
		//errorMessage = "Sendmail failed.";
		qDebug() << "An error occurrent while sending the email " + smtp.getResponseText();
		//emit failed();
		smtp.quit();
		return false;
	} else {
		//Email sent
		//emit messageStatus("Message successfully sent");
		qDebug() << "Email sent (" + subject + ")";
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
