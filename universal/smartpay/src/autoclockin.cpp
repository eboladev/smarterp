#include "autoclockin.h"
#include "ui_autoclockin.h"

AutoClockIn::AutoClockIn(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::AutoClockIn)
{
	ui->setupUi(this);
	db = database;
}

AutoClockIn::~AutoClockIn()
{
	delete ui;
}

void AutoClockIn::reloadEmployees() {
	//ui->lstEmployees-
	employeesModel = new QSqlQueryModel(this);
	employeesModel->setQuery("SELECT * FROM vw_employeenames ORDER BY `#` ASC", db);
	ui->lstEmployees->setModel(employeesModel);
	ui->lstEmployees->setColumnHidden(0, true);
	for (int i = 0; i < employeesModel->rowCount(); i++) {
		ui->lstEmployees->itemDelegateForRow(i);
	}


}
