#ifndef ATTENDANCERECALCULATOR_H
#define ATTENDANCERECALCULATOR_H

#include <QThread>
#include <QObject>
#include <QtSql>
#include <QProgressDialog>

class ThreadedAttendanceCalculator : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedAttendanceCalculator(QObject *parent = 0);
    void run();
    void setVars(QString monthID, QSqlDatabase database);
private:
    QString s_monthID;
    QSqlDatabase db;
};

class AttendanceRecalculator : public QObject
{
    Q_OBJECT
public:
    explicit AttendanceRecalculator(QObject *parent = 0);
    
private:
    QProgressDialog *dg;
signals:
    
public slots:
    
};

#endif // ATTENDANCERECALCULATOR_H
