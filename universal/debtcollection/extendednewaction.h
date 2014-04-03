#ifndef EXTENDEDNEWACTION_H
#define EXTENDEDNEWACTION_H

#include <QDialog>
#include "publics.h"
#include "calendar.h"
namespace Ui {
class ExtendedNewAction;
}

class ExtendedNewAction : public QDialog
{
	Q_OBJECT

public:
	explicit ExtendedNewAction(QWidget *parent = 0, QList<Calendar *> *calendars = new QList <Calendar *>);
	~ExtendedNewAction();
	void setCustomer(QString custName);
	void loadCustomerAgeing();
private slots:
	void on_cmdSave_clicked();

	void on_cmdShowAgeing_clicked();

	void on_cboCustomer_currentIndexChanged(const QString &arg1);

	void on_cmdExit_clicked();

	void on_cboNextCalendar_editTextChanged(const QString &arg1);


private:
	Ui::ExtendedNewAction *ui;
	Appointment *currentAction;
	Appointment *nextAction;
	QList <Calendar *> *ptrCalendars;
};

#endif // EXTENDEDNEWACTION_H
