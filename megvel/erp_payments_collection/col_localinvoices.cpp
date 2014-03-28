#include "col_localinvoices.h"
#include "ui_col_localinvoices.h"
#include "datapublics.h"
col_LocalInvoices::col_LocalInvoices(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::col_LocalInvoices)
{
    ui->setupUi(this);
    db = database;
    connect (ui->cmdShowTransactions, SIGNAL(clicked()), SLOT(showInvoices()));
    connect (ui->cmdFetchQuickbooksData, SIGNAL(clicked()), SLOT(refetchQbData()));
    DataPublics::loadQueryToComboBox("SELECT DISTINCT CustomerName FROM qb_transactions", "CustomerName", db, ui->cboCustomerList);

    ui->cboCustomerList->setEnabled(false);
    ui->groupBox->setEnabled(false);

    ui->dtpEndDate->setDate(QDate::currentDate());
    ui->dtpStartDate->setDate(QDate::currentDate());
}

col_LocalInvoices::~col_LocalInvoices()
{
    delete ui;
}

void col_LocalInvoices::showInvoices()
{
    QString query = "SELECT * FROM qb_transactions";

    if (ui->chkAllCustomers->isChecked() && ui->chkAllDates->isChecked()) {
        query.append(" ORDER BY EntryID DESC LIMIT 0, 2000");
    } else {
        query.append( " WHERE ");
        if (!ui->chkAllCustomers->isChecked()) {
            query.append( " CustomerName = '" + ui->cboCustomerList->currentText() + "' ");
        }

        if (!ui->chkAllCustomers->isChecked() && !ui->chkAllDates->isChecked()) {
            //Both boxes unchecked
            query.append( " AND ");
        }

        if (!ui->chkAllDates->isChecked()) {
            query.append(" (EntryDate BETWEEN '" + ui->dtpStartDate->date().toString("yyyy-MM-dd") + "' AND '" + ui->dtpEndDate->date().toString("yyyy-MM-dd") + "') ");
        }


    }


    qDebug() << query;


    ui->lstInvoices->setQuery(query, db, "Invoices", true);
    ui->lstInvoices->setColumnHidden(0, true);
}

#include "col_invoicefetcher.h"
void col_LocalInvoices::refetchQbData()
{
    QSqlDatabase qbDb = QSqlDatabase::addDatabase("QODBC", "Quickbooks Data");
    qbDb.setDatabaseName("Quickbooks Data");

    if (qbDb.open()) {
        col_InvoiceFetcher *ft = new col_InvoiceFetcher(this, db, qbDb);
        if (ft->exec() == QDialog::Accepted) {
            showInvoices();
        }
    } else {
        DataPublics::showWarning("Quickbooks Connection Error\n\n" + qbDb.lastError().text());
    }
}

#include "col_invoicedateupdater.h"
void col_LocalInvoices::on_cmdChangeInvoiceDates_clicked()
{
    QSqlDatabase qbDb = QSqlDatabase::addDatabase("QODBC", "Quickbooks Data");
    qbDb.setDatabaseName("Quickbooks Data");

    if (qbDb.open()) {
        col_InvoiceDateUpdater *dt = new col_InvoiceDateUpdater(this, db, qbDb);
        if (dt->exec() == QDialog::Accepted) {
            showInvoices();
        }
    } else {
        DataPublics::showWarning("Quickbooks Connection Error\n\n" + qbDb.lastError().text());
    }
}

void col_LocalInvoices::on_cmdFetchQuickbooksData_clicked()
{

}
