#include "companies.h"
#include "ui_companies.h"

Companies::Companies(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Companies)
{
    ui->setupUi(this);
    db = database;
    refreshData();
}

Companies::~Companies()
{
    delete ui;
}

void Companies::refreshData()
{
    ui->lstCompanies->setQuery(
                "SELECT CompanyID, CompanyName as 'Company',"
                "Telephone, ContactName as 'Contact',"
                "ContactTel as 'Contact Tel',"
                "ContactEmail as 'Email' FROM companies"
                , db, "Sacco Companies", true);
    ui->lstCompanies->setColumnHidden(0, true);
}
