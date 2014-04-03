#include "threadedmanualclockinout.h"

ThreadedManualClockInOut::ThreadedManualClockInOut(QObject *parent) :
    QThread(parent)
{
}

void ThreadedManualClockInOut::run()
{
    if (!db.isOpen())
        db.open();

    if (db.isOpen()) {
        double empCount = employees.count() - 1;

        for (double i = 0; i <= empCount; i++) {
            QString employeeID = employees.at(i);
            QString employeeName = DataPublics::getDbValue("SELECT Name FROM vw_employeenames WHERE EmployeeID = '" + employeeID + "'", db, "Name").toString();


            QString inOut = "IN";
            if (!in)
                inOut = "OUT";

            QString qu = "DELETE FROM employees_attendance WHERE `Date` = '" + DataPublics::mysqlDate(date) + "' AND `InOut` = '" + inOut + "' AND `EmployeeID` = '" + employeeID + "'";
            ////qDebug() << employeeID << date << time << inOut << qu;
            db.exec(qu);

            qu = tr("INSERT INTO employees_attendance (`EmployeeID`, `Date`,`Time`, `InOut`,  `Closed`) VALUES ('%1', '%2', '%3', '%4', 'No')")
                    .arg(employeeID, DataPublics::mysqlDate(date), time.toString("HH:mm:ss"), inOut);
            ////qDebug() << qu;
            db.exec(qu);
            if (db.lastError().isValid()) {
                //qDebug() << db.lastError().text();
            } else {
               // qDebug () << "OK";
            }

            emit employeeChanged(employeeName);
            //qDebug() << i << empCount <<  (i / empCount) * 100;
            emit showPercentage( (i / empCount) * 100);
        }
        db.close();
    }
}


void ThreadedManualClockInOut::setVars(QSqlDatabase database, QStringList e, QDate d, bool i, QTime t)
{
    db = QSqlDatabase::addDatabase("QMYSQL", "threadManualClockinConnection");
    db.setHostName(database.hostName());
    db.setUserName(database.userName());
    db.setPort(database.port());
    db.setPassword(database.password());
    db.setDatabaseName(database.databaseName());
    db.open();
    //qDebug() << "Thread db open";
    employees = e;
    date = d;
    in = i;
    time = t;
}
