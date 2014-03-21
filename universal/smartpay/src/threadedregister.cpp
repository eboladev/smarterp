#include "threadedregister.h"

ThreadedRegister::ThreadedRegister(QObject *parent) :
    QThread(parent)
{
    Q_UNUSED(parent);
}

void ThreadedRegister::run()
{
    double allEmployees = e.count();
    for (double i = 0; i < e.count(); i++) {
        emit showProgress((i / allEmployees) *100);
        QString employeeID = e.at(i);
        QString inTime = ins.at(i);
        QString outTime = outs.at(i);
        QString date = ds.at(i);
        db.exec("DELETE FROM employees_attendance WHERE employeeID = '" + employeeID + "' AND Date = '" + date + "'");
        db.exec("INSERT INTO employees_attendance(`EmployeeID`, `Date`, `Time`, `InOut`, `Closed`) VALUES ('"
                + employeeID + "', '"
                + date  + "', '"
                + inTime + "', '"
                + "In" + "', '"
                + "No')");
        if (db.lastError().isValid())
            //qDebug() << db.lastError().text();

        db.exec("INSERT INTO employees_attendance(`EmployeeID`, `Date`, `Time`, `InOut`, `Closed`) VALUES ('"
                + employeeID + "', '"
                + date  + "', '"
                + outTime + "', '"
                + "Out" + "', '"
                + "No')");
        //if (db.lastError().isValid())
            //qDebug() << db.lastError().text();
    }
    db.close();
    emit showProgress(100);
}

void ThreadedRegister::setVars(QStringList employees, QStringList dates, QStringList inTimes, QStringList outTimes, QSqlDatabase d)
{
    db = QSqlDatabase::addDatabase("QMYSQL", "threadRegisterConnection");
    db.setHostName(d.hostName());
    db.setUserName(d.userName());
    db.setPort(d.port());
    db.setPassword(d.password());
    db.setDatabaseName(d.databaseName());
    db.open();
    //qDebug() << "Thread db open";

    e = employees;
    ins = inTimes;
    outs = outTimes;
    ds = dates;
}
