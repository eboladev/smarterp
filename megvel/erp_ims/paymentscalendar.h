#ifndef PAYMENTSCALENDAR_H
#define PAYMENTSCALENDAR_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class PaymentsCalendar;
}

class PaymentsCalendar : public QMainWindow
{
	Q_OBJECT

public:
	explicit PaymentsCalendar(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~PaymentsCalendar();

private:
	Ui::PaymentsCalendar *ui;
	QSqlDatabase db;
	QDate cDate;

private slots:
	void autoMonth();
	void autocDate();
	void on_cmdPreviousMonth_clicked();
	void on_cmdNextMonth_clicked();
	void redrawCalendar();
	void on_cboMonth_currentIndexChanged(int index);
	void on_cboYear_currentIndexChanged(int index);
};

#endif // PAYMENTSCALENDAR_H
