#include "qcdataentry.h"
#include "ui_qcdataentry.h"
#include "datapublics.h"
QcDataEntry::QcDataEntry(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::QcDataEntry)
{
    ui->setupUi(this);
    db = database;
}

QcDataEntry::~QcDataEntry()
{
    delete ui;
}

void QcDataEntry::setOc(QString oc)
{
    ocID = oc;
    QSqlQuery qu = db.exec("SELECT * FROM qc WHERE TicketNO = '" + ocID + "'");
    qu.first();
    ui->txtCustomerName->setText(qu.record().value("CustomerName").toString());
    ui->txtProduct->setText(qu.record().value("Product").toString());
    ui->txtOcNo->setText(ocID);
    ui->txtPaperSpec->setText(DataPublics::getDbValue("SELECT PaperSpecs as 'dt' FROM newreport WHERE TicketNo = '" + ocID + "'", db, "dt").toString());
    ui->Target->setText(DataPublics::getDbValue("SELECT * FROM qc WHERE TicketNo = '" + ocID + "'", db, "OrderQty").toString());
    ui->txtOrderDate->setText(DataPublics::getDbValue("SELECT date_format(`newreport`.`Date`, '%D-%M-%Y') as 'dt' FROM newreport WHERE TicketNo = '" + ocID + "'", db, "dt").toString());

    ui->CorrugatedBW->setText(qu.record().value("CorrugatedBW").toString());
    ui->PrintedBW->setText(qu.record().value("PrintedBW").toString());
    ui->BCT->setText(qu.record().value("BCT").toString());
    ui->ECT->setText(qu.record().value("ECT").toString());
    ui->Run->setText(qu.record().value("Run").toString());
    ui->Target->setText(qu.record().value("Target").toString());
    ui->CrushTest->setText(qu.record().value("CrushTest").toString());
    ui->CartonWeight->setText(qu.record().value("CartonWeight").toString());
}

void QcDataEntry::on_cmcSave_clicked()
{
    QSqlQuery qu = db.exec("UPDATE qc SET "
                           "BCT = '" + ui->BCT->text() + "', "
                           "CorrugatedBW = '" + ui->CorrugatedBW->text() + "', "
                           "PrintedBW = '" + ui->PrintedBW->text() + "', "
                           "ECT = '" + ui->ECT->text() + "', "
                           "Run = '" + ui->Run->text() + "', "
                           "CrushTest = '" + ui->CrushTest->text() + "', " +
                           "CartonWeight = '" + ui->CartonWeight->text() + "' WHERE TicketNo = '" + ocID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning("<h1>Database Error</h1>" + qu.lastError().text());
    } else {
        this->accept();
    }

}
