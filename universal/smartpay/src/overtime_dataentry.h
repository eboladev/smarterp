#ifndef OVERTIME_DATAENTRY_H
#define OVERTIME_DATAENTRY_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Overtime_DataEntry;
}

class Overtime_DataEntry : public QMainWindow
{
	Q_OBJECT

public:
	explicit Overtime_DataEntry(QWidget *parent = 0,
				    QSqlDatabase database = QSqlDatabase()
			);
	~Overtime_DataEntry();

private slots:
	void on_dtpDate_dateChanged(const QDate &date);
	void refreshOt();
	void on_cmdNew_clicked();

	void on_cmdSave_clicked();
	void reformatDates();
private:
	Ui::Overtime_DataEntry *ui;
	QSqlDatabase db;
	QSqlRelationalTableModel *otModel;
};

#endif // OVERTIME_DATAENTRY_H
