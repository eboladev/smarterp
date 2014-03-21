#include "erp_complains_editor.h"
#include "ui_erp_complains_editor.h"

#include "datapublics.h"

erp_complains_editor::erp_complains_editor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::erp_complains_editor)
{
    ui->setupUi(this);
    db = database;

    DataPublics::loadQueryToComboBox("SELECT * FROM customers", "CompanyName", db, ui->cboCustomer);
    ui->dtpDate->setDate(QDate::currentDate());

    isAdding = true;
}

erp_complains_editor::~erp_complains_editor()
{
    delete ui;
}

void erp_complains_editor::AddNew()
{
    isAdding = true;
}

void erp_complains_editor::Edit(QString ComplainID)
{
    currentID = ComplainID;
    isAdding = false;

    QSqlQuery qu = db.exec("SELECT * FROM erp_complains WHERE ComplainID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
    } else {
        qu.first();
        QSqlRecord rec = qu.record();
        QString customerID = rec.value("CustomerID").toString();
        QString productID = rec.value("ProductID").toString();
        ui->txtOCRef->setText(rec.value("OCRef").toString());
        ui->dtpDate->setDate(QDate::fromString(rec.value("LoggedOn").toString(), "yyyy-MM-dd"));
        ui->txtComplain->setPlainText(rec.value("Complain").toString());

        QString cust = DataPublics::getDbValue("SELECT * FROM customers WHERE CustomerID = '" + customerID + "'", db, "CompanyName").toString();
        QString prod = DataPublics::getDbValue("SELECT * FROM products WHERE `Product ID` = '" + productID + "'", db, "Product").toString();

        for (int c = 0; c < ui->cboCustomer->count(); c++) {
            if (ui->cboCustomer->itemText(c) == cust)
                ui->cboCustomer->setCurrentIndex(c);
        }

        for (int p = 0; p < ui->cboProduct->count(); p++) {
            if (ui->cboProduct->itemText(p) == prod)
                ui->cboProduct->setCurrentIndex(p);
        }
    }
}

void erp_complains_editor::on_cmdSave_clicked()
{
    QString customerID = DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'", db, "CustomerID").toString();
    QString productID = DataPublics::getDbValue("SELECT `Product ID` as p FROM products WHERE Product = '" + ui->cboProduct->currentText() + "'", db, "p").toString();

    QString query = "SELECT NOW()";

    if (!isAdding) {
        db.exec("DELETE FROM erp_complains WHERE ComplainID = '" + currentID + "'");
    }
    query = "INSERT INTO erp_complains (CustomerID, ProductID, OCRef, LoggedOn, UserID, Complain) VALUES ('" +
            customerID + "', '"+
            productID  + "', '"+
            ui->txtOCRef->text()  + "', '"+
            ui->dtpDate->date().toString("yyyy-MM-dd")  + "', '"+
            DataPublics::getCurrentUserID()  + "', '"+
            ui->txtComplain->toPlainText() + "')";


    QSqlQuery qu = db.exec(query);
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
    } else {
        this->accept();
    }
}

void erp_complains_editor::on_cboCustomer_currentIndexChanged(const QString &arg1)
{
    ui->cboProduct->clear();
    QString customerID = DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" + arg1 + "'", db, "CustomerID").toString();
    DataPublics::loadQueryToComboBox("SELECT * FROM products WHERE Customer = '" + customerID + "'", "Product", db, ui->cboProduct);
}

