#include "overtime_entryscan.h"
#include "ui_overtime_entryscan.h"

Overtime_EntryScan::Overtime_EntryScan(QWidget *parent, QSqlDatabase database, QString Month) :
	QDialog(parent),
	ui(new Ui::Overtime_EntryScan)
{
	ui->setupUi(this);
	db = database;
	monthID = Month;
}

Overtime_EntryScan::~Overtime_EntryScan()
{
	delete ui;
}
