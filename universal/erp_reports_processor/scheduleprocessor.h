#ifndef SCHEDULEPROCESSOR_H
#define SCHEDULEPROCESSOR_H

#include <QObject>
#include <QtSql>
#include <QTimer>
#include <QDateTime>

class ScheduleProcessor : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleProcessor(QObject *parent = 0, QSqlDatabase database = QSqlDatabase());
    
signals:
    
public slots:
    void timeOut();
    void mailer();
private:
    QSqlDatabase db;
    QTimer *tmrSec;
    QTimer *tmrMailer;

};

#endif // SCHEDULEPROCESSOR_H
