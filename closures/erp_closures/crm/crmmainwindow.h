#ifndef CRMMAINWINDOW_H
#define CRMMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTableWidgetItem>
namespace Ui {
class CRMMainWindow;
}

class CRMMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CRMMainWindow(QWidget *parent = 0);
    ~CRMMainWindow();
    
private:
    Ui::CRMMainWindow *ui;
    QSqlDatabase db;
    QString customerID;
    QString companyName;
    int current_product_row;
    QString productID;
private slots:
    void reloadCustomers();
    void reloadProducts();
    void reloadOrders();
    void on_trvCustomers_doubleClicked(const QModelIndex &index);
    void on_trvCustomers_clicked(const QModelIndex &index);
    void on_cmdNewCustomer_clicked();
    void on_cmdNewProduct_clicked();
    void on_tblProducts_itemDoubleClicked(QTableWidgetItem *item);
    void on_cmdGenerateJobTicket_clicked();
    void on_tblProducts_itemClicked(QTableWidgetItem *item);
    void on_trvOrders_doubleClicked(const QModelIndex &index);
};

#endif // CRMMAINWINDOW_H
