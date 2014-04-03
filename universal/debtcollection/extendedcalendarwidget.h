#ifndef EXTENDEDCALENDARWIDGET_H
#define EXTENDEDCALENDARWIDGET_H

#include <QWidget>

namespace Ui {
class ExtendedCalendarWidget;
}

class ExtendedCalendarWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ExtendedCalendarWidget(QWidget *parent = 0);
	~ExtendedCalendarWidget();

private slots:
	void on_cmdNextMonth_clicked();

	void on_cmdPreviousMonth_clicked();
	void redrawMonth();
private:
	Ui::ExtendedCalendarWidget *ui;
};

#endif // EXTENDEDCALENDARWIDGET_H
