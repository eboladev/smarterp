#include "newactionwizard.h"
#include "ui_newactionwizard.h"

NewActionWizard::NewActionWizard(QWidget *parent) :
	QWizard(parent),
	ui(new Ui::NewActionWizard)
{
	ui->setupUi(this);
}

NewActionWizard::~NewActionWizard()
{
	delete ui;
}
