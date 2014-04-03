#ifndef OVERTIME_ENTRYSCAN_H
#define OVERTIME_ENTRYSCAN_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Overtime_EntryScan;
}

class Overtime_EntryScan : public QDialog
{
	Q_OBJECT

public:
	explicit Overtime_EntryScan(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
				    QString Month = QString());
	~Overtime_EntryScan();

private:
	Ui::Overtime_EntryScan *ui;
	QSqlDatabase db;
	QString monthID;
};

#endif // OVERTIME_ENTRYSCAN_H
