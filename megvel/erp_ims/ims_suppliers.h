#ifndef IMS_SUPPLIERS_H
#define IMS_SUPPLIERS_H

#include <QMainWindow>
#include "datapublics.h"
namespace Ui {
class ims_suppliers;
}

class ims_suppliers : public QMainWindow
{
	Q_OBJECT

public:
	explicit ims_suppliers(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ims_suppliers();
	void reloadList();
private slots:
	void on_lstSuppliers_doubleClicked(const QModelIndex &index);

	void on_cmdNewSupplier_clicked();

	void on_cmdDeleteSupplier_clicked();

private:
	Ui::ims_suppliers *ui;
	QSqlDatabase db;
};

#endif // IMS_SUPPLIERS_H
