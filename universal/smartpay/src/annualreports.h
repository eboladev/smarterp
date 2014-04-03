#ifndef ANNUALREPORTS_H
#define ANNUALREPORTS_H

#include <QMainWindow>

namespace Ui {
class AnnualReports;
}

class AnnualReports : public QMainWindow
{
	Q_OBJECT

public:
	explicit AnnualReports(QWidget *parent = 0);
	~AnnualReports();

private:
	Ui::AnnualReports *ui;
};

#endif // ANNUALREPORTS_H
