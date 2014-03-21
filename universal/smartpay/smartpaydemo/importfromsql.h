#ifndef IMPORTFROMSQL_H
#define IMPORTFROMSQL_H

#ifdef WIN32
    #include <Qtcore/qt_windows.h>
#endif

#include <QtSql>
#include <QObject>
#include <QThread>
#include <QProgressDialog>
#include "mysql.h"

class ThreadedImporter : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedImporter(QObject *parent = 0,QSqlDatabase mysql = QSqlDatabase(),QString fileName = QString());
    void run();
signals:
    void progress(int p);
    void minMax(quint64 min, quint64 max);
    void error(QString err);
    void status(QString s);
private:
    QSqlDatabase db;
    QString fName;
    void runQuery(QString q);
    MYSQL mysql;
};

class ImportFromSQL : public QObject
{
    Q_OBJECT
public:
    explicit ImportFromSQL(QObject *parent = 0, QString fileName = QString(),QSqlDatabase mysql =  QSqlDatabase());
signals:
    void complete();
public slots:
    void threadProgress(int p);
    void threadStatus(QString s);
    void threadMinMax(quint64 min, quint64 max);
    void error(QString err);
private:
    QProgressDialog *prg;
    QString fName;
};

#endif // IMPORTFROMSQL_H
