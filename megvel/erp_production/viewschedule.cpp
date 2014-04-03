#include "viewschedule.h"
#include "ui_viewschedule.h"

ViewSchedule::ViewSchedule(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::ViewSchedule)
{
	ui->setupUi(this);
	db = database;
	ui->dtpDate->setDate(QDate::currentDate());
	reloadSchedule();
}

ViewSchedule::~ViewSchedule()
{
	delete ui;
}

void ViewSchedule::reloadSchedule()
{
	ui->lstSchedule->setQuery("SELECT TicketNo as 'OC#', Client, Product, PaperSpecs, round(A, 0) as 'A', L, W, T, S, F1, F2,"
				  "F3, ProductionComment as 'Comment' FROM productionSchedule WHERE Date = '"
				  + ui->dtpDate->date().toString("yyyy-MM-dd") + "' ORDER By `W` DESC"
				  , db, "Production Schedule (" + ui->dtpDate->date().toString("dd MMM yyyy") + ")", false);
	ui->lstSchedule->sortByColumn(6, Qt::DescendingOrder);
}

void ViewSchedule::on_cmdPreviousDate_clicked()
{
	ui->dtpDate->setDate(ui->dtpDate->date().addDays(-1));
}

void ViewSchedule::on_cmdNextDate_clicked()
{
	ui->dtpDate->setDate(ui->dtpDate->date().addDays(1));
}

void ViewSchedule::on_cmdPrintProductionSchedule_clicked()
{
	ui->lstSchedule->actionPrint();
}

void ViewSchedule::on_dtpDate_dateChanged(const QDate &date)
{
	Q_UNUSED(date);
	reloadSchedule();
}
