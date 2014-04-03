#ifndef COL_INVOICEFETCHER_H
#define COL_INVOICEFETCHER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class col_InvoiceFetcher;
}

class col_InvoiceFetcher : public QDialog
{
	Q_OBJECT

public:
	explicit col_InvoiceFetcher(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
				    QSqlDatabase OdbcDatbase = QSqlDatabase());
	~col_InvoiceFetcher();

private slots:
	void on_cmdCancel_clicked();
	void showProgress(QString invNo);
private:
	Ui::col_InvoiceFetcher *ui;
	QSqlDatabase db;
	QSqlDatabase odbc_db;
};

#endif // COL_INVOICEFETCHER_H
