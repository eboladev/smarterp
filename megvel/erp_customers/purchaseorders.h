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
	void setDatabase(QSqlDatabase database);
public slots:
	void reloadCustomers();
	void reloadAllOrders();
private slots:
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

	void on_cmdDelete_clicked();


	void on_lstLPOs_clicked(const QModelIndex &index);

private:
	Ui::PurchaseOrders *ui;
	QSqlDatabase db;

	QString customerID;
	QString orderID;
};

#endif // PURCHASEORDERS_H
