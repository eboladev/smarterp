#ifndef PAYSLIPS_H
#define PAYSLIPS_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class Payslips;
}

class Payslips : public QMainWindow
{
	Q_OBJECT

public:
	explicit Payslips(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~Payslips();

private slots:
	void on_cmdGenerate_clicked();
	void reloadEmployees();
	void reloadMonths();
	void on_checkBox_toggled(bool checked);

private:
	Ui::Payslips *ui;
	QSqlDatabase db;
};

#endif // PAYSLIPS_H
