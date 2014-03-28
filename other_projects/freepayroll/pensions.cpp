#include "pensions.h"
#include "ui_pensions.h"
#include <QMessageBox>
PensionEditor::PensionEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PensionEditor)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("freepayroll");

    model = new QSqlTableModel(this, db);
    model->setTable("pensions");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    mapper = new QDataWidgetMapper(this);
    connect (mapper, SIGNAL(currentIndexChanged(int)), SLOT(mapperChanged(int)));
    mapper->setModel(model);
    mapper->addMapping(ui->txtPension, model->fieldIndex("PensionName"));
    mapper->addMapping(ui->txtDescription, model->fieldIndex("Description"));
    ui->lstPensions->setModel(model);
    ui->lstPensions->setModelColumn(1);
    ui->lstPensions->setModel(model);

    mapper->toFirst();
}

PensionEditor::~PensionEditor()
{
    delete ui;
}

void PensionEditor::on_cmdNewPension_clicked()
{
    model->submitAll();
    model->insertRows(model->rowCount(), 1);
    mapper->toLast();
}

void PensionEditor::mapperChanged(int row)
{
    ui->lstPensions->setCurrentIndex(model->index(row, 1));
}

void PensionEditor::on_lstPensions_clicked(const QModelIndex &index)
{
    model->submitAll();
    mapper->setCurrentIndex(index.row());
}

void PensionEditor::on_cmdSave_clicked()
{
    model->submitAll();
}

void PensionEditor::on_cmdDeletePension_clicked()
{
    if (QMessageBox::question(this, tr("Confirm Delete"), tr("Are you sure you want to delete this %1?").arg("pension"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
        return;
    }
    db.exec("DELETE FROM pensions WHERE PensionID = '" + model->index(mapper->currentIndex(), 0).data().toString() + "'");
    model->select();
    mapper->toFirst();
}
