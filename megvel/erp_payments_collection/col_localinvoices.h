#ifndef COL_LOCALINVOICES_H
#define COL_LOCALINVOICES_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class col_LocalInvoices;
}

class col_LocalInvoices : public QMainWindow
{
	Q_OBJECT

public:
	explicit col_LocalInvoices(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~col_LocalInvoices();

private:
	Ui::col_LocalInvoices *ui;
	QSqlDatabase db;
	QSqlDatabase odbc_db;

private slots:
	void showInvoices();
	void refetchQbData();
	void on_cmdChangeInvoiceDates_clicked();
	void on_cmdFetchQuickbooksData_clicked();
};

#endif // COL_LOCALINVOICES_H
