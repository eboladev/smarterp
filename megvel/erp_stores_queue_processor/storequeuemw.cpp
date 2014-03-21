#include "storequeuemw.h"
#include "ui_storequeuemw.h"

#include "datapublics.h"
StoreQueueMW::StoreQueueMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StoreQueueMW)
{
    ui->setupUi(this);
    writeLog("Starting queue processor");
    minuteTimer = new QTimer(this);
    connect (minuteTimer, SIGNAL(timeout(QPrivateSignal)), SLOT(onMinuteTimer()));
    minuteTimer->start(60000);
    writeLog("Connecting to db");
    db = DataPublics::getDatabase("queue-conn", "cartons");
    //db.open();

    secondTimer = new QTimer(this);
    connect (secondTimer, SIGNAL(timeout(QPrivateSignal)), SLOT(onSecondTimer()));
    secondTimer->start(1000);
}

StoreQueueMW::~StoreQueueMW()
{
    delete ui;
}

void StoreQueueMW::onMinuteTimer()
{
    writeLog("Looking for unposted items...");
    QSqlDatabase mysqlDb = DataPublics::getDatabase("queue-timer", "cartons");
    QSqlDatabase odbcDb = QSqlDatabase::addDatabase("QODBC");

    writeLog("Clossing queue db connections...");
    if (mysqlDb.isOpen()) {
        mysqlDb.close();
    }
    if (odbcDb.isOpen()) {
        odbcDb.close();
    }
    writeLog("Connections Closed.");
}

void StoreQueueMW::onSecondTimer()
{
    if (db.isOpen()) {
        writeLog("Open...");
        ui->trvQueued->setQuery("SELECT EntryID as 'Rqn No.', RequestedBy as 'Requested By', RequisitionDate as 'Reqn Date' , DateRequired as 'Date Required', suppliers.SupplierName as 'Supplier' FROM store_requisition_master, suppliers WHERE (Status = 'Queued') AND (store_requisition_master.SupplierID = suppliers.supplierID)", db, "Queued Requisitions", true);
        ui->trvPosted->setQuery("SELECT EntryID as 'Rqn No.', RequestedBy as 'Requested By', RequisitionDate as 'Reqn Date' , DateRequired as 'Date Required', suppliers.SupplierName as 'Supplier' FROM store_requisition_master, suppliers WHERE (Status = 'Posted') AND (store_requisition_master.SupplierID = suppliers.supplierID)", db, "Posted Requisitions", true);
    } else {
        db.open();
    }
}

void StoreQueueMW::writeLog(QString msg)
{
    ui->txtLog->append("[" + QDateTime::currentDateTime().toString("yyyy-MMM-dd hh:mm:ss") + "]: " + msg);
}
