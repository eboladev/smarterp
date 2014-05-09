#include "machines.h"
#include "ui_machines.h"

Machines::Machines(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Machines)
{
    ui->setupUi(this);
    reloadMachines();

    connect (ui->action_New_Machine, SIGNAL(triggered()), this, SLOT(newRow()));
}

Machines::~Machines()
{
    delete ui;
}

void Machines::newRow()
{
    model->insertRow(model->rowCount());
    QModelIndex index = model->index(model->rowCount() - 1, 1);
    model->setData(index, "Machine " + QString::number(model->rowCount()));
    model->setData(index, "Machine " + QString::number(model->rowCount()), Qt::DisplayRole);
    model->submitAll();

    reloadMachines();
}

void Machines::reloadMachines()
{
    model = new QSqlTableModel(this, QSqlDatabase::database("closures"));
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("machines");
    model->setFilter("deleted='false'");

    model->setHeaderData(1, Qt::Horizontal, "Machine Name", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal,  "Machine Code", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal,  "Manufacturer", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal,  "Comments", Qt::DisplayRole);

    model->select();
    ui->tblMachines->setModel(model);
    ui->tblMachines->setColumnHidden(0, true);
    ui->tblMachines->setColumnHidden(5, true);
}

void Machines::on_actionRefresh_triggered()
{
    reloadMachines();
}

void Machines::on_cmdDelete_clicked()
{
    QModelIndex index =
            model->index(ui->tblMachines->currentIndex().row()
                         , 5);
    model->setData(index, "true");
    reloadMachines();

}
