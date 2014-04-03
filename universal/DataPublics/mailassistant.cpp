#include "mailassistant.h"
#include "smtpclient/smtpclient.h"
#include "datapublics.h"
#include "smtpclient/SmtpMime"
MailAssistant::MailAssistant(QObject *parent) :
	QThread(parent)
{
}

void MailAssistant::run()
{
	QString host = "smtpout.accesskenya.com";//DataPublics::getIniSetting("smtpHostName");
	int port = 587;//DataPublics::getIniSetting("smtpPort").toInt();
	bool ssl = false;
	//    if (DataPublics::getIniSetting("smtpSSL") == "true")
	//        ssl = true;
	//bool auth =false;

	//    if (DataPublics::getIniSetting("smtpAuth") == "true")
	//        auth = true;

	//   QString user = DataPublics::getIniSetting("smtpUsername");
	//   QString password = DataPublics::getIniSetting("smtpPassword");


	EmailAddress *sender = DataPublics::stringToEmail(fromEmail);

	SmtpClient smtp (host, port, ssl ? SmtpClient::SslConnection : SmtpClient::TcpConnection);
	MimeMessage message;

	message.setSender(sender);
	message.setSubject(subject);

	for (int i = 0; i < recepients.size(); ++i)
		message.addRecipient(DataPublics::stringToEmail(recepients.at(i)));

	MimeHtml content;
	content.setHtml(messageBody);

	message.addPart(&content);

	for (int i = 0; i < attachments.count(); ++i) {
		message.addPart(new MimeAttachment(new QFile(attachments.at(i))));
	}

	if (!smtp.connectToHost()) {
		errorMessage = "SMTP error";
		emit errorOccurred(tr("Unable to connect to the mail server at %1 .").arg(host));
		return;
	}

	//    if (auth) {
	//        if (!smtp.login(user, password)) {
	//            errorMessage = "Authentication failed";
	//            emit errorOccurred("Mail server authentication failed. Check your user name and password.");
	//            return;
	//        }
	//    }

	if (!smtp.sendMail(message)) {
		errorMessage = "Sendmail failed.";
		emit errorOccurred("An error occurrent while sending the email " + smtp.getResponseText());
		return;
	} else {
		//Email sent
		emit messageStatus("Message successfully sent");
	}

	smtp.quit();
}

void MailAssistant::setVars(QString Subject, QString Message, QStringList Recepients, QStringList Attachments, QString From)
{
	subject = Subject;
	messageBody = Message;
	recepients = Recepients;
	attachments = Attachments;
	fromEmail = From;
}
