#include "startnewemployeedialog.h"
#include "ui_startnewemployeedialog.h"

StartNewEmployeeDialog::StartNewEmployeeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::StartNewEmployeeDialog)
{
	ui->setupUi(this);
}

StartNewEmployeeDialog::~StartNewEmployeeDialog()
{
	delete ui;
}

void StartNewEmployeeDialog::on_buttonBox_accepted()
{
	name = ui->txtFName->text();
}
