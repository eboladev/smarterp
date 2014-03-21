#include <QCoreApplication>
#include <QtSql>

#include "qmysqlembeddeddriver.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    qDebug() << "Available Drivers: " << QSqlDatabase::drivers();

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQLEMBEDDED", "embededConnectionTest");

    db.setDatabaseName("mysql");
    if (db.open()) {
        qDebug() << "Embedded database open.";
        QSqlQuery qu = db.exec("SHOW databases");
        QStringList lst;
        if (qu.lastError().isValid()) {
            qDebug() << qu.lastError().text();
        } else {
            while (qu.next()) {
                lst << qu.record().value(0).toString();
            }
            qDebug() << lst;
            if (!lst.contains("smartpay-master")) {
                QFile f(qApp->applicationDirPath() + QDir::separator() + "sqls" + QDir::separator() + "smartpay_master.sql");
                if (f.open(QIODevice::ReadOnly)) {
                    QString fData = f.readAll();
                    f.close();
                    QStringList sqls = fData.split("\r\n\r\n");
                    for (int i = 0; i < sqls.count(); i++) {
                        QString sql = sqls.at(i);
                        db.exec(sql);
                        if (db.lastError().isValid()) {
                            qDebug() << db.lastError().text();
                        } else {
                            qDebug() << sql;
                        }

                    }
                    qDebug() << "Successfully Created smartpay-master database";
                } else {
                    qDebug() << "Could not open script file.";
                }
            } else {
                db.exec("DROP smartpay-master");
            }
           // db.close();
           // db.open();
        }
    } else {
        qDebug() << "Database not open." << db.lastError().text();
    }

    return a.exec();
}
