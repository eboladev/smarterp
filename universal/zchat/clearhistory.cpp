#include "clearhistory.h"
#include "ui_clearhistory.h"

ClearHistory::ClearHistory(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ClearHistory)
{
	ui->setupUi(this);
}

ClearHistory::~ClearHistory()
{
	delete ui;
}
