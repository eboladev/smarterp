#ifndef COL_THREADEDINVOICEFETCHER_H
#define COL_THREADEDINVOICEFETCHER_H

#include <QThread>
#include <QtSql>

class col_ThreadedInvoiceFetcher : public QThread
{
    Q_OBJECT
public:
    explicit col_ThreadedInvoiceFetcher(QObject *parent = 0,
                                        QSqlDatabase database = QSqlDatabase(),
                                        QSqlDatabase QbDatabase = QSqlDatabase());
    void run();
signals:
    void complete();
    void currentInv(QString);
public slots:

private:
    QSqlDatabase db;
    QSqlDatabase odbc_db;
    
};

#endif // COL_THREADEDINVOICEFETCHER_H
