#include "attendance_newdaterange.h"
#include "ui_attendance_newdaterange.h"

Attendance_NewDateRange::Attendance_NewDateRange(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Attendance_NewDateRange)
{
	ui->setupUi(this);
	ui->dtpDateIn->setDate(QDate::currentDate());
	ui->dtpDateOut->setDate(QDate::currentDate());

	connect (ui->dtpDateIn, SIGNAL(dateChanged(QDate)), SLOT(DateChange()));
	connect (ui->dtpDateOut, SIGNAL(dateChanged(QDate)), SLOT(DateChange()));
}

Attendance_NewDateRange::~Attendance_NewDateRange()
{
	delete ui;
}

void Attendance_NewDateRange::DateChange()
{
	dateIn = ui->dtpDateIn->date();
	dateOut = ui->dtpDateOut->date();
}
