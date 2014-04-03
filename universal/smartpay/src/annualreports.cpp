#include "annualreports.h"
#include "ui_annualreports.h"

AnnualReports::AnnualReports(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::AnnualReports)
{
	ui->setupUi(this);
}

AnnualReports::~AnnualReports()
{
	delete ui;
}
