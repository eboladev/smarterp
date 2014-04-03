#include "tabularoclinking.h"
#include "ui_tabularoclinking.h"
#include <QMessageBox>
#include <QtSql>
#include "datapublics.h"
TabularOcLinking::TabularOcLinking(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent), db(database),
    ui(new Ui::TabularOcLinking)
{
    ui->setupUi(this);

    model = new SqlTableModel(this, db);

    ui->dtpDate->setDate(QDate::currentDate());
    on_dtpDate_dateChanged(QDate::currentDate());
}

TabularOcLinking::~TabularOcLinking()
{
    delete ui;
}

void TabularOcLinking::on_dtpDate_dateChanged(const QDate &date)
{
    model = new SqlTableModel(this, db);
    model->setSchema("cartons");
    model->setTable("production_manual_allocation");
    model->setFilter("Date = '" + date.toString("yyyy-MM-dd") + "'");
    model->setEditStrategy(SqlTableModel::OnManualSubmit);
    model->select();
    ui->tblAllocation->setModel(model);
    ui->tblAllocation->setColumnHidden(0, true);
    ui->tblAllocation->resizeRowsToContents();
}

void TabularOcLinking::on_cmdPreviousDate_clicked()
{
    ui->dtpDate->setDate(ui->dtpDate->date().addDays(-1));
}

void TabularOcLinking::on_cmdNextDate_clicked()
{
    ui->dtpDate->setDate(ui->dtpDate->date().addDays(1));
}

void TabularOcLinking::on_action_New_triggered()
{
    model->insertRows(model->rowCount(), 1);
    model->setData(model->index(model->rowCount() - 1, 1), ui->dtpDate->date());
    ui->tblAllocation->resizeRowsToContents();
}

void TabularOcLinking::on_action_Save_triggered()
{
    ui->tblAllocation->selectRow(ui->tblAllocation->currentIndex().row());
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
    ui->tblAllocation->resizeRowsToContents();
}

void TabularOcLinking::on_action_Delete_triggered()
{
     model->removeRows(ui->tblAllocation->currentIndex().row(), 1);
}
