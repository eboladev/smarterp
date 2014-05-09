#ifndef PURCHASEORDERS_H
#define PURCHASEORDERS_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class PurchaseOrders;
}

class PurchaseOrders : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PurchaseOrders(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~PurchaseOrders();
    
private slots:
    void reloadCustomers();
    void reloadOrders();
    void reloadOrderDetails();
    void reloadOCs();
    void on_trvCustomers_clicked(const QModelIndex &index);

    void on_cmdNewLPO_clicked();

    void on_trvOrders_clicked(const QModelIndex &index);

    void on_cmdDownloadLPO_clicked();

    void on_cmdEmailLPO_clicked();

    void on_cmdNewJobTicket_clicked();



    void on_cmdAssignOCs_clicked();

    void on_cmdUploadLPOFile_clicked();

private:
    Ui::PurchaseOrders *ui;
    QSqlDatabase db;
};

#endif // PURCHASEORDERS_H
