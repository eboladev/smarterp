#include "saccomainwindow.h"
#include "ui_saccomainwindow.h"
#include <QtSql>
#include "datapublics.h"
SaccoMainWindow::SaccoMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::SaccoMainWindow)
{
	ui->setupUi(this);
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "sacco");
	db.setHostName(DataPublics::getSettingValue("dbHostName", "192.168.0.8").toString());
	db.setUserName(DataPublics::getSettingValue("dbUserName", "root").toString());
	db.setPassword(DataPublics::getSettingValue("dbPassword", "pledge").toString());

	db.setDatabaseName("zaracbs");

	if (db.open()) {
		ui->statusBar->showMessage("Connected to " + db.hostName());
	} else {
		DataPublics::showWarning("Database Connection Failed <br/><br/>" + db.lastError().text());
	}
}

SaccoMainWindow::~SaccoMainWindow()
{
	delete ui;
}
