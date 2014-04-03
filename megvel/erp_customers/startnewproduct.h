#ifndef STARTNEWPRODUCT_H
#define STARTNEWPRODUCT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class StartNewProduct;
}

class StartNewProduct : public QDialog
{
	Q_OBJECT

public:
	explicit StartNewProduct(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~StartNewProduct();
	void setCustomer(QString customerName);
signals:
	void saved(QString pID);
private slots:
	void on_cmdNext_clicked();

private:
	Ui::StartNewProduct *ui;
	QSqlDatabase db;
};

#endif // STARTNEWPRODUCT_H
