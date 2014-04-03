#ifndef COL_CUSTOMERLIST_H
#define COL_CUSTOMERLIST_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class col_CustomerList;
}

class col_CustomerList : public QMainWindow
{
	Q_OBJECT

public:
	explicit col_CustomerList(QWidget *parent = 0);
	~col_CustomerList();

private:
	Ui::col_CustomerList *ui;
	QSqlDatabase odbc_db;

private slots:
	void openConnection();
	void on_cmdShow_clicked();
};

#endif // COL_CUSTOMERLIST_H
