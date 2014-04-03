#ifndef PRODUCTSAPPROVAL_H
#define PRODUCTSAPPROVAL_H

#include <QMainWindow>
#include <QtSql>
#include <QSettings>

namespace Ui {
class ProductsApproval;
}

class ProductsApproval : public QMainWindow
{
	Q_OBJECT

public:
	explicit ProductsApproval(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ProductsApproval();
	void setDatabase(QSqlDatabase database);
private slots:
	void reloadCustomers();
	void loadProducts();
	void on_trvCustomers_clicked(const QModelIndex &index);

	void on_cmdApprove_clicked();

	void on_cmdUnapprove_clicked();

private:
	Ui::ProductsApproval *ui;
	QSqlDatabase db;
	QString currentCustomerID;
	QSettings sett;
};

#endif // PRODUCTSAPPROVAL_H
