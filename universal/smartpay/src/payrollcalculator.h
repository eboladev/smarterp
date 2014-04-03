#ifndef PAYROLLCALCULATOR_H
#define PAYROLLCALCULATOR_H

#include <QtSql>
#include <QDialog>

namespace Ui {
class PayrollCalculator;
}

class PayrollCalculator : public QDialog
{
	Q_OBJECT

public:
	explicit PayrollCalculator(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
				   QString month = QString());
	~PayrollCalculator();
private slots:
	void progress(int p);
	void finished();
	void employee(QString e);
private:
	Ui::PayrollCalculator *ui;
	QSqlDatabase db;
	QString monthID;
};

#endif // PAYROLLCALCULATOR_H
