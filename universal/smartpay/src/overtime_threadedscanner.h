#ifndef OVERTIME_THREADEDSCANNER_H
#define OVERTIME_THREADEDSCANNER_H

#include <QThread>
#include <QtSql>


class Overtime_ThreadedScanner : public QThread
{
public:
    explicit Overtime_ThreadedScanner(QObject *parent,
            QSqlDatabase database = QSqlDatabase(),
            QString Month = QString()
            );
    void run();
private:
    QString monthID;
    QSqlDatabase db;
};

#endif // OVERTIME_THREADEDSCANNER_H
