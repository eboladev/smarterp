#ifndef PAYROLLINTRODUCTIONSCREEN_H
#define PAYROLLINTRODUCTIONSCREEN_H

#include <QMainWindow>

namespace Ui {
class PayrollIntroductionScreen;
}

class PayrollIntroductionScreen : public QMainWindow
{
	Q_OBJECT

public:
	explicit PayrollIntroductionScreen(QWidget *parent = 0);
	~PayrollIntroductionScreen();

private:
	Ui::PayrollIntroductionScreen *ui;
};

#endif // PAYROLLINTRODUCTIONSCREEN_H
