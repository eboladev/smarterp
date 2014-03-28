#include <QCoreApplication>
#include <QApplication>
#include <QtSql>
#include <QDebug>

#include "datapublics.h"
#include "scheduleprocessor.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Smart Erp";
    qDebug() << "Auto reports queue manager";
    qDebug() << "(c) Panther Technologies Ltd (2012)";
    qDebug() << "====================================";


    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL", "ScheduledReportsConnection");
    bool b = false;
    while (!db.isOpen()) {
         qDebug() << "====================================";
        qDebug() << "Reading database settings from config file...";
        db.setHostName(DataPublics::getIniSetting("hostName"));
        db.setUserName(DataPublics::getIniSetting("userName"));
        db.setDatabaseName("cartons");
        db.setPassword(DataPublics::getIniSetting("password"));

        qDebug() << "Attempting to connect to " + db.userName() + "@" + db.hostName();
        b = db.open();
        if (!b) {
            qWarning() << "Database connection failed. Trying again in a mo.";
        } else {
            qDebug() << "Database connection successful. Starting Shedule Processor...";
        }
    }
    qDebug() << "====================================";
    if (b) {

        ScheduleProcessor *sch  = new ScheduleProcessor(0, db);
        Q_UNUSED(sch);
    } else {
        a.quit();
    }


    return a.exec();
}
