#include "col_threadedinvoicedatechanger.h"

col_ThreadedInvoiceDateChanger::col_ThreadedInvoiceDateChanger(QObject *parent, QSqlDatabase database, QSqlDatabase QbDatabase) :
    QThread(parent)
{
    db = database;
    odbc_db = QbDatabase;
}

void col_ThreadedInvoiceDateChanger::run()
{
    QSqlQuery qu = odbc_db.exec("SELECT * FROM Invoice Invoice");
    while (qu.next()) {
        QSqlRecord rec = qu.record();

        QDate date = rec.value("DueDate").toDate();
        QString newDate = QString::number(date.year()) + "-" + QString::number(date.month()) + "-01";

        emit currentInv("Current Invoice: " + rec.value("RefNumber").toString());

        QSqlQuery upQu = odbc_db.exec("UPDATE Invoice SET DueDate = '" + newDate + "' WHERE TxnNumber = " + rec.value("TxnNumber").toString());
        if (upQu.lastError().isValid()){
            qDebug() << upQu.lastError().text();
        }
    }

    emit complete();
}
