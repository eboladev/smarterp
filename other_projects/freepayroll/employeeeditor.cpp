#include "employeeeditor.h"
#include "ui_employeeeditor.h"
#include <QInputDialog>
#include "payrollapi.h"
EmployeeEditor::EmployeeEditor(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::EmployeeEditor)
{
	ui->setupUi(this);
	db = QSqlDatabase::database("freepayroll");
	model = new QSqlTableModel(this, db);
	model->setTable("employees");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);
	model->select();

	ui->lstEmployees->setModel(model);
	ui->lstEmployees->setModelColumn(1);


	mapper = new QDataWidgetMapper(this);
	connect (mapper, SIGNAL(currentIndexChanged(int)), SLOT(mapperChanged(int)));
	mapper->setModel(model);
	mapper->addMapping(ui->txtName, model->fieldIndex("Name"));
	mapper->addMapping(ui->txtDOB, model->fieldIndex("DateOfBirth"));
	mapper->addMapping(ui->txtIDNo, model->fieldIndex("IDNo"));
	mapper->toFirst();
}

EmployeeEditor::~EmployeeEditor()
{
	delete ui;
}

#include "startnewemployeedialog.h"
void EmployeeEditor::on_cmdAddNew_clicked()
{
	StartNewEmployeeDialog *ed = new StartNewEmployeeDialog(this);
	if (ed->exec() == QDialog::Accepted) {
		db.exec("INSERT INTO employees(Name) VALUES('"
			+ ed->name + "')");
		if (db.lastError().isValid()) {
			qDebug() << db.lastError().text();
		}
		model->select();
		mapper->toLast();
	}
}

void EmployeeEditor::mapperChanged(int row)
{
	ui->lstEmployees->setCurrentIndex(model->index(row, 1));
	setEmpName();
}

void EmployeeEditor::on_txtLastName_textChanged(const QString &arg1)
{
	ui->lblName->setText(arg1);
}

void EmployeeEditor::on_lstEmployees_activated(const QModelIndex &index)
{
	model->submitAll();
	mapper->setCurrentIndex(index.row());
	setEmpName();
}

void EmployeeEditor::on_lstEmployees_clicked(const QModelIndex &index)
{
	model->submitAll();
	mapper->setCurrentIndex(index.row());
	setEmpName();
}

void EmployeeEditor::setEmpName()
{
	ui->lblName->setText(ui->txtName->text());
}

void EmployeeEditor::on_txtName_textChanged(const QString &arg1)
{
	ui->lblName->setText(arg1);
}

void EmployeeEditor::on_cmdSetDateOfBirth_clicked()
{
	PayrollAPI::setLineEditDate(ui->txtDOB);
	on_cmdSave_clicked();
}

void EmployeeEditor::on_cmdSave_clicked()
{
	model->submitAll();
}
