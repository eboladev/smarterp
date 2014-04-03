#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "settingsmanager.h"
SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	sett = new SettingsManager(this);
	ui->odbcDataSource->setText(sett->odbcDataSource());
	ui->mysqlDbName->setText(sett->mysqlDatabaseName());
	ui->mysqlHostName->setText(sett->mysqlHostName());
	ui->mysqlPassword->setText(sett->mysqlPassword());
	ui->mysqlUserName->setText(sett->mysqlUserName());
}

SettingsDialog::~SettingsDialog()
{
	sett->setOdbcDataSource(ui->odbcDataSource->text());
	sett->setMysqlDatabaseName(ui->mysqlDbName->text());
	sett->setMysqlHostName(ui->mysqlHostName->text());
	sett->setMysqlPassword(ui->mysqlPassword->text());
	sett->setMysqlUserName(ui->mysqlUserName->text());
	delete ui;
}
