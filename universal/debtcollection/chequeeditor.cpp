#include "chequeeditor.h"
#include "ui_chequeeditor.h"
#include "datapublics.h"
ChequeEditor::ChequeEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::ChequeEditor)
{
    ui->setupUi(this);
    db = database;
    isAdding = true;

    DataPublics::loadQueryToComboBox("SELECT * FROM customers", "CompanyName", db, ui->cboCustomer);

    ui->dtpDateReceived->setDate(QDate::currentDate());
    ui->dtpChequeDate->setDate(QDate::currentDate());
}

ChequeEditor::~ChequeEditor()
{
    delete ui;
}

void ChequeEditor::AddNew()
{
    isAdding = true;
}


void ChequeEditor::Edit(QString chequeID)
{
    isAdding = false;
    currentID = chequeID;

    QSqlQuery qu = db.exec("SELECT * FROM cheques WHERE ChequeID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
    } else {
        qu.first();
        QString customerName = DataPublics::getDbValue("SELECT * FROM customers WHERE CustomerID = '" + qu.record().value("CustomerID").toString() + "'", db, "CompanyName").toString();
        for (int i = 0; i < ui->cboCustomer->count(); i++) {
            if (ui->cboCustomer->itemText(i) == customerName)
                ui->cboCustomer->setCurrentIndex(i);
        }

        ui->dtpChequeDate->setDate(qu.record().value("ChequeDate").toDate());
        ui->dtpDateReceived->setDate(qu.record().value("DateReceived").toDate());
        ui->txtAmount->setText(qu.record().value("Amount").toString());
        ui->txtBank->setText(qu.record().value("Bank").toString());
        ui->txtChequeNo->setText(qu.record().value("ChequeNo").toString());
        ui->txtReceivedBy->setText(qu.record().value("ReceivedBy").toString());
    }
}

void ChequeEditor::on_cmdSave_clicked()
{
    QString query = "SELECT NOW()";

    QString customerID = DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'", db, "CustomerID").toString();


    if (isAdding) {
        query = "INSERT INTO cheques (CustomerID, DateReceived, ChequeDate, Bank, "
                " ChequeNo, Amount, ReceivedBy) VALUES ('"
                + customerID + "', '"
                + ui->dtpDateReceived->date().toString("yyyy-MM-dd") + "', '"
                + ui->dtpChequeDate->date().toString("yyyy-MM-dd") + "', '"
                + ui->txtBank->text()  + "', '"
                + ui->txtChequeNo->text() + "', '"
                + ui->txtAmount->text() + "', '"
                + ui->txtReceivedBy->text()  + "')";
    } else {
        query = "UPDATE cheques SET "
                " CustomerID = '" + customerID + "', "
                " DateReceived = '" + ui->dtpDateReceived->date().toString("yyyy-MM-dd") + "', "
                " ChequeDate = '" + ui->dtpChequeDate->date().toString("yyyy-MM-dd") + "', "
                " Bank = '" + ui->txtBank->text()  + "', "
                " ChequeNo = '" + ui->txtChequeNo->text() + "', "
                " Amount = '" + ui->txtAmount->text() + "', "
                " ReceivedBy = '" + ui->txtReceivedBy->text() + "' "
                " WHERE ChequeID = '" + currentID + "'";
    }


    QSqlQuery qu = db.exec(query);
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
    } else {
        this->accept();
    }
}
