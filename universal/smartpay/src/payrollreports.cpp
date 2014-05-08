#include "payrollreports.h"
#include "ui_payrollreports.h"

PayrollReports::PayrollReports(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::PayrollReports)
{
	ui->setupUi(this);
	db = database;
}

PayrollReports::~PayrollReports()
{
	delete ui;
}
