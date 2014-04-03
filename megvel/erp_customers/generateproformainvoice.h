#ifndef GENERATEPROFORMAINVOICE_H
#define GENERATEPROFORMAINVOICE_H

#include <QDialog>
#include <QSqlDatabase>
#include <iostream>
#include <cmath>
#include <stdint.h>
namespace Ui {
class GenerateProformaInvoice;
}

class GenerateProformaInvoice : public QDialog
{
	Q_OBJECT

public:
	explicit GenerateProformaInvoice(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~GenerateProformaInvoice();
	QString customerID() const;
	void setCustomerID(const QString &customerID);
	void addProduct(QString productID);
	double round_nplaces(double &value, const uint32_t &to = 2);
private slots:
	void recalculateTotals();
	void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

	void on_tableWidget_clicked(const QModelIndex &index);

	void on_cmdGenerate_clicked();

	void on_GenerateProformaInvoice_accepted();

private:
	Ui::GenerateProformaInvoice *ui;
	QSqlDatabase db;
	QString m_customerID;
	double round2(double number);
};

#endif // GENERATEPROFORMAINVOICE_H
