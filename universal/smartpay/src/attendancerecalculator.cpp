#include "attendancerecalculator.h"
#include "datapublics.h"
AttendanceRecalculator::AttendanceRecalculator(QObject *parent) :
	QObject(parent)
{
	// dg = new QProgressDialog(this);
	//  dg->setMinimum(0);
	//  dg->setMaximum(100);
	//  dg->show();
	//dg = new QProgressDialog(this);
	//dg->setMinimum(0);
	//dg->setMaximum(100);
	//dg->show();
}


ThreadedAttendanceCalculator::ThreadedAttendanceCalculator(QObject *parent)
{
	Q_UNUSED(parent);
}

void ThreadedAttendanceCalculator::run()
{
	QString s_monthEnd = DataPublics::getDbValue("SELECT EndDate FROM months WHERE MonthID = '" + s_monthID + "'", db, "StartDate").toString();
	QString s_monthStart = DataPublics::getDbValue("SELECT StartDate FROM months WHERE MonthID = '" + s_monthID + "'", db, "StartDate").toString();

	// QSqlQuery qu = db.exec("SELECT ")
}

void ThreadedAttendanceCalculator::setVars(QString monthID, QSqlDatabase database)
{
	db = QSqlDatabase::addDatabase("QMYSQL", "ThreadedAttendanceCalculator");
	db.setHostName(database.hostName());
	db.setUserName(database.userName());
	db.setPassword(database.password());
	db.setPort(database.port());
	db.setDatabaseName(database.databaseName());
	db.open();

	s_monthID = monthID;
}
