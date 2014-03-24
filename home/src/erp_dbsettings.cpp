#include "erp_dbsettings.h"
#include "ui_erp_dbsettings.h"

ERP_DbSettings::ERP_DbSettings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ERP_DbSettings)
{
	ui->setupUi(this);
}

ERP_DbSettings::~ERP_DbSettings()
{
	delete ui;
}

void ERP_DbSettings::on_cmdSaveSettings_clicked()
{

}
