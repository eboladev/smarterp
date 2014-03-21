#include "corrugatormw.h"
#include "ui_corrugatormw.h"
#include "datapublics.h"
#include <QTimer>

CorrugatorMW::CorrugatorMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CorrugatorMW)
{
    ui->setupUi(this);

    QTimer *tmr = new QTimer(this);
    connect (tmr, SIGNAL(timeout()), SLOT(reloadSchedule()));

    ui->txtCustomer->setReadOnly(true);
    ui->txtProduct->setReadOnly(true);
    ui->txtTarget->setReadOnly(true);

    db = DataPublics::getDatabase("corrugatorConnection", "cartons");

    db.open();

    reloadSchedule();
    tmr->start(60000);
}

CorrugatorMW::~CorrugatorMW()
{
    delete ui;
}

void CorrugatorMW::reloadSchedule()
{
    ui->lstSchedule->setQuery("SELECT EntryID, TicketNo as 'Oc Number', Client, Product, PaperSpecs, W, CorrugatorCuts as 'Cuts', CorrugatorOuts as 'Outs' from newreport WHERE scheduleDate = Current_Date() ORDER BY W DESC", db, "Corrugator Schedule", true);
    ui->lstSchedule->setColumnHidden(0, true);
    ui->lstSchedule->sortByColumn(5, Qt::DescendingOrder);
    ui->lstSchedule->resizeColumnToContents(2);
    ui->lstSchedule->resizeColumnToContents(3);
    ui->lstSchedule->resizeColumnToContents(4);
}

void CorrugatorMW::on_lstSchedule_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString id = ui->lstSchedule->getCurrentID();
    if (id.length() > 0) {
        currentOcID = id;
        currentOcNo = DataPublics::getDbValue("SELECT TicketNo FROM newreport WHERE EntryID = '" + id + "' LIMIT 0, 1", db, "TicketNo").toString();
        QSqlQuery qu = db.exec("SELECT * FROM newreport WHERE EntryID = '" + id + "' LIMIT 0, 1");
        if (!qu.lastError().isValid()) {
            qu.first();
            ui->txtCustomer->setText(qu.record().value("Client").toString());
            ui->txtProduct->setText(qu.record().value("Product").toString());
            ui->txtTarget->setText(qu.record().value("Qty").toString());
            ui->dtpStartTime->setTime(QTime::currentTime());
            ui->dtpEndTime->setTime(QTime::currentTime());
            ui->spinCuts->setValue(0);
            ui->spinOuts->setValue(0);
        } else {
            DataPublics::showWarning(qu.lastError().text());
        }
    } else {
        DataPublics::showWarning("No order selected.");
    }
}

void CorrugatorMW::on_cmdSave_clicked()
{
    QSqlQuery qu = db.exec("CALL CorrugatorData('" + currentOcID + "', '" + currentOcNo + "', '" + 
                           QString::number(ui->spinCuts->value()) + "', '" + QString::number(ui->spinOuts->value()) + "')");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
    } else {
        DataPublics::showInformation("Saved");
        reloadSchedule();
    }
}
