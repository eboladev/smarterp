#ifndef CALENDARDATESELECTOR_H
#define CALENDARDATESELECTOR_H

#include <QDialog>
#include <QDate>
namespace Ui {
class CalendarDateSelector;
}

class CalendarDateSelector : public QDialog
{
	Q_OBJECT

public:
	explicit CalendarDateSelector(QWidget *parent = 0, QDate def = QDate::currentDate());
	~CalendarDateSelector();
	QDate dat;
private slots:
	void on_buttonBox_accepted();

private:
	Ui::CalendarDateSelector *ui;
};

#endif // CALENDARDATESELECTOR_H
