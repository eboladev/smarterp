#include "odbctomysqlimport.h"
#include "settingsmanager.h"
ODBCToMysqlImport::ODBCToMysqlImport(QObject *parent) :
	QObject(parent)
{
}

void ODBCToMysqlImport::run()
{

}

void ODBCToMysqlImport::prepare()
{
	odbcDb =  QSqlDatabase::addDatabase("QODBC","ODBCTHREADDB");
	mysqlDb = QSqlDatabase::addDatabase("QMYSQL", "MYSQLTHREADDB");

	openOdbcDb();
	openMysqlDb();
}

void ODBCToMysqlImport::openOdbcDb()
{

	SettingsManager *sett = new SettingsManager(this);
	odbcDb.setDatabaseName(sett->odbcDataSource());
	odbcDb.setHostName("127.0.0.1");

	if (!odbcDb.open()) {
		emit error("Hand Punch Database ERROR: " + odbcDb.lastError().text());
	} else {
		emit message("Hand Punch Database successfully opened.");
	}
}

void ODBCToMysqlImport::openMysqlDb()
{

	SettingsManager *sett = new SettingsManager(this);
	mysqlDb.setDatabaseName(sett->mysqlDatabaseName());
	mysqlDb.setHostName(sett->mysqlHostName());
	mysqlDb.setUserName(sett->mysqlUserName());
	mysqlDb.setPassword(sett->mysqlPassword());
	mysqlDb.setDatabaseName(sett->mysqlDatabaseName());

	if (!mysqlDb.open()) {
		emit error("Payroll Database ERROR: " + mysqlDb.lastError().text());
	} else {
		emit message("Payroll Database successfully opened.");
	}
}

void ODBCToMysqlImport::on_timer()
{
	if (!mysqlDb.isOpen()) {
		emit error("Hand Punch Database not open. Reconnecting...");
		openMysqlDb();
		return;
	}

	if (!odbcDb.isOpen()) {
		emit error("Payroll Database not open. Reconnecting...");
		openOdbcDb();
		return;
	}

	if (odbcDb.isOpen() && mysqlDb.isOpen()) {
		//All ok...fetch data
		emit message("Checking for new records...");
		QSqlQuery odQu = odbcDb.exec("SELECT * FROM tblRacData Where Posted != 1  ORDER BY RacDataTrnCode");
		if (odQu.lastError().isValid()) {
			emit error("Hand Punch Database Error: " + odQu.lastError().text());
		} else {
			int count = 0;
			while (odQu.next()) {
				QSqlRecord rec = odQu.record();
				QString empNo = rec.value("EnrollMentNo").toString();
				QString entryID = rec.value("RacDataTrnCode").toString();
				QDate date = rec.value("IDDateTime").toDate();
				QTime time = rec.value("IDDateTime").toTime();
				QString inOut = rec.value("InOut").toString();

				// emit message(empNo + "-" + entryID + "-" + date.toString()  + "-" + time.toString() + "-" + inOut);

				int emp_no = empNo.toInt();

				QString dbName = "smartpay-megvel";

				if (emp_no < 300)
					dbName = "smartpay-lupra";

				if (emp_no > 599)
					dbName = "smartpay-closures";

				QSqlQuery ins_qu =  mysqlDb.exec("INSERT INTO `" + dbName + "`.biometric_attendance ("
								 "`Date`, "
								 "`Time`, "
								 "`StaffNo`, "
								 "`InOut`, "
								 "`EndeavourID`"
								 ")"
								 " VALUES ('" +
								 date.toString("yyyy-MM-dd") + "', '" +
								 time.toString("HH:mm:ss")+ "', '" +
								 empNo + "', '" +
								 inOut + "', '" +
								 entryID + "')");

				if (ins_qu.lastError().isValid()) {
					emit error("Insert Error: " + ins_qu.lastError().text());
				} else {
					odbcDb.exec("UPDATE tblRacData SET Posted = 1 WHERE RacDataTrnCode = '" + entryID + "'");
					count ++;
				}
			}
			emit message(QString::number(count) + " records inserted.");
		}
	}
}

void ODBCToMysqlImport::process()
{
	prepare();
	//    tmr = new QTimer(this);
	//    connect (tmr, SIGNAL(timeout()), SLOT(on_timer()));
	//    tmr->start(30000);
	on_timer();
}
