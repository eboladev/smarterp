#ifndef ODBCTOMYSQLIMPORT_H
#define ODBCTOMYSQLIMPORT_H

#include <QtSql>
#include <QTimer>

class ODBCToMysqlImport : public QObject
{
    Q_OBJECT
public:
    explicit ODBCToMysqlImport(QObject *parent = 0);
    void run();
    void prepare();
private:
    QTimer *tmr;
    QSqlDatabase odbcDb;
    QSqlDatabase mysqlDb;
    void openOdbcDb();
    void openMysqlDb();
private slots:
    void on_timer();
signals:
    void error(QString err);
    void message(QString msg);
    void finished();
public slots:
    void process();
};

#endif // ODBCTOMYSQLIMPORT_H
