#include "userlogin.h"
#include "ui_userlogin.h"

#include <QMessageBox>
#include "datapublics.h"
#include "selectcompanydialog.h"
#include "payrolldbsettingsdialog.h"
#include <QSettings>
UserLogin::UserLogin(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::UserLogin)
{
	ui->setupUi(this);
	hostName = getSettingValue("dbHostName", "192.168.0.8").toString();
	userName = getSettingValue("dbUserName", "root").toString();
	password = getSettingValue("dbPassword", "pledge").toString();

	db = QSqlDatabase::addDatabase("QMYSQL", "payrollConnection");
	db.setUserName(userName);
	db.setPassword(password);
	db.setHostName(hostName);
	db.setDatabaseName("smartpay-master");

	db.open();

	connect (ui->Cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect (ui->Login, SIGNAL(clicked()), SLOT(tryLogin()));
	DataPublics::loadQueryToComboBox("SELECT * FROM `smartpay-master`.companies", "CompanyName",
					 db, ui->cboCompanies);
	for (int i = 0; i < ui->cboCompanies->count(); i++) {
		companies.append(ui->cboCompanies->itemText(i));
	}
	ui->label_5->setVisible(false);
	ui->cboCompanies->setVisible(false);
}

UserLogin::~UserLogin()
{
	delete ui;
}

void UserLogin::tryLogin() {
	if (!db.isOpen()) {
		DataPublics::showWarning("Please check the database settings.");
		return;
	}
	bool ok = false;
	payrollAccess = false;
	bool dbOk;
	dbOk = true;
	// QSqlQuery qu = db.exec("SELECT UserName, CompanyName, PayrollAccess, Password, DatabaseName FROM `smartpay-master`.vw_company_users WHERE UserName = '" + ui->UserName->text() + "' AND CompanyName = '" + ui->cboCompanies->currentText() + "' AND `Password` = PASSWORD('" + ui->Password->text() + "')");
	QSqlQuery qu = db.exec("SELECT UserID, UserName, CompanyName, PayrollAccess, Password, DatabaseName FROM `smartpay-master`.vw_company_users WHERE UserName = '" + ui->UserName->text() + "' AND `Password` = PASSWORD('" + ui->Password->text() + "')");

	if (qu.lastError().isValid()) {
		ok = false;
	} else {
		if (qu.size() < 1) {
			ok = false;
		} else {
			userID = DataPublics::getDbValue("SELECT * FROM users WHERE UserName = '" + ui->UserName->text() + "'", db, "UserID").toString();
			ok = true;
		}
	}
	if (!ok) {
		QMessageBox::critical(this, "Login Error", "Login failed.\nYou may have entered the wrong company information, or you may have selected a company for which you do not have access.\n\nDatabase Error\n" + qu.lastError().text());
	} else {
		QSqlQuery cQu = db.exec("SELECT * FROM `smartpay-master`.vw_company_users WHERE UserID = '" + qu.record().value("UserID").toString() + "'");
		while (cQu.next()) {
			companies.append(cQu.record().value("CompanyName").toString());
		}
		//		SelectCompanyDialog *cmp = new SelectCompanyDialog(this, companies);
		//		if (cmp->exec()) {
		//			companies = cmp->selectedCompanies();
		//		}
		this->accept();
	}
}

void UserLogin::on_cmdAuthConfig_clicked()
{
	QString authPassword = QInputDialog::getText(this, "Database Settings", "Enter your admin password",
						     QLineEdit::Password);
	if (authPassword == "pledge") {
		PayrollDbSettingsDialog *dbSet = new PayrollDbSettingsDialog(this, hostName, userName, password);
		if (dbSet->exec() == QDialog::Accepted) {
			setSettingValue("dbHostName", dbSet->hostName);
			setSettingValue("dbUserName", dbSet->userName);
			setSettingValue("dbPassword", dbSet->password);
			hostName = dbSet->hostName;
			userName = dbSet->userName;
			password = dbSet->password;
			if (db.isOpen()) {
				QSqlDatabase::removeDatabase("payrollConnection");
				db.close();
			}
			db.setHostName(hostName);
			db.setUserName(userName);
			db.setPassword(password);
			db.open();
		}
	}
}

void UserLogin::setSettingValue(QString settingName, QVariant value)
{
	QSettings sett("Smart Software", "SmartPay");
	sett.setValue(settingName, value);
}

QVariant UserLogin::getSettingValue(QString settingName, QVariant defaultValue)
{
	QSettings sett("Smart Software", "SmartPay");
	return sett.value(settingName, defaultValue);
}
