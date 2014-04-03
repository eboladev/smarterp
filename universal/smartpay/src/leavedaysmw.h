#ifndef LEAVEDAYSMW_H
#define LEAVEDAYSMW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class LeaveDaysMW;
}

class LeaveDaysMW : public QMainWindow
{
	Q_OBJECT

public:
	explicit LeaveDaysMW(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~LeaveDaysMW();

private slots:
	void on_cboMonths_editTextChanged(const QString &arg1);

	void on_actionNew_triggered();

	void on_cmdDelete_clicked();

	void on_cboMonths_currentIndexChanged(const QString &arg1);

private:
	Ui::LeaveDaysMW *ui;
	QSqlDatabase db;
};

#endif // LEAVEDAYSMW_H
