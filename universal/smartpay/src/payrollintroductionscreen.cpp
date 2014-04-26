#include "payrollintroductionscreen.h"
#include "ui_payrollintroductionscreen.h"

PayrollIntroductionScreen::PayrollIntroductionScreen(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::PayrollIntroductionScreen)
{
	ui->setupUi(this);
}

PayrollIntroductionScreen::~PayrollIntroductionScreen()
{
	delete ui;
}
