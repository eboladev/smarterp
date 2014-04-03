#include "createregister.h"
#include "ui_createregister.h"
#include <QtGui>
#include "datapublics.h"
#include "threadedregister.h"
CreateRegister::CreateRegister(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::CreateRegister)
{
	ui->setupUi(this);
	db = database;
	ui->dtpDate->setDate(QDate::currentDate());
}

CreateRegister::~CreateRegister()
{
	delete ui;
}

void CreateRegister::on_cmdPreview_clicked()
{
	ui->lstPreview->invisibleRootItem()->takeChildren();
	QSqlQuery employeesQuery = db.exec("SELECT * FROM vw_employeenames");
	while (employeesQuery.next()) {
		QString empID = employeesQuery.record().value("EmployeeID").toString();
		QString empName = employeesQuery.record().value("Name").toString();
		QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstPreview);
		it->setText(0, employeesQuery.record().value("#").toString());
		it->setText(1, empName);
		it->setText(2, "No Shift Defined");
		it->setCheckState(0, Qt::Unchecked);
		it->setText(99, empID);
		//Get the shift for this employee for this date
		QSqlQuery timetableQuery = db.exec("SELECT * FROM employees_timetable WHERE employeeID = '" + empID +
						   "' AND Date = '" + ui->dtpDate->date().toString("yyyy-MM-dd") + "'" +
						   " ");
		if (timetableQuery.size() > 0) {
			//Has a timetable entry
			timetableQuery.first();
			QString shiftID = timetableQuery.record().value("ShiftID").toString();
			QString shiftStartTime = DataPublics::getDbValue("SELECT * FROM shifts WHERE ShiftID = '" + shiftID + "'", db, "StartTime").toString();
			QString shiftEndTime = DataPublics::getDbValue("SELECT * FROM shifts WHERE ShiftID = '" + shiftID + "'", db, "EndTime").toString();
			it->setText(2, DataPublics::getDbValue("SELECT * FROM shifts WHERE ShiftID = '" + shiftID + "'", db, "ShiftName").toString());
			it->setText(3, shiftStartTime);
			it->setText(4, shiftEndTime);
			it->setCheckState(0, Qt::Checked);
		} else {
			//Has no timetable entry
		}
	}
}

void CreateRegister::on_cmdSave_clicked()
{
	QStringList employees;
	QStringList dates;
	QStringList inTimes;
	QStringList outTimes;
	for (int i = 0; i < ui->lstPreview->invisibleRootItem()->childCount(); i++ ) {
		if (ui->lstPreview->invisibleRootItem())
			employees.append(ui->lstPreview->invisibleRootItem()->child(i)->text(99));
		dates.append(DataPublics::mysqlDate(ui->dtpDate->date()));
		inTimes.append(ui->lstPreview->invisibleRootItem()->child(i)->text(3));
		outTimes.append(ui->lstPreview->invisibleRootItem()->child(i)->text(4));
	}
	ThreadedRegister *th = new ThreadedRegister(this);
	th->setVars(employees, dates, inTimes, outTimes, db);
	connect (th, SIGNAL(showProgress(int)), ui->prgClockIn, SLOT(setValue(int)));
	th->run();
}
