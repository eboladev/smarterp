#include "col_invoicedateupdater.h"
#include "ui_col_invoicedateupdater.h"

#include "col_threadedinvoicedatechanger.h"
col_InvoiceDateUpdater::col_InvoiceDateUpdater(QWidget *parent, QSqlDatabase database, QSqlDatabase OdbcDatbase) :
	QDialog(parent),
	ui(new Ui::col_InvoiceDateUpdater)
{
	ui->setupUi(this);
	db = database;
	odbc_db = OdbcDatbase;

	col_ThreadedInvoiceDateChanger *th = new col_ThreadedInvoiceDateChanger(this, db, odbc_db);
	connect (th, SIGNAL(currentInv(QString)), SLOT(showProgress(QString)));
	connect (th, SIGNAL(complete()), SLOT(accept()));
	connect (th, SIGNAL(finished()), SLOT(accept()));

	th->start();
}

col_InvoiceDateUpdater::~col_InvoiceDateUpdater()
{
	delete ui;
}

void col_InvoiceDateUpdater::on_cmdCancel_clicked()
{
	this->reject();
}

void col_InvoiceDateUpdater::showProgress(QString invNo)
{
	ui->lblCurrent->setText(invNo);
}
