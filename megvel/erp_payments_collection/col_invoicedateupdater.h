#ifndef COL_INVOICEDATEUPDATER_H
#define COL_INVOICEDATEUPDATER_H

#include <QDialog>
#include <QtSql>
namespace Ui {
class col_InvoiceDateUpdater;
}

class col_InvoiceDateUpdater : public QDialog
{
	Q_OBJECT

public:
	explicit col_InvoiceDateUpdater(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
					QSqlDatabase OdbcDatbase = QSqlDatabase());
	~col_InvoiceDateUpdater();
private slots:
	void on_cmdCancel_clicked();
	void showProgress(QString invNo);
private:
	Ui::col_InvoiceDateUpdater *ui;
	QSqlDatabase db;
	QSqlDatabase odbc_db;
};

#endif // COL_INVOICEDATEUPDATER_H
