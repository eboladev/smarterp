#include "departmenteditor.h"
#include "ui_departmenteditor.h"
#include <QMessageBox>
DepartmentEditor::DepartmentEditor(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DepartmentEditor)
{
	ui->setupUi(this);
	db = QSqlDatabase::database("freepayroll");

	model = new QSqlTableModel(this, db);
	model->setTable("departments");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);
	model->select();

	mapper = new QDataWidgetMapper(this);
	connect (mapper, SIGNAL(currentIndexChanged(int)), SLOT(mapperChanged(int)));
	mapper->setModel(model);
	mapper->addMapping(ui->txtBranchName, model->fieldIndex("DepartmentName"));
	mapper->addMapping(ui->txtDescription, model->fieldIndex("Description"));
	ui->lstDepartments->setModel(model);
	ui->lstDepartments->setModelColumn(1);
	ui->lstDepartments->setModel(model);

	mapper->toFirst();
}

DepartmentEditor::~DepartmentEditor()
{
	delete ui;
}

void DepartmentEditor::on_cmdNewDepartment_clicked()
{
	model->submitAll();
	model->insertRows(model->rowCount(), 1);
	mapper->toLast();
}

void DepartmentEditor::mapperChanged(int row)
{
	ui->lstDepartments->setCurrentIndex(model->index(row, 1));
}

void DepartmentEditor::on_lstDepartments_clicked(const QModelIndex &index)
{
	model->submitAll();
	mapper->setCurrentIndex(index.row());
}

void DepartmentEditor::on_cmdSave_clicked()
{
	model->submitAll();
}

void DepartmentEditor::on_cmdDeleteDepartment_clicked()
{
	if (QMessageBox::question(this, tr("Confirm Delete"), tr("Are you sure you want to delete this %1?").arg("department"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
		return;
	}
	db.exec("DELETE FROM departments WHERE DepartmentID = '" + model->index(mapper->currentIndex(), 0).data().toString() + "'");
	model->select();
	mapper->toFirst();
}
