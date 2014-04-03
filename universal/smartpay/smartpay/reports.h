#ifndef REPORTS_H
#define REPORTS_H

#include <QMainWindow>

namespace Ui {
class Reports;
}

class Reports : public QMainWindow
{
	Q_OBJECT

public:
	explicit Reports(QWidget *parent = 0);
	~Reports();

private:
	Ui::Reports *ui;
};

#endif // REPORTS_H
