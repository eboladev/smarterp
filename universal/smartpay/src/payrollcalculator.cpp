#include "payrollcalculator.h"
#include "ui_payrollcalculator.h"
#include <QMessageBox>
#include "threadedpayrollcalculator.h"
PayrollCalculator::PayrollCalculator(QWidget *parent, QSqlDatabase database, QString month) :
	QDialog(parent),
	ui(new Ui::PayrollCalculator)
{
	ui->setupUi(this);
	db = database;
	monthID = month;
	ui->lblEmployee->setText("");

	QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames");
	if (!qu.lastError().isValid()) {
		ui->progress->setMaximum(qu.size());
		ui->progress->setMinimum(0);
		ui->progress->setValue(0);
		ThreadedPayrollCalculator *th = new ThreadedPayrollCalculator(this, db, monthID);
		connect (th, SIGNAL(progress(int)), SLOT(progress(int)));
		connect (th, SIGNAL(finished()), SLOT(finished()));
		connect (th, SIGNAL(terminated()), SLOT(finished()));
		connect (th, SIGNAL(currentEmployee(QString)), SLOT(employee(QString)));
		th->start();
	} else {
		this->reject();
	}
}

PayrollCalculator::~PayrollCalculator()
{
	delete ui;
}

void PayrollCalculator::progress(int p)
{
	ui->progress->setValue(p);
}

void PayrollCalculator::finished()
{
	this->accept();
}

void PayrollCalculator::employee(QString e)
{
	ui->lblEmployee->setText(e);
}
