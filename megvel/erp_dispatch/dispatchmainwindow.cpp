#include "dispatchmainwindow.h"
#include "ui_dispatchmainwindow.h"
#include "dispatchlistdialog.h"
#include "confirmdelivery.h"
#include "newdispatchdialog.h"
#include "pastentriesdialog.h"
DispatchMainWindow::DispatchMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::DispatchMainWindow)
{
	ui->setupUi(this);
	db = database;
	ui->calDispatchDate->setSelectedDate(QDate::currentDate());
	ui->calDispatchDate->setMaximumDate(QDate::currentDate().addDays(1));
	reloadDispatch();

	connect (ui->calDispatchDate, SIGNAL(clicked(QDate)), this, SLOT(reloadDispatch()));
}

DispatchMainWindow::~DispatchMainWindow()
{
	delete ui;
}

void DispatchMainWindow::reloadDispatch()
{
	ui->trvDispatch->setQuery("SELECT * FROM vw_dispatch3 WHERE Date = '" + ui->calDispatchDate->selectedDate().toString("yyyy-MM-dd") + "'", db, "Dispatch Entries for " + ui->calDispatchDate->selectedDate().toString("dd-MMM-yyyy"), true);
	ui->trvDispatch->setColumnHidden(0, true);
}

void DispatchMainWindow::on_trvDispatch_doubleClicked(const QModelIndex &index)
{
	QString ocNo = index.model()->index(index.row(), 1).data().toString();
	DispatchListDialog dg(this, ocNo, db);
	dg.exec();
}

void DispatchMainWindow::on_pushButton_2_clicked()
{
	ConfirmDelivery conf(this, db);
	conf.exec();
}

void DispatchMainWindow::on_cmdNewDispatch_clicked()
{
	NewDispatchDialog dg(this, db);
	dg.exec();
	reloadDispatch();
}

void DispatchMainWindow::on_cmdSearchPastEntries_clicked()
{
	PastEntriesDialog past(this, db);
	past.exec();
}
