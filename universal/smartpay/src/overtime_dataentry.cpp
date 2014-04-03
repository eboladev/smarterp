#include "overtime_dataentry.h"
#include "ui_overtime_dataentry.h"

Overtime_DataEntry::Overtime_DataEntry(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Overtime_DataEntry)
{
	ui->setupUi(this);
	db = database;
	ui->dtpDate->setDate(QDate::currentDate());
	refreshOt();
}

Overtime_DataEntry::~Overtime_DataEntry()
{
	delete ui;
}

void Overtime_DataEntry::on_dtpDate_dateChanged(const QDate &date)
{
	Q_UNUSED(date);
	refreshOt();
}

#include "calendarwidget.h"
void Overtime_DataEntry::refreshOt()
{
	otModel = new QSqlRelationalTableModel(this, db);
	otModel->setTable("overtime_dataentry");

	QSqlRelation rel("vw_employeenames_ex", "employeeID", "Name");
	otModel->setRelation(1, rel);

	QSqlRelation rel2("vw_shifts", "ShiftID", "ShiftName");
	otModel->setRelation(2, rel2);
	otModel->select();
	otModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

	ui->tblData->setModel(otModel);
	ui->tblData->setColumnHidden(0, true);
	ui->tblData->setItemDelegate(new QSqlRelationalDelegate(ui->tblData));
	ui->tblData->setItemDelegateForColumn(3, new CalendarWidget(this));

	ui->tblData->resizeColumnsToContents();
	ui->tblData->resizeRowsToContents();
	reformatDates();
}

void Overtime_DataEntry::on_cmdNew_clicked()
{
	int r = otModel->rowCount();
	otModel->insertRow(r);
	QModelIndex index = otModel->index(r, 3);
	otModel->setData(index, ui->dtpDate->date().toString(), Qt::EditRole);
	ui->tblData->resizeColumnsToContents();
	ui->tblData->resizeRowsToContents();
}

void Overtime_DataEntry::on_cmdSave_clicked()
{
	otModel->submitAll();
	ui->tblData->resizeColumnsToContents();
	ui->tblData->resizeRowsToContents();
	reformatDates();
}

void Overtime_DataEntry::reformatDates()
{
	for (int i = 0; i < otModel->rowCount(); i++) {
		QDate dat = otModel->data(otModel->index(i, 3)).toDate();
		otModel->setData(otModel->index(i, 3), dat.toString("yyyy-MMM-dd"));
	}
}
