#include "samplecalc.h"
#include "ui_samplecalc.h"

SampleCalc::SampleCalc(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SampleCalc)
{
	ui->setupUi(this);
}

SampleCalc::~SampleCalc()
{
	delete ui;
}
