#include "col_customerlist.h"
#include "ui_col_customerlist.h"

#include "datapublics.h"
col_CustomerList::col_CustomerList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::col_CustomerList)
{
    ui->setupUi(this);
    odbc_db = QSqlDatabase::addDatabase("QODBC", "Quickbooks Data");

}

col_CustomerList::~col_CustomerList()
{
    delete ui;
}

void col_CustomerList::openConnection()
{
    odbc_db.setDatabaseName("Quickbooks Data");

    if (odbc_db.open()) {
        DataPublics::showInformation("Database Open");
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery("SELECT Customer.CompanyName FROM Customer Customer", odbc_db);
        ui->treeView->setModel(model);
    } else {
        DataPublics::showWarning("Database connection failed.\n\n" + odbc_db.lastError().text());
    }
}

void col_CustomerList::on_cmdShow_clicked()
{
    openConnection();
}
