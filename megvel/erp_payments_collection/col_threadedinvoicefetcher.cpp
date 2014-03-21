#include "col_threadedinvoicefetcher.h"

col_ThreadedInvoiceFetcher::col_ThreadedInvoiceFetcher(QObject *parent, QSqlDatabase database, QSqlDatabase QbDatabase) :
    QThread(parent)
{
    db = database;
    odbc_db = QbDatabase;
}

void col_ThreadedInvoiceFetcher::run()
{

    QSqlQuery qu = odbc_db.exec("SELECT * FROM Invoice");
    if (qu.lastError().isValid()) {
        qDebug() << qu.lastError().text();
    } else {

        QString mysqlQuery = "";
        while (qu.next()) {
            QSqlRecord rec = qu.record();

            QDate realInvoiceDate = rec.value("TxnDate").toDate();
            QString newDate = QString::number(realInvoiceDate.year()) + "-" + QString::number(realInvoiceDate.month()) + "-01";


            mysqlQuery.append("INSERT INTO qb_invoices (InvoiceNo, CustomerName, InvoiceDate, "
                              "NewInvoiceDate, PONumber, DueDate, SalesRep, Subtotal, "
                              "SalesTaxPercentage, SalesTaxTotal, AmountPaid, Balance, "
                              "Currency, ExchangeRate, BalanceInHomeCurrency, IsPaid"
                              ") VALUES ('"
                              + rec.value("RefNumber").toString() +  "', '"
                              + rec.value("CustomerRefFullName").toString() +  "', '"
                              + rec.value("TxnDate").toString() +  "', '"
                              + newDate +  "', '"
                              + rec.value("PONumber").toString() +  "', '"
                              + rec.value("DueDate").toString() +  "', '"
                              + rec.value("SalesRepFullName").toString() +  "', '"
                              + rec.value("SubTotal").toString() +  "', '"
                              + rec.value("SalesTaxPercentage").toString() +  "', '"
                              + rec.value("SalesTaxTotal").toString() +  "', '"
                              + rec.value("AppliedAmount").toString() +  "', '"
                              + rec.value("BalanceRemaining").toString() +  "', '"
                              + rec.value("CurrencyRefFullName").toString() +  "', '"
                              + rec.value("ExchangeRate").toString() +  "', '"
                              + rec.value("BalanceRemainingInHomeCurrency").toString() +  "', '"
                              + rec.value("IsPaid").toString() +
                              "');");

            emit currentInv("Downloading Invoice NO: " + rec.value("RefNumber").toString() + "-"  + rec.value("CustomerRefFullName").toString());
        }
        emit currentInv("Saving downloaded data. This may take a while...");
        db.exec("DELETE FROM qb_invoices");
        db.exec(mysqlQuery);
        if (db.lastError().isValid()) {
            qDebug() << db.lastError().text();
        } else {
            db.exec("UPDATE qb_invoices SET `InvoiceTotal` = `Subtotal` + `SalesTaxTotal`");
        }
    }
    emit complete();
}





/*
 *void col_ThreadedInvoiceFetcher::run()
{



    //Get Invoices
    QSqlQuery qu = odbc_db.exec("SELECT * FROM Invoice Invoice");
    if (qu.lastError().isValid()) {
        qDebug() << qu.lastError().text();
    } else {

        QString mysqlQuery = "";
        while (qu.next()) {
            QSqlRecord rec = qu.record();

            QDate realInvoiceDate = rec.value("TxnDate").toDate();
            QString newDate = QString::number(realInvoiceDate.year()) + "-" + QString::number(realInvoiceDate.month()) + "-01";
            QString invoiceAmount = QString::number(rec.value("SubTotal").toDouble() +
                                                    rec.value("SalesTaxTotal").toDouble());

            // mysqlQuery.append("DELETE FROM qb_transactions WHERE TxnNo = '" + rec.value("TxnNumber").toString() + "';");

            emit currentInv("Downloading Invoice NO: " + rec.value("RefNumber").toString() + "-"  + rec.value("CustomerRefFullName").toString());

            QString query = "INSERT INTO qb_transactions (CustomerName, EntryType, "
                    "TxnNo, EntryNo, EntryDate, NewDate, EntryAmount "
                    ") VALUES ('"
                    + rec.value("CustomerRefFullName").toString() +  "', '"
                    + "Invoice', '"
                    + rec.value("TxnNumber").toString() +  "', '"
                    + rec.value("RefNumber").toString() +  "', '"
                    + realInvoiceDate.toString("yyyy-MM-dd") + "', '"
                    + newDate + "', '"
                    + invoiceAmount +
                    "');";

           // db.exec(query);
            mysqlQuery.append(query);
        }

        //Get Credit Memos


        //Get Received Payments


        //Get General Journal Entries



        //Save the data
        emit currentInv("Saving downloaded data. This may take a while...");
        db.exec("DELETE FROM qb_transactions");
               db.exec(mysqlQuery);
               if (db.lastError().isValid()) {
                   qDebug() << db.lastError().text();
               } else {
                  // db.exec("UPDATE qb_invoices SET `InvoiceTotal` = `Subtotal` + `SalesTaxTotal`");
               }
    }
    emit complete();
*/
