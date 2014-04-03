#include "levamainwindow.h"
#include "ui_levamainwindow.h"


LevaMainWindow::LevaMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::LevaMainWindow)
{
	ui->setupUi(this);
	db = database;

	//addConnection("", "", "", "", 3306);
}

LevaMainWindow::~LevaMainWindow()
{
	delete ui;
}

void LevaMainWindow::addConnection(QString serverName, QString userName, QString password, QString dbName, int port)
{
	LevaConnectionWindow *lvcw = new LevaConnectionWindow(0);
	lvcw->hostName = serverName;
	lvcw->originalUserName = userName;
	lvcw->originalPassword = password;
	lvcw->originalDb = dbName;
	lvcw->originalPort = port;
	lvcw->setOriginalVars();
	ui->tabWidget->insertTab(ui->tabWidget->count(), lvcw, lvcw->windowTitle());
}

void LevaMainWindow::on_actionNew_Connection_triggered()
{
	addConnection(db.hostName(), db.userName(), db.password(), db.databaseName(), db.port());
}
