#ifndef THREADEDREQUISITIONQUEMANAGER_H
#define THREADEDREQUISITIONQUEMANAGER_H

#include <QThread>
#include <QtSql>
#include <QTimer>

class ThreadedRequisitionQueManager : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedRequisitionQueManager(QObject *parent = 0);
    void run();
private:
    QSqlDatabase db;
    QTimer *tmr;
signals:
    void status(QString state);
public slots:
    void timeout();
};

#endif // THREADEDREQUISITIONQUEMANAGER_H
