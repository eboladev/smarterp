#include <QApplication>

#include <QtSql>
#include "imsmainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("pledge");
    db.setDatabaseName("ims");

    ImsMainWindow *ims = new ImsMainWindow(0, db);
    ims->show();

    return a.exec();
}
