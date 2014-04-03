#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QMainWindow>
#include <QtSql>

#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QTimer>

#include "productsmodel.h"
#include "customersmodel.h"
#include "QSortFilterProxyModel"
namespace Ui {
class Customers;
}

class Customers : public QMainWindow
{
	Q_OBJECT
public:
	explicit Customers(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase()
			);
	~Customers();


public slots:
	void reloadCustomers();
private slots:
	void currentProductChanged(QModelIndex newIndex ,QModelIndex oldIndex);
	void reloadProducts();
	void reloadOrders();
	void customerChanged();
	void on_cmdNewCustomer_clicked();
	void on_cmdNewProduct_clicked();
	void editProduct(QString m_productID);
	void on_cmdGenerateJobTicket_clicked();

	void on_cmdProforma_clicked();
	void keepDbAlive();
	void reconnectDb();

	void on_lblExport_linkActivated(const QString &link);

	void on_tblProducts_clicked(const QModelIndex &index);

	void on_tblProducts_doubleClicked(const QModelIndex &index);

	void currentCustomerChanged(QModelIndex newRow, QModelIndex oldRow);
	void on_trvOrders_doubleClicked(const QModelIndex &index);

	void on_cmdCostingCalc_clicked();

	void on_tblCustomers_doubleClicked(const QModelIndex &index);

	void on_txtProductsSearch_textChanged(const QString &arg1);

	void on_txtCustomerSearch_textChanged(const QString &arg1);

	void on_trvOrders_clicked(const QModelIndex &index);

signals:
	void emitDb(QSqlDatabase db);
private:
	Ui::Customers *ui;
	QSqlDatabase db;
	QString customerID;
	QString companyName;
	QString productID;
	int current_product_row;

	QTimer *tenSecondTimer;

	ProductsModel *m_productsModel;
	QSortFilterProxyModel *m_productsSorter;

	CustomersModel *m_customersModel;
	QSortFilterProxyModel *m_customersSorter;

	bool isQc;
};

#endif // CUSTOMERS_H
