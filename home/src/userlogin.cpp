#include "userlogin.h"
#include "ui_userlogin.h"
#include "mailassistant.h"
#include "settingsmanager.h"

UserLogin::UserLogin(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::UserLogin)
{
	ui->setupUi(this);
	db = QSqlDatabase::addDatabase("QMYSQL");

}

UserLogin::~UserLogin()
{
	delete ui;
}

void UserLogin::on_cmdLogin_clicked()
{
	if (db.isOpen()) {
		db.close();
	}
	dbHostName = SettingsManager::getSettingValue("dbHostName").toString();
	dbUserName = SettingsManager::getSettingValue("dbUserName", "root").toString();
	dbPassword = SettingsManager::getSettingValue("dbPassword", "pledge").toString();

	//if hostname is blank, use and save default values
	if (dbHostName.length() < 1) {
		dbHostName = "192.168.0.8";
		SettingsManager::setSettingValue("dbHostName", dbHostName);
		SettingsManager::setSettingValue("dbUserName", dbUserName);
		SettingsManager::setSettingValue("dbPassword", dbPassword);

		SettingsManager::setSettingValue("tlmServer", "197.254.15.122");
		SettingsManager::setSettingValue("tlmPort", "4317");

		SettingsManager::setSettingValue("smtpServer", "197.254.15.122");
		SettingsManager::setSettingValue("smtpPort", "25");

		SettingsManager::setSettingValue("smtpSSL", "0");
		SettingsManager::setSettingValue("smtpAuthentication", "0");

		SettingsManager::setSettingValue("smtpUserName", "");
		SettingsManager::setSettingValue("smtpPassword", "");
	}

	db.setUserName(dbUserName);
	db.setHostName(dbHostName);
	db.setPassword(dbPassword);
	db.setDatabaseName("cartons");
	if (!db.open()) {
		DataPublics::showWarning("<b>Database Connection Failed<b><br/>" + db.lastError().text());
		return;
	}

	QSqlQuery qu = db.exec(tr("SELECT * FROM `cartons`.`users` WHERE `UserName` = '%1' AND `Password` = '%2'")
			       .arg(ui->txtUserName->text(), ui->txtPassword->text()));
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}
	if (qu.first()) {
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

		this->accept();
	} else {
		DataPublics::showWarning("Login Failed. Please check your user name and password.");
	}
}

void UserLogin::smtpError(QString msg)
{
	qDebug() << "Smtp Error: " + msg;
}

void UserLogin::smtpMessage(QString msg)
{
	qDebug() << "Smtp Message: " + msg;
}


#include "databasesetupdialog.h"
void UserLogin::on_cmdDbSetup_clicked()
{
	DatabaseSetupDialog *dg = new DatabaseSetupDialog(this);
	dg->exec();
}
