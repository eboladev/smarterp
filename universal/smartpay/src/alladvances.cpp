#include "alladvances.h"
#include "ui_alladvances.h"

#include "cash_advances.h"
#include "advances.h"

AllAdvances::AllAdvances(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::AllAdvances)
{
	ui->setupUi(this);
	db = database;

	CashAdvances *cashAdvances = new CashAdvances(this, db);
	Advances *advances = new Advances(this, db);

	ui->widget->insertTab(advances);
	ui->widget->insertTab(cashAdvances);
}

AllAdvances::~AllAdvances()
{
	delete ui;
}
