#include "col_invoicefetcher.h"
#include "ui_col_invoicefetcher.h"

#include "col_threadedinvoicefetcher.h"
col_InvoiceFetcher::col_InvoiceFetcher(QWidget *parent, QSqlDatabase database, QSqlDatabase OdbcDatbase) :
    QDialog(parent),
    ui(new Ui::col_InvoiceFetcher)
{
    ui->setupUi(this);
    db = database;
    odbc_db = OdbcDatbase;
    this->setWindowTitle("Getting quickbooks transactions.");
    col_ThreadedInvoiceFetcher *th = new col_ThreadedInvoiceFetcher(this, db, odbc_db);
    connect (th, SIGNAL(currentInv(QString)), SLOT(showProgress(QString)));
    connect (th, SIGNAL(complete()), SLOT(accept()));
    connect (th, SIGNAL(finished()), SLOT(accept()));
    //db.exec("DELETE FROM qb_transactions");
    th->start();
}

col_InvoiceFetcher::~col_InvoiceFetcher()
{
    delete ui;
}

void col_InvoiceFetcher::on_cmdCancel_clicked()
{

}

void col_InvoiceFetcher::showProgress(QString invNo)
{
    ui->lblCurrent->setText(invNo);
}
