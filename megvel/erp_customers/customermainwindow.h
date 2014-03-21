#ifndef CUSTOMERMAINWINDOW_H
#define CUSTOMERMAINWINDOW_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
#include <QMainWindow>
#include "lgmqueue.h"

class Customers;
class ProductsApproval;
class PurchaseOrders;
class ProformaList;
class OcRegister;

namespace Ui {
class CustomerMainWindow;
}

class CustomerMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CustomerMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CustomerMainWindow();
private:
    Ui::CustomerMainWindow *ui;
    QSqlDatabase db;
    LGMQueue *queue;

    Customers *cust;
    ProductsApproval *prod;
    PurchaseOrders *lpos;
    ProformaList *prof;
    OcRegister *ocs;

    bool isQc;

private slots:
    void receiveDb(QSqlDatabase database);
    void pageChanged(QString newPage);
};

#endif // CUSTOMERMAINWINDOW_H
