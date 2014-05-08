#ifndef PAYROLLREPORTS_H
#define PAYROLLREPORTS_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class PayrollReports;
}

class PayrollReports : public QMainWindow
{
	Q_OBJECT

public:
	explicit PayrollReports(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~PayrollReports();

private:
	Ui::PayrollReports *ui;
	QSqlDatabase db;
};

#endif // PAYROLLREPORTS_H
