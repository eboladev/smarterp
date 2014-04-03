#ifndef VIEWSCHEDULE_H
#define VIEWSCHEDULE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ViewSchedule;
}

class ViewSchedule : public QDialog
{
	Q_OBJECT

public:
	explicit ViewSchedule(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ViewSchedule();

private:
	Ui::ViewSchedule *ui;
	QSqlDatabase db;
private slots:
	void reloadSchedule();
	void on_cmdPreviousDate_clicked();
	void on_cmdNextDate_clicked();
	void on_cmdPrintProductionSchedule_clicked();
	void on_dtpDate_dateChanged(const QDate &date);
};

#endif // VIEWSCHEDULE_H
