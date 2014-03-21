#include <QApplication>
#include <QtPlugin>
#include "erpmainwindow.h"
#include <QDebug>
//Q_IMPORT_PLUGIN(erp_welcome_screen)
#include <QDebug>
#include <QtSql>

#include "userlogin.h"
// TODO: School Teachers
// TODO: School Students
// TODO: School Library
// TODO: School Timetable
// TODO: School Grading
// TODO: School Attendance
// TODO: School Finance

#include "datapublics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Smart ERP");
    a.setOrganizationName("Panther Technologies");
    a.setApplicationVersion("2.0");
    a.setOrganizationDomain("panthertechno.com");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.0.8");
    db.setUserName("root");
    db.setPassword("pledge");
    db.setDatabaseName("cartons");

    if (db.open()) {
        UserLogin *log = new UserLogin(0, db);
        if (log->exec() == QDialog::Accepted) {
            ERPMainWindow *mW = new ERPMainWindow(0, "megvel", "cartons", log->userID, db);
            mW->userChanged(log->userName);
            mW->showMaximized();
        } else {
            return 0;
        }
    } else {
        DataPublics::showWarning("Connection failed:\n\n" + db.lastError().text());
    }
    return a.exec();
}


