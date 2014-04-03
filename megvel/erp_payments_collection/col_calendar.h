#ifndef COL_CALENDAR_H
#define COL_CALENDAR_H

#include <QMainWindow>

namespace Ui {
class col_calendar;
}

class col_calendar : public QMainWindow
{
	Q_OBJECT

public:
	explicit col_calendar(QWidget *parent = 0);
	~col_calendar();

private:
	Ui::col_calendar *ui;
};

#endif // COL_CALENDAR_H
