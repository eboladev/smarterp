
#include <QApplication>
#include <QtSql>
#include "mainwindow.h"
#include "datapublics.h"

#include "payrollcontainer.h"
#include <QFile>
#include <QMessageBox>
#include "smartpayembeddeddatabasemanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQLEMBEDDED", "payrollConnection1");

    db.setHostName("localhost");
    db.setUserName("root");
    //db.setPassword(password);
    db.setDatabaseName("mysql");
    if (db.open()) {
        SmartPayEmbeddedDatabaseManager *sm  = new SmartPayEmbeddedDatabaseManager(0, db);
        if (!sm->checkMaster() || !sm->checkDemoDb()) {
            if (!sm->checkMaster()) {
                qDebug() << "Master database not present. Creating...";
                if (sm->initMaster()) {
                    qDebug() << "Master database successfully created.";
                } else {
                    qDebug() << "Could not create master database";
                    QMessageBox::critical(0, "Database Error", "Could not initialize master database.\n\nThis application cannot work.\n\nPlease contact joejoshw@gmail.com or +254724276654 for support");
                    return 1;
                }
            }
            if (!sm->checkDemoDb()) {
                qDebug() << "Demo database not present. Creating...";
                if (sm->initDemoDb()) {
                    qDebug() << "Demo database successfully created.";
                } else {
                    qDebug() << "Could not create demo database";
                    QMessageBox::critical(0, "Database Error", "Could not initialize demo database.\n\nThis application cannot work.\n\nPlease contact joejoshw@gmail.com or +254724276654 for support");
                    return 1;
                }
            }
        }
        //All databases are ok at this point.
        QSqlDatabase master_db = QSqlDatabase::addDatabase("QMYSQLEMBEDDED", "payrollConnection3");
        master_db.setHostName("localhost");
        master_db.setUserName("root");
        master_db.setDatabaseName("smartpay-master");
        if (master_db.open()) {
            PayrollContainer w(0, master_db, true);
            w.showMaximized();
            return a.exec();
        } else {
            QMessageBox::critical(0, "Database Error", "<h3>Could not connect to database.</h3> <br/>" + master_db.lastError().text());
            return 1;
        }
    } else {
        QMessageBox::critical(0, "Database Error", "<h3>Could not connect to database.</h3> <br/>" + db.lastError().text());
        return 1;
    }

}
