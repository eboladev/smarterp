#ifndef PAYROLLAPI_H
#define PAYROLLAPI_H

#include <QObject>
#include <QDate>

class QLineEdit;
class PayrollAPI : public QObject
{
	Q_OBJECT
public:
	explicit PayrollAPI(QObject *parent = 0);
	static void showError(QString error, QWidget *parent = 0, QString title = "Error");
	static QString selectDateFromCalendar(QDate defaultDate = QDate::currentDate());
	static void setLineEditDate(QLineEdit *txt);
signals:

public slots:

};



#endif // PAYROLLAPI_H
