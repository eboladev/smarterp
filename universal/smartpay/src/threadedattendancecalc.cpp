#include "threadedattendancecalc.h"
#include "hourcalculator.h"
#include "publics.h"

#include <QDate>

ThreadedAttendanceCalc::ThreadedAttendanceCalc(QObject *parent) :
	QThread(parent)
{
	Q_UNUSED(parent);
}


void ThreadedAttendanceCalc::run() {
	if (db.isOpen()) {
		double empCount = employees.count();
		double days = startDate.daysTo(endDate);

		double totalDays = days * empCount;
		double d2 = 0;

		for (double i = 0; i < empCount; i++) {
			QString employeeID = employees.at(i);
			QString employeeName = Publics::getDbValue(db, "SELECT Name FROM vw_employeenames WHERE EmployeeID = '" + employeeID + "'", "Name");
			emit employeeChanged(employeeName);
			for (double d = 0; d < days; d++) {
				d2 = d2 + 1;
				QDate dat = startDate.addDays(d);
				emit dateChanged(dat.toString("dd-MMM-yyyy"));
				HourCalculator::CalculateAttendanceForDay(Publics::getDateString(dat), employeeID, db);

				perc = ( (d+1) /days) * 100;
				double pPerc = (d2 / totalDays) * 100;
				emit showPercentage(pPerc);
				emit showEmployeePercentage(perc);
			}
		}
	}
	db.close();
	return;
}

void ThreadedAttendanceCalc::setVars(QSqlDatabase d, QStringList e, QDate sD, QDate eD, int p)
{
	db = QSqlDatabase::addDatabase("QMYSQL", "threadAttendanceCalcConnection");
	db.setHostName(d.hostName());
	db.setUserName(d.userName());
	db.setPort(d.port());
	db.setPassword(d.password());
	db.setDatabaseName(d.databaseName());
	db.open();
	//qDebug() << "Thread db open";
	employees  = e;
	startDate = sD;
	endDate = eD;
	perc = p;
}
