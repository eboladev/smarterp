#include "qsmainwindow.h"
#include "ui_qsmainwindow.h"

#include <QDebug>
#include "pingtest.h"
#include <QTreeWidgetItem>
#include "mailassistant.h"
#include "datapublics.h"
#include "mailqueue.h"
QSMainWindow::QSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QSMainWindow)
{
    ui->setupUi(this);
    QString Octet = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    ui->txtStartAddress->setValidator(new QRegExpValidator(
                                          QRegExp("^" + Octet + "\\." + Octet + "\\." + Octet + "\\." + Octet + "$"), this));
    ui->txtEndAddress->setValidator(new QRegExpValidator(
                                        QRegExp("^" + Octet + "\\." + Octet + "\\." + Octet + "\\." + Octet + "$"), this));

    m_mailQueue = new MailQueue(this);
    connect (m_mailQueue, SIGNAL(message(QString)), this, SLOT(onMailLog(QString)));
    m_mailQueue->start();

    //ui->dtpProductionDate->setDate(QDate::currentDate());

    ui->dtpApportionDate->setDate(QDate::currentDate());
}

QSMainWindow::~QSMainWindow()
{
    delete ui;
}

void QSMainWindow::on_cmdScan_clicked()
{
    ui->trvScanResult->invisibleRootItem()->takeChildren();

    QString startAddress = ui->txtStartAddress->text();
    QString endAddress = ui->txtEndAddress->text();

    QString startNo = startAddress.split(".").last();
    QString endNo = endAddress.split(".").last();

    int d_startNo = startNo.toInt();
    int d_endNo = endNo.toInt();

    QStringList ipAddresses;

    for (int i = d_startNo; i <= d_endNo; i++) {
        QString prefix = startAddress.split(".").at(0) + "." +
                startAddress.split(".").at(1) + "." +
                startAddress.split(".").at(2) + ".";
        QString thisIp = prefix + QString::number(i);
        ipAddresses.append(thisIp);
    }

    if (ipAddresses.length() > 0) {
        for (int i = 0; i < ipAddresses.count(); i++) {
            QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvScanResult->invisibleRootItem());
            it->setText(0, ipAddresses.at(i));
            it->setBackgroundColor(0, Qt::gray);
            it->setBackgroundColor(1, Qt::gray);

            PingTest *test = new PingTest(this, ipAddresses.at(i));
            connect (test, SIGNAL(message(QString)), this, SLOT(pingthreadMessage(QString)));
            connect (test, SIGNAL(succeeded()), this, SLOT(pingThreadSuccess()));
            connect (test, SIGNAL(failed()), this, SLOT(pingthreadFailure()));
            test->start();
        }
    }
}

void QSMainWindow::pingthreadMessage(QString msg)
{
    PingTest *thread = qobject_cast<PingTest *>(sender());
    for (int i = 0; i < ui->trvScanResult->invisibleRootItem()->childCount(); i++) {
        QTreeWidgetItem *it = ui->trvScanResult->invisibleRootItem()->child(i);
        if (it->text(0) == thread->address) {
            it->setText(1, msg);
            it->setBackgroundColor(0, Qt::gray);
            it->setBackgroundColor(1, Qt::gray);
        }
    }
}

void QSMainWindow::pingthreadFailure()
{
    PingTest *thread = qobject_cast<PingTest *>(sender());
    for (int i = 0; i < ui->trvScanResult->invisibleRootItem()->childCount(); i++) {
        QTreeWidgetItem *it = ui->trvScanResult->invisibleRootItem()->child(i);
        if (it->text(0) == thread->address) {
            it->setText(1, "Host not found.");
            it->setBackgroundColor(0, Qt::red);
            it->setBackgroundColor(1, Qt::red);
        }
    }
}

void QSMainWindow::pingThreadSuccess()
{
    PingTest *thread = qobject_cast<PingTest *>(sender());
    for (int i = 0; i < ui->trvScanResult->invisibleRootItem()->childCount(); i++) {
        QTreeWidgetItem *it = ui->trvScanResult->invisibleRootItem()->child(i);
        if (it->text(0) == thread->address) {
            it->setText(1, "Host Alive.");
            it->setBackgroundColor(0, Qt::green);
            it->setBackgroundColor(1, Qt::green);
        }
    }
}

void QSMainWindow::onMailLog(QString log)
{
    ui->txtMailQueueLog->append(QString("\n[%1]: %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss dd-MMM-yyyy"), log));
}



void QSMainWindow::on_cmdApportion_clicked()
{



    QSqlDatabase db = DataPublics::getDatabase("AllocationDb", "cartons");
    db.setDatabaseName("cartons");

    db.exec("DELETE FROM corrugator_ai WHERE ProductionDate = '" + ui->dtpApportionDate->date().toString("yyyy-MM-dd") + "'");


    QSqlQuery qu = db.exec("SELECT DISTINCT(`OcNo`) AS 'Oc' FROM production_manual_allocation WHERE `Date` =  '" + ui->dtpApportionDate->date().toString("yyyy-MM-dd") + "'  GROUP BY `OcNo` ");

    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }

   QSqlQueryModel *model = new QSqlQueryModel(this);
   model->setQuery(qu);

    while (qu.next()) {
        QSqlQuery qu2 = db.exec("SELECT * FROM newreport WHERE TicketNo = '"  + qu.record().value("OcNo").toString() + "'");
        qu2.first();
        DataPublics::showInformation(qu.record().value("OcNo").toString());
        QString oc_no = qu2.record().value("TicketNo").toString();
        QString production_date = qu2.record().value("ScheduleDate").toString();
        QString theoretical_approxQty = qu2.record().value("ApproxQty").toString();
        QString actual_approxQty = "";

        QSqlQuery qu_1 = db.exec("INSERT INTO corrugator_ai (OcNo, ProductionDate, TheoreticalApproxQty) VALUES ('" +
                                 oc_no  + "', '"
                                 + production_date  + "', '"
                                 + theoretical_approxQty  + "')");
        QString entry_id = qu_1.lastInsertId().toString();
    }
}
