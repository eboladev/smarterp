#include "userlogin.h"
#include "ui_userlogin.h"
#include "mailassistant.h"
UserLogin::UserLogin(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::UserLogin)
{
	ui->setupUi(this);
	db = database;
	if (!db.isOpen()) {
		db.open();
	}
}

UserLogin::~UserLogin()
{
	delete ui;
}

void UserLogin::on_cmdLogin_clicked()
{

	QSqlQuery qu = db.exec(tr("SELECT * FROM `cartons`.`users` WHERE `UserName` = '%1' AND `Password` = '%2'")
			       .arg(ui->txtUserName->text(), ui->txtPassword->text()));
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}
	if (qu.first()) {
		//qu.first();
		//Login OK
		userID = qu.record().value("UserID").toString();
		userName = qu.record().value("userName").toString();
		QString tmpFileName = qApp->applicationDirPath() + QDir::separator() + "~tmpcurrentuser.dat";
		QFile fil(tmpFileName);
		if (fil.exists())
			fil.remove();

		if (fil.open(QIODevice::ReadWrite)) {
			fil.write(qu.record().value("UserID").toString().toUtf8());
			fil.close();
		}

		MailAssistant *ma = new MailAssistant(this);
		connect (ma, SIGNAL(errorOccurred(QString)), SLOT(smtpError(QString)));
		connect (ma, SIGNAL(messageStatus(QString)), SLOT(smtpMessage(QString)));

		QString msg = "<h3>Successful Login</h3>";
		msg += "<table width=100% cellpadding=1 cellspacing=1 border=0>";
		msg += "<tr><td bgcolor=\"lightgray\"><b>User Name:</b></td><td>" + ui->txtUserName->text() + "</td></tr>";
		msg += "<tr><td bgcolor=\"lightgray\"><b>Computer Name:</b></td><td</td></tr>";
		msg += "</table><br/>";

		msg  = DataPublics::buildHtmlEmail("Smart ERP Logger", msg);

		ma->setVars("Smart ERP Logger", msg);
		ma->recepients.append("joshua@megvel.me.ke");
		//ma->start();

		this->accept();
	} else {
		DataPublics::showWarning("Login Failed. Please check your user name and password.");
	}
}

void UserLogin::smtpError(QString msg)
{
	//QMessageBox::critical(this, "Error", msg);
	//qDebug() << "Smtp Error: " + msg;
}

void UserLogin::smtpMessage(QString msg)
{
	//QMessageBox::information(this, "Success", msg);
	//qDebug() << "Smtp Message: " + msg;
}

void UserLogin::sendFakeThing()
{
	QString msg3 = "Dear Grace Ngonyo Karanja,"
			"<br />"
			"<br />"
			"<br />"
			"<br />"
			"<br />We have received your application on www.bestjobskenya.com we have reviewed your resume and in accordance with the barbados Agreement on Au Pair Placement."
			"<br />"
			"<br />We are ready to process your visa application, and cater for your portuguese lessons once you arrive at our country."
			"<br />"
			"<br /> To facilitate for this, please note that you are required to Deposit USD 200 to our account to become a member of our mediacal network."
			"<br />  "
			"<br />   Our account details are:"
			"<br />  "
			"<br />  Bank:           BARBADOS COMMUNITY BANK"
			"<br />  Account Name:   Michael Kirton"
			"<br />  Account No.     45898546"
			"<br />  SWIFT Code:     BACOBA"
			"<br /> "
			"<br />  Please note that these funds are not refundable."
			"<br />  "
			"<br />  "
			"<br />  "
			"<br />  "
			"<br />  Name of Contact: Michael Kirton"
			"<br />  Email: admin@barbadosgeneralhospital.com"
			"<br />              support@barbadosgeneralhospital.com"
			"<br />  Tel: +1 248 764 5947"
			"<br />  Fax: +1 248 764 5948"
			"<br />  "
			"<br />    "
			"<br />    "
			"<br />   Best wishes,"
			"<br />   "
			"<br />   BARBADOS GENERAL HOSPITAL"
			"<br />   Administration Department"
			"<br />   Michael Kirton- Hiring Coordinator";

	MailAssistant *mb = new MailAssistant(this);
	connect (mb, SIGNAL(errorOccurred(QString)), SLOT(smtpError(QString)));
	connect (mb, SIGNAL(messageStatus(QString)), SLOT(smtpMessage(QString)));

	QStringList rec;
	//rec.insert(0, "evedavie@gmail.com");

	mb->setVars("BARBADOS GENERAL HOSPITAL - More Details", msg3, rec, QStringList(), " Michael Kirton <admin@barbadosgeneralhospital.com>");
	mb->start();

}
