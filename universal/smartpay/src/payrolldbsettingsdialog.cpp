#include "payrolldbsettingsdialog.h"
#include "ui_payrolldbsettingsdialog.h"

PayrollDbSettingsDialog::PayrollDbSettingsDialog(QWidget *parent, QString hName, QString uName, QString pWord) :
	QDialog(parent),
	ui(new Ui::PayrollDbSettingsDialog)
{
	ui->setupUi(this);
	ui->txtHostName->setText(hName);
	ui->txtUserName->setText(uName);
	ui->txtPassword->setText(pWord);
}

PayrollDbSettingsDialog::~PayrollDbSettingsDialog()
{
	delete ui;
}

void PayrollDbSettingsDialog::on_buttonBox_accepted()
{
	hostName = ui->txtHostName->text();
	userName = ui->txtUserName->text();
	password = ui->txtPassword->text();
	this->accept();
}
