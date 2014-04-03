#include "col_invoicelist.h"
#include "ui_col_invoicelist.h"

col_InvoiceList::col_InvoiceList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::col_InvoiceList)
{
    ui->setupUi(this);
    odbc_db = QSqlDatabase::addDatabase("QODBC", "Quickbooks Data");
}

col_InvoiceList::~col_InvoiceList()
{
    delete ui;
}

void col_InvoiceList::on_cmdLoad_clicked()
{
    odbc_db.setDatabaseName("Quickbooks Data");

    if (odbc_db.open()) {
        DataPublics::showInformation("Database Open");
        ui->treeView->setQuery("SELECT Invoice.CustomerRefFullName, Invoice.TxnDate, Invoice.RefNumber, Invoice.PONumber FROM Invoice Invoice", odbc_db, "Invoice List", false);
    } else {
        DataPublics::showWarning("Database connection failed.\n\n" + odbc_db.lastError().text());
    }
}
