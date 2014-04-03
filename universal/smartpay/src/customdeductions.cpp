#include "customdeductions.h"
#include "ui_customdeductions.h"

CustomDeductions::CustomDeductions(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CustomDeductions)
{
	ui->setupUi(this);
}

CustomDeductions::~CustomDeductions()
{
	delete ui;
}
