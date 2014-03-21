#include "pastentriesdialog.h"
#include "ui_pastentriesdialog.h"
#include "datapublics.h"
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>

PastEntriesDialog::PastEntriesDialog(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::PastEntriesDialog)
{
    ui->setupUi(this);
    db = database;

    model = new QSqlQueryModel(this);
    filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(model);
    filterModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui->tblResults->setModel(filterModel);
}

PastEntriesDialog::~PastEntriesDialog()
{
    delete ui;
}

void PastEntriesDialog::on_cmdSearch_clicked()
{
    QString query =
            "SELECT `Ticket No`, `Date`, `Client`, Product, `Invoice #`, "
            "`Dispatched Qty`, `Delivery Mode`, Comments, Confirmed "
            "FROM vw_alldispatch "
            " WHERE "
            "`Ticket No` LIKE '%" + ui->txtSearch->text() + "%' OR "
            "`Date` LIKE '%" + ui->txtSearch->text() + "%' OR "
            "`Client` LIKE '%" + ui->txtSearch->text() + "%' OR "
            "Product LIKE '%" + ui->txtSearch->text() + "%' OR "
            "`Invoice #` LIKE '%" + ui->txtSearch->text() + "%' OR "
            "`Dispatched Qty` LIKE '%" + ui->txtSearch->text() + "%' OR "
            "`Delivery Mode` LIKE '%" + ui->txtSearch->text() + "%' OR "
            "Comments LIKE '%" + ui->txtSearch->text() + "%' OR "
            "Confirmed LIKE '%" + ui->txtSearch->text() + "%' Order by DispatchID DESC";

    qDebug() << query;

    filterModel = new QSortFilterProxyModel(this);
    model->setQuery(query, db);
    filterModel->setSourceModel(model);
    filterModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    filterModel->setFilterKeyColumn(-1);
    ui->tblResults->setModel(filterModel);

    ui->tblResults->resizeColumnsToContents();
    ui->tblResults->resizeRowsToContents();
}
