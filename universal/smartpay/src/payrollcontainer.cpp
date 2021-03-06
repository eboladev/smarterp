#include "payrollcontainer.h"
#include "ui_payrollcontainer.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "userlogin.h"
PayrollContainer::PayrollContainer(QWidget *parent, bool embedded, QStringList companies, QString user_id) :
	QMainWindow(parent),
	ui(new Ui::PayrollContainer)
{
	ui->setupUi(this);
	bEmbed = embedded;
	selectedCompanies = companies;
	userID = user_id;
	logIn();
}

PayrollContainer::~PayrollContainer()
{
	delete ui;
}

#include "mainwindow.h"
void PayrollContainer::logIn()
{
	db = QSqlDatabase::database("payrollConnection");
	QSqlQuery qu = db.exec("SELECT * FROM `smartpay-master`.vw_company_users WHERE UserID = '" + userID + "'");
	if (!qu.lastError().isValid()) {
		int ci = 0;
		while (qu.next()) {
			//qDebug() << ci << qu.record();
			ci++;
			QString s_payrollAccess = qu.record().value("PayrollAccess").toString();
			bool pAccess = false;
			if (s_payrollAccess == "Yes")
				pAccess = true;

			QString dbName = qu.record().value("DatabaseName").toString();
			QString companyName = qu.record().value("CompanyName").toString();


			QSqlDatabase cDb;

			if (bEmbed) {
				cDb  = QSqlDatabase::addDatabase("QMYSQLEMBEDDED", QString::number(ci) + companyName + "connection");
				cDb.setHostName("localhost");
				cDb.setUserName("root");
				cDb.setDatabaseName("smartpay_demo");
			} else {
				cDb  = QSqlDatabase::addDatabase("QMYSQL", QString::number(ci) + companyName + "connection");
				cDb.setHostName(db.hostName());
				cDb.setPassword(db.password());
				cDb.setUserName(db.userName());
				cDb.setDatabaseName(dbName);
			}

			//qDebug() << selectedCompanies << companyName;
			if (selectedCompanies.contains(companyName)) {
				MainWindow *mw = new MainWindow(ui->mdiArea, db);
				mw->setCompanyName(qu.record().value("FullName").toString());
				mw->companyDb = cDb;
				mw->payrollAccess = pAccess;
				mw->logIn();
				mw->setWindowTitle(companyName);
				ui->mdiArea->addSubWindow(mw);
				mw->show();
			}
		}
	} else {
		QMessageBox::critical(this, "Error", qu.lastError().text());
	}
}
