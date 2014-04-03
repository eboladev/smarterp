#include "jobgroupeditor.h"
#include "ui_jobgroupeditor.h"
#include <QMessageBox>
JobGroupEditor::JobGroupEditor(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::JobGroupEditor)
{
	ui->setupUi(this);
	db = QSqlDatabase::database("freepayroll");

	model = new QSqlTableModel(this, db);
	model->setTable("jobgroups");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);
	model->select();

	mapper = new QDataWidgetMapper(this);
	connect (mapper, SIGNAL(currentIndexChanged(int)), SLOT(mapperChanged(int)));
	mapper->setModel(model);
	mapper->addMapping(ui->txtJobGroup, model->fieldIndex("JobGroupName"));
	mapper->addMapping(ui->txtDescription, model->fieldIndex("Description"));
	ui->lstJobGroups->setModel(model);
	ui->lstJobGroups->setModelColumn(1);
	ui->lstJobGroups->setModel(model);

	mapper->toFirst();
}

JobGroupEditor::~JobGroupEditor()
{
	delete ui;
}

void JobGroupEditor::on_cmdNewJobGroup_clicked()
{
	model->submitAll();
	model->insertRows(model->rowCount(), 1);
	mapper->toLast();
}

void JobGroupEditor::mapperChanged(int row)
{
	ui->lstJobGroups->setCurrentIndex(model->index(row, 1));
}

void JobGroupEditor::on_lstJobGroups_clicked(const QModelIndex &index)
{
	model->submitAll();
	mapper->setCurrentIndex(index.row());
}

void JobGroupEditor::on_cmdSave_clicked()
{
	model->submitAll();
}

void JobGroupEditor::on_cmdDeleteJobGroup_clicked()
{
	if (QMessageBox::question(this, tr("Confirm Delete"), tr("Are you sure you want to delete this %1?").arg(" job group"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
		return;
	}
	db.exec("DELETE FROM jobgroups WHERE JobGroupID = '" + model->index(mapper->currentIndex(), 0).data().toString() + "'");
	model->select();
	mapper->toFirst();
}
