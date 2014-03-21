#ifndef THREADEDMANUALCLOCKINOUT_H
#define THREADEDMANUALCLOCKINOUT_H

#include <QThread>
#include <QtSql>
#include "datapublics.h"
#include <QObject>

class ThreadedManualClockInOut : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedManualClockInOut(QObject *parent = 0);
    void run();
    QSqlDatabase db;
    QStringList employees;
    QDate date;
    QTime time;
    bool in;

    void setVars(QSqlDatabase database, QStringList e, QDate d, bool i, QTime t);

signals:
    void showPercentage(int p);
    void employeeChanged(QString eName);
    
public slots:
    
};

#endif // THREADEDMANUALCLOCKINOUT_H
