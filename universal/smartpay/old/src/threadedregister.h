#ifndef THREADEDREGISTER_H
#define THREADEDREGISTER_H

#include <QThread>
#include <QtSql>
#include <QDate>

class ThreadedRegister : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedRegister(QObject *parent = 0);
    void run();
    void setVars(QStringList employees, QStringList dates,
                 QStringList inTimes, QStringList outTimes, QSqlDatabase d);
signals:
    void showProgress(int);
    void employeeChanged(QString);
    void dateChanged(QDate);
public slots:
    
private:
    QSqlDatabase db;
    QStringList e, ds, ins, outs;
};

#endif // THREADEDREGISTER_H
