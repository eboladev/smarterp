#include "cooperatives.h"
#include "ui_cooperatives.h"
#include <QMessageBox>
CooperativeEditor::CooperativeEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CooperativeEditor)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("freepayroll");

    model = new QSqlTableModel(this, db);
    model->setTable("cooperatives");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    mapper = new QDataWidgetMapper(this);
    connect (mapper, SIGNAL(currentIndexChanged(int)), SLOT(mapperChanged(int)));
    mapper->setModel(model);
    mapper->addMapping(ui->txtCooperative, model->fieldIndex("CooperativeName"));
    mapper->addMapping(ui->txtDescription, model->fieldIndex("Description"));
    ui->lstCooperatives->setModel(model);
    ui->lstCooperatives->setModelColumn(1);
    ui->lstCooperatives->setModel(model);

    mapper->toFirst();
}

CooperativeEditor::~CooperativeEditor()
{
    delete ui;
}

void CooperativeEditor::on_cmdNewCooperative_clicked()
{
    model->submitAll();
    model->insertRows(model->rowCount(), 1);
    mapper->toLast();
}

void CooperativeEditor::mapperChanged(int row)
{
    ui->lstCooperatives->setCurrentIndex(model->index(row, 1));
}

void CooperativeEditor::on_lstCooperatives_clicked(const QModelIndex &index)
{
    model->submitAll();
    mapper->setCurrentIndex(index.row());
}

void CooperativeEditor::on_cmdSave_clicked()
{
    model->submitAll();
}

void CooperativeEditor::on_cmdDeleteCooperative_clicked()
{
    if (QMessageBox::question(this, tr("Confirm Delete"), tr("Are you sure you want to delete this %1?").arg("cooperative"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
        return;
    }
    db.exec("DELETE FROM cooperatives WHERE CooperativeID = '" + model->index(mapper->currentIndex(), 0).data().toString() + "'");
    model->select();
    mapper->toFirst();
}
