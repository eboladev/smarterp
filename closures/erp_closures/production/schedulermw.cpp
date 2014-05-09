#include "schedulermw.h"
#include "ui_schedulermw.h"
#include "datapublics.h"
#include <QtSql>

SchedulerMW::SchedulerMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SchedulerMW)
{
    ui->setupUi(this);

    ui->dtpDateToAddTo->setDate(QDate::currentDate());
    ui->calDate->setCurrentPage(QDate::currentDate().year(), QDate::currentDate().month());

    connect (ui->dtpDateToAddTo, SIGNAL(dateChanged(QDate)), SLOT(reloadSchedule()));
    reloadSchedule();
}

SchedulerMW::~SchedulerMW()
{
    delete ui;
}



void SchedulerMW::on_calDate_clicked(const QDate &date)
{
    QSqlDatabase db = QSqlDatabase::database("closures");
    ui->trvOrders->setQuery("SELECT * FROM vw_ocs WHERE `Order Date` = '" + date.toString("yyyy-MM-dd") + "'", db, "Orders", false);
    ui->trvOrders->setColumnHidden(0, false);
}

void SchedulerMW::reloadSchedule()
{
    ui->trvCurrentSchedule->setQuery("SELECT * FROM vw_schedule_theoretical WHERE `Schedule Date` = '" + ui->dtpDateToAddTo->date().toString("yyyy-MM-dd") + "'", QSqlDatabase::database(), "Production Schedule for " + ui->dtpDateToAddTo->date().toString("dd MMM yyyy"), true);
    ui->trvCurrentSchedule->setColumnHidden(0, true);
}

void SchedulerMW::on_cmdAddOrder_clicked()
{
    QString currentOrderID = ui->trvOrders->getCurrentID();
    if (currentOrderID.length() < 0) {
        DataPublics::showWarning("Please select an order to add to schedule.");
        return;
    }

    QSqlQuery machine_qu = QSqlDatabase::database("closures").exec("SELECT * FROM machines WHERE deleted  = 'false'");
    QString machine_id = "1";
    if (machine_qu.first()) {
        machine_id = machine_qu.record().value("machine_id").toString();
    }

    QSqlQuery qu = QSqlDatabase::database("closures").exec("INSERT INTO production_schedule (order_id, schedule_date, machine_id) VALUES('"
                                                 + currentOrderID  + "', '" + ui->dtpDateToAddTo->date().toString("yyyy-MM-dd") + "', '" + machine_id + "')");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }
    reloadSchedule();
}

#include <QMessageBox>
void SchedulerMW::on_cmdDeleteFromSchedule_clicked()
{
    QString schID = ui->trvCurrentSchedule->getCurrentID();
    if (schID.length() > 0) {
        if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this item?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
	    QSqlDatabase::database("closures").exec("DELETE FROM production_schedule WHERE entry_id = '" + schID + "'");
            reloadSchedule();
        }
    }
}

//#include "../gui-commons/reportshower.h"
void SchedulerMW::on_cmdPrintSchedule_clicked()
{
    //ReportShower *rpt = new ReportShower(this, true);
    //rpt->prepareReport("ProductionPlanning", false, true, " WHERE `Schedule Date` = '" + ui->dtpDateToAddTo->date().toString("yyyy-MM-dd") + "'");

}
