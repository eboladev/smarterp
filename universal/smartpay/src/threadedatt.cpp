#include "threadedatt.h"
#include "hourcalculator.h"
#include "publics.h"



void ThreadedAtt::run() {
    if (db.isOpen()) {
        int empCount = employees.count();
        int days = startDate.daysTo(endDate);
        for (int i = 0; i < empCount; i++) {
            QString employeeID = employees.at(i);
            for (int d = 0; d < days; d++) {
                QDate dat = startDate.addDays(d);
                HourCalculator::CalculateAttendanceForDay(Publics::getDateString(dat), employeeID, db);
                perc = ( d / days) * 100;

                //qDebug() << perc;
                emit showPercentage(perc);
            }            
        }
    }
    db.close();
    return;
}

void ThreadedAtt::setVars(QSqlDatabase d, QStringList e, QDate sD, QDate eD, int p)
{
    db = QSqlDatabase::addDatabase("QMYSQL", "threadTimeTableConnection");
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

ThreadedAtt::ThreadedAtt(QObject *parent)
{
    Q_UNUSED(parent);
}

ThreadedAtt::~ThreadedAtt()
{
}
