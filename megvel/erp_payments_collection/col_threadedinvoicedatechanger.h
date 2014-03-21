#ifndef COL_THREADEDINVOICEDATECHANGER_H
#define COL_THREADEDINVOICEDATECHANGER_H

#include <QThread>
#include <QtSql>
class col_ThreadedInvoiceDateChanger : public QThread
{
    Q_OBJECT
public:
    explicit col_ThreadedInvoiceDateChanger(QObject *parent = 0,
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

#endif // COL_THREADEDINVOICEDATECHANGER_H
