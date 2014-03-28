#include "companymanager.h"
#include "ui_companymanager.h"
#include <QMessageBox>
CompanyManager::CompanyManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompanyManager)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("free_sacco");

    model = new SqlTableModel(this, db);
    loadCompanies();
}

CompanyManager::~CompanyManager()
{
    delete ui;
}

void CompanyManager::loadCompanies()
{
    model = new SqlTableModel(this, db);
    model->setSchema("freesacco");
    model->setTable("fs_companies");
    model->setEditStrategy(SqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(1, Qt::Horizontal, "Company Name", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Address", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Postcode", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal, "Town", Qt::DisplayRole);
    model->setHeaderData(5, Qt::Horizontal, "Country", Qt::DisplayRole);
    ui->tblCompanies->setModel(model);
    ui->tblCompanies->setColumnHidden(0, true);
    ui->tblCompanies->resizeColumnsToContents();
    ui->tblCompanies->resizeRowsToContents();
}

void CompanyManager::on_cmdNewCompany_clicked()
{
    model->insertRows(model->rowCount(), 1);
}

void CompanyManager::on_cmdDeleteCompany_clicked()
{
    if (QMessageBox::question(this,
                              tr("Confirm Delete")
                              , tr("Are you sure you want to delete this company?")
                              , QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
        return;
    }

    model->removeRows(ui->tblCompanies->currentIndex().row(), 1);
    on_cmdSaveCompany_clicked();
    loadCompanies();
}

void CompanyManager::on_cmdSaveCompany_clicked()
{
    ui->tblCompanies->selectRow(ui->tblCompanies->currentIndex().row());
    if (!model->submitAll())
    {
        int ret = QMessageBox::question(this, qApp->applicationName(),
                                        tr("There is a pending transaction in progress. That cannot be commited now."\
                                           "\nError: %1\n"\
                                           "Perform rollback?").arg(model->lastError().text()),
                                        QMessageBox::Yes, QMessageBox::No);
        if(ret == QMessageBox::Yes)
            model->revertAll();
        model->setPendingTransaction(false);
        return;
    }
    model->setPendingTransaction(false);
    ui->tblCompanies->resizeColumnsToContents();
    ui->tblCompanies->resizeRowsToContents();
}
