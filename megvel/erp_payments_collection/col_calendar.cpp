#include "col_calendar.h"
#include "ui_col_calendar.h"

col_calendar::col_calendar(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::col_calendar)
{
	ui->setupUi(this);
}

col_calendar::~col_calendar()
{
	delete ui;
}
