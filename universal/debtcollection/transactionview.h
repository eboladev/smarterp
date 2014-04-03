#ifndef TRANSACTIONVIEW_H
#define TRANSACTIONVIEW_H

#include <QWidget>
#include "publics.h"
#include "mymodels.h"

namespace Ui {
class TransactionView;
}

class TransactionView : public QWidget
{
	Q_OBJECT

public:
	explicit TransactionView(QWidget *parent = 0);
	~TransactionView();

	QString customer() { return m_customer; }
	QDate startDate() { return m_startDate; }
	QDate endDate() {return m_endDate; }
	QString txnType() { return m_type; }

	void setCustomer(QString c);
	void setCustomerID(QString cID);
	void setStartDate(QDate d);
	void setEndDate(QDate d);
	void setTxnType(QString t);

	void reloadData();
	void reInitialize();
private slots:
	void on_cboCustomers_textChanged(const QString &arg1);

	void on_dtpStartDate_dateChanged(const QDate &date);

	void on_dtpEndDate_dateChanged(const QDate &date);

	void on_cboTxnType_currentIndexChanged(const QString &arg1);

private:
	Ui::TransactionView *ui;

	QString m_customer;
	QDate m_startDate;
	QDate m_endDate;

	QString m_type;

	TransactionsModel *transModel;
};

#endif // TRANSACTIONVIEW_H
