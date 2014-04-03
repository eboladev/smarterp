#ifndef MANUALCLOCKIN_H
#define MANUALCLOCKIN_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ManualClockIn;
}

class ManualClockIn : public QDialog
{
	Q_OBJECT

public:
	explicit ManualClockIn(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ManualClockIn();

private slots:
	void on_cmdSave_clicked();

	void on_SelectAll_clicked();

	void on_SelectNone_clicked();

private:
	Ui::ManualClockIn *ui;
	QSqlDatabase db;
	void loadEmployees();
};

#endif // MANUALCLOCKIN_H
