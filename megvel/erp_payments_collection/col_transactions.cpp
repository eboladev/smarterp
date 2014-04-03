#include "col_transactions.h"
#include "ui_col_transactions.h"

col_transactions::col_transactions(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::col_transactions)
{
	ui->setupUi(this);
}

col_transactions::~col_transactions()
{
	delete ui;
}
