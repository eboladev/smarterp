#ifndef THREADEDPAYROLLCALCULATOR_H
#define THREADEDPAYROLLCALCULATOR_H

#include <QtSql>
#include <QThread>

class ThreadedPayrollCalculator : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedPayrollCalculator(QObject *parent = 0, QSqlDatabase database = QSqlDatabase(),
                                       QString month = QString());
    void run();
signals:
    void progress(int);
    void currentEmployee(QString);
public slots:
    
private:
    QSqlDatabase db;
    QString monthID;
};

#endif // THREADEDPAYROLLCALCULATOR_H
