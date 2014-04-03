#include "imsstoremainwindow.h"
#include "ui_imsstoremainwindow.h"
#include "datapublics.h"

ImsStoreMainWindow::ImsStoreMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::ImsStoreMainWindow)
{
	ui->setupUi(this);

	db = QSqlDatabase::addDatabase("QMYSQL", "reelReceiverDb");
	db.setDatabaseName("ims");
	db.setHostName(database.hostName());
	db.setUserName(database.userName());
	db.setPassword(database.password());

	if (!db.open()) {
		db = database;
		db.exec("USE ims");
	}


	reelsModel = new QSqlTableModel(this);
	ui->tblReels->setModel(reelsModel);

	reloadContainers();
	connect (ui->cmdRefreshContainers, SIGNAL(clicked()), SLOT(reloadContainers()));
}

ImsStoreMainWindow::~ImsStoreMainWindow()
{
	delete ui;
}

void ImsStoreMainWindow::reloadContainers()
{
	ui->trvContainers->setQuery("SELECT * FROM vw_arrived_containers", db, "Containers", true);
	ui->trvContainers->setColumnHidden(0, true);
}

void ImsStoreMainWindow::showReels()
{

}

void ImsStoreMainWindow::on_trvContainers_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString containerID = ui->trvContainers->getCurrentID();
	if (containerID.length() < 1)
		return;

	reelsModel = new QSqlTableModel(this, db);
	reelsModel->setTable("reels");
	reelsModel->setFilter("ContainerID = '" + containerID + "'");
	reelsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
	reelsModel->select();


	ui->tblReels->setModel(reelsModel);
	ui->tblReels->setColumnHidden(0, true);
	ui->tblReels->setColumnHidden(1, true);

	QString cnt = QString::number(reelsModel->rowCount());
	QString wt = "0";

	QSqlQuery qu = db.exec("SELECT sum(weight) as wt FROM reels WHERE ContainerID = '" + containerID + "'");
	if (!qu.lastError().isValid()) {
		qu.first();
		wt = qu.record().value("wt").toString();
	}

	QString summary = tr("<html><head/><body><table border=\"0\" style=\""
			     "margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;"
			     " width=\"100%\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p><span style="
			     "font-size:10pt; font-weight:600;\">Number Of Reels</span></p><p><span style="
			     "font-size:10pt; font-weight:600; color:#00007f;\">%1</span></p></td><td><p><span style="
			     "font-size:10pt; font-weight:600;\">Total Weight</span></p><p><span style="
			     "font-size:10pt; font-weight:600; color:#00007f;\">%2</span></p></td></tr></table></body></html>").
			arg(cnt, wt);

	ui->lblSummary->setText(summary);

}

void ImsStoreMainWindow::on_cmdSave_clicked()
{

}
