#include "brancheditor.h"
#include "ui_brancheditor.h"
#include <QMessageBox>
BranchEditor::BranchEditor(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::BranchEditor)
{
	ui->setupUi(this);
	db = QSqlDatabase::database("freepayroll");

	model = new QSqlTableModel(this, db);
	model->setTable("branches");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);
	model->select();

	mapper = new QDataWidgetMapper(this);
	connect (mapper, SIGNAL(currentIndexChanged(int)), SLOT(mapperChanged(int)));
	mapper->setModel(model);
	mapper->addMapping(ui->txtBranchName, model->fieldIndex("BranchName"));
	mapper->addMapping(ui->txtDescription, model->fieldIndex("Description"));
	ui->lstBranches->setModel(model);
	ui->lstBranches->setModelColumn(1);
	ui->lstBranches->setModel(model);

	mapper->toFirst();
}

BranchEditor::~BranchEditor()
{
	delete ui;
}

void BranchEditor::on_cmdNewBranch_clicked()
{
	model->submitAll();
	model->insertRows(model->rowCount(), 1);
	mapper->toLast();
}

void BranchEditor::mapperChanged(int row)
{
	ui->lstBranches->setCurrentIndex(model->index(row, 1));
}

void BranchEditor::on_lstBranches_clicked(const QModelIndex &index)
{
	model->submitAll();
	mapper->setCurrentIndex(index.row());
}

void BranchEditor::on_cmdSave_clicked()
{
	model->submitAll();
}

void BranchEditor::on_cmdDeleteBranch_clicked()
{
	if (QMessageBox::question(this, tr("Confirm Delete"), tr("Are you sure you want to delete this %1?").arg("branch"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
		return;
	}
	db.exec("DELETE FROM branches WHERE BranchID = '" + model->index(mapper->currentIndex(), 0).data().toString() + "'");
	model->select();
	mapper->toFirst();
}
