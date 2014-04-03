#ifndef QUEUEPROCESSOR_H
#define QUEUEPROCESSOR_H

#include <QThread>
#include <QtSql>
#include <QTimer>

class QueueProcessor : public QThread
{
    Q_OBJECT
public:
    explicit QueueProcessor(QObject *parent = 0, QSqlDatabase database = QSqlDatabase());
    void run();
signals:
    
public slots:
    void timeOut();
private:
    QSqlDatabase db;
    QTimer *tmr;
    bool running;
};

#endif // QUEUEPROCESSOR_H
