#include "databasesetupdialog.h"
#include "ui_databasesetupdialog.h"

#include <QSqlDatabase>
#include "datapublics.h"
#include "settingsmanager.h"
DatabaseSetupDialog::DatabaseSetupDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DatabaseSetupDialog)
{
	ui->setupUi(this);

	ui->txtHostName->setText(SettingsManager::getSettingValue("dbHostName").toString());
	ui->txtUserName->setText(SettingsManager::getSettingValue("dbUserName").toString());
	ui->txtPassword->setText(SettingsManager::getSettingValue("dbPassword").toString());

	ui->txtTlmServer->setText(SettingsManager::getSettingValue("tlmServer").toString());
	ui->txtTLMPort->setText(SettingsManager::getSettingValue("tlmPort").toString());

	ui->txtSMTPServer->setText(SettingsManager::getSettingValue("smtpServer").toString());
	ui->txtSMTPPort->setText(SettingsManager::getSettingValue("smtpPort").toString());

	ui->txtSMTPUserName->setText(SettingsManager::getSettingValue("smtpUserName").toString());
	ui->txtSMTPPassword->setText(SettingsManager::getSettingValue("smtpPassword").toString());

	QString ssl = SettingsManager::getSettingValue("smtpSSL").toString();
	QString auth = SettingsManager::getSettingValue("smtpAuthentication").toString();

	if (ssl == "1")
		ui->chkSMTPSSL->setChecked(true);

	if (auth == "1")
		ui->chkSMTPAuth->setChecked(true);
}

DatabaseSetupDialog::~DatabaseSetupDialog()
{
	delete ui;
}

void DatabaseSetupDialog::on_buttonBox_rejected()
{
	this->reject();
}

void DatabaseSetupDialog::on_buttonBox_accepted()
{
	SettingsManager::setSettingValue("dbHostName", ui->txtHostName->text());
	SettingsManager::setSettingValue("dbUserName", ui->txtUserName->text());
	SettingsManager::setSettingValue("dbPassword", ui->txtPassword->text());

	SettingsManager::setSettingValue("tlmServer", ui->txtTlmServer->text());
	SettingsManager::setSettingValue("tlmPort", ui->txtTLMPort->text());

	SettingsManager::setSettingValue("smtpUserName", ui->txtSMTPUserName->text());
	SettingsManager::setSettingValue("smtpPassword", ui->txtSMTPPassword->text());

	QString auth = "0";
	QString ssl = "0";

	if (ui->chkSMTPAuth->isChecked())
		auth  = "1";

	if (ui->chkSMTPSSL->isChecked())
		ssl = "1";

	SettingsManager::setSettingValue("smtpAuthentication", auth);
	SettingsManager::setSettingValue("smtpSSL", ssl);

	this->accept();
}

void DatabaseSetupDialog::on_cmdTestConnection_clicked()
{
	QSqlDatabase testDb = QSqlDatabase::addDatabase("QMYSQL", "settings_test");
	testDb.setHostName(ui->txtHostName->text());
	testDb.setUserName(ui->txtUserName->text());
	testDb.setPassword(ui->txtPassword->text());

	if (testDb.open()) {
		QMessageBox::information(this, "Success", "Connection successful.");
		testDb.close();
	} else {
		QMessageBox::critical(this, "Database Error", "<b>Connection Failed</b><br/>" + testDb.lastError().text());
	}

	QSqlDatabase::removeDatabase("settings_test");
}
