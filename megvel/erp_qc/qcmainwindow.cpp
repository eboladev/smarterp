#include "qcmainwindow.h"
#include "ui_qcmainwindow.h"
#include "qcdataentry.h"
QcMainWindow::QcMainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::QcMainWindow)
{
    ui->setupUi(this);
    db = database;
    ui->dtpStartDate->setDate(QDate::currentDate().addMonths(-3));
    ui->dtpEndDate->setDate(QDate::currentDate());
    reload();

    aliveTimer = new QTimer(this);
    connect (aliveTimer, SIGNAL(timeout()), SLOT(alive()));
    aliveTimer->start(10000);

    ui->trvQcData->setVisible(false);
}

QcMainWindow::~QcMainWindow()
{
    delete ui;
}

void QcMainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString id =  ui->treeView->getCurrentID();
    QcDataEntry *ed = new QcDataEntry(this, db);
    ed->setOc(id);
    if (ed->exec() == QDialog::Accepted) {
        reload();
    }
}

void QcMainWindow::reload()
{
    QString query = tr("SELECT TicketNo, TicketNo, OrderDate,CustomerName,Product,CartonWeight,OrderQty, Run FROM vw_qc WHERE (vw_qc.OrderDate BETWEEN '%1' AND '%2') AND (CustomerName LIKE '%3' OR TicketNo LIKE '%3' OR Product LIKE '%3') ORDER BY OrderDate DESC").arg(DataPublics::mysqlDate(ui->dtpStartDate->date()), DataPublics::mysqlDate(ui->dtpEndDate->date()), "%" + ui->txtSearch->text() + "%");
    ui->treeView->setQuery(query, db, "QC Entries", true);
    ui->treeView->setColumnHidden(0, true);
    ui->treeView->setSearchVisible(false);
//    ui->trvQcData->invisibleRootItem()->takeChildren();
//    QSqlQuery qu;
//    qu.setForwardOnly(true);
//    qu = db.exec(query);
//    while (qu.next()) {
//        QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvQcData);
//        it->setText(0, qu.record().value("TicketNo").toString());
//        it->setText(1, qu.record().value("OrderDate").toString());
//        it->setText(2, qu.record().value("CustomerName").toString());
//        it->setText(3, qu.record().value("Product").toString());
//        it->setText(4, qu.record().value("CartonWeight").toString());
//        it->setText(5, qu.record().value("OrderQty").toString());
//        it->setText(6, qu.record().value("Run").toString());
//    }
}

void QcMainWindow::on_cmdShowOcs_clicked()
{
    reload();
}

void QcMainWindow::alive()
{

    if (!db.isOpen())
        db.open();
    db.exec("SELECT NOW()");
}

void QcMainWindow::on_trvQcData_doubleClicked(const QModelIndex &index)
{

}
