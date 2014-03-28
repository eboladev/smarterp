#include "smartpayembeddeddatabasemanager.h"
#include <QDebug>

SmartPayEmbeddedDatabaseManager::SmartPayEmbeddedDatabaseManager(QObject *parent, QSqlDatabase database) :
    QObject(parent)
{
    db = database;
}

bool SmartPayEmbeddedDatabaseManager::checkMaster()
{
    qDebug() << "Checking for master connection.";
    QSqlQuery qu = db.exec("SHOW databases");
    if (qu.lastError().isValid())
        return false;

    while (qu.next()) {
        if (qu.record().value(0).toString() == "smartpay-master")
            return true;
    }
    return false;
}

bool SmartPayEmbeddedDatabaseManager::checkDemoDb()
{
    qDebug() << "Checking for demo database connection.";
    QSqlQuery qu = db.exec("SHOW databases");
    if (qu.lastError().isValid())
        return false;

    while (qu.next()) {
        if (qu.record().value(0).toString() == "smartpay_demo")
            return true;
    }
    return false;
}

bool SmartPayEmbeddedDatabaseManager::initMaster()
{
    qDebug() << "Initializing master connection." ;
    return runSqlScript("smartpay_master.sql", "smartpay-master");
}

bool SmartPayEmbeddedDatabaseManager::initDemoDb()
{
    qDebug() << "Initializing demo database." ;
    return runSqlScript("smartpay_demo.sql", "smartpay_demo");
}

#include "importfromsql.h"
bool SmartPayEmbeddedDatabaseManager::runSqlScript(QString scriptName, QString dbName)
{
    QString fName = qApp->applicationDirPath() + QDir::separator() + "sqls" + QDir::separator() + scriptName;
    ImportFromSQL *imp = new ImportFromSQL(this, fName, db);
 //   QFile f(fName);
//    if (f.open(QIODevice::ReadOnly)) {
//        QString fData = f.readAll();
//        f.close();
//        QStringList sqls = fData.split(";");
//        for (int i = 0; i < sqls.count(); i++) {
//            QString sql = sqls.at(i);
//            db.exec(sql);
//            if (db.lastError().isValid()) {
//                qDebug() << db.lastError().text();
//            } else {
//                qDebug() << sql;
//            }
//        }
//        return true;
//    } else {
//        db.exec("DROP DATABASE " + dbName);
//        qDebug() << "Could not open script file.";
//        return false;
    //    }
}

void SmartPayEmbeddedDatabaseManager::threadsFinished()
{
    //
}
