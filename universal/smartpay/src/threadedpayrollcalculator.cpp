#include "threadedpayrollcalculator.h"

ThreadedPayrollCalculator::ThreadedPayrollCalculator(QObject *parent, QSqlDatabase database, QString month) :
    QThread(parent)
{

    QSqlDatabase newDb = QSqlDatabase::addDatabase("QMYSQL", "payrollCalculator" + database.databaseName());
    newDb.setDatabaseName(database.databaseName());
    newDb.setUserName(database.userName());
    newDb.setHostName(database.hostName());
    newDb.setPassword(database.password());

    newDb.open();

    db = newDb;

    monthID = month;
}

void ThreadedPayrollCalculator::run()
{
    if (db.isOpen()) {
        int p = 0;
        QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames");
        db.exec("DELETE FROM payroll WHERE MonthID = '" + monthID + "'");
        while (qu.next()) {
            db.exec("CALL RecalculateEmployeeMonth('" + qu.record().value("employeeID").toString() + "', '" + monthID + "')");
            p = p +1;
            emit currentEmployee(qu.record().value("Name").toString());
            emit progress (p);
        }
    }
}
