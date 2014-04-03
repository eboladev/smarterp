#include "createproforma.h"
#include "ui_createproforma.h"

CreateProforma::CreateProforma(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CreateProforma)
{
	ui->setupUi(this);
}

CreateProforma::~CreateProforma()
{
	delete ui;
}
