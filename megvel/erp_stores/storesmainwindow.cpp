#include "storesmainwindow.h"
#include "ui_storesmainwindow.h"
#include "suppliers.h"
#include "inventory.h"
#include "newrequisition.h"
#include "approverequisition.h"
#include "requisitionwizard.h"
StoresMainWindow::StoresMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::StoresMainWindow)
{
	ui->setupUi(this);
	db  = database;
}

StoresMainWindow::~StoresMainWindow()
{
	delete ui;
}

void StoresMainWindow::on_actionManage_Suppliers_triggered()
{
	Suppliers *supp = new Suppliers(this);
	ui->mdiArea->addSubWindow(supp);
	supp->show();
}

void StoresMainWindow::on_actionItem_List_triggered()
{
	Inventory *inv = new Inventory(this);
	ui->mdiArea->addSubWindow(inv);
	inv->show();
}

void StoresMainWindow::on_actionNew_Requisition_triggered()
{
	RequisitionWizard *newReq = new RequisitionWizard(this);
	if (newReq->exec() == QDialog::Accepted) {

	}
}

void StoresMainWindow::on_actionView_Requisitions_triggered()
{
	ApproveRequisition *app = new ApproveRequisition(this);
	ui->mdiArea->addSubWindow(app);
	app->show();
}

void StoresMainWindow::on_actionNew_Film_Requisition_triggered()
{
	RequisitionWizard *newReq = new RequisitionWizard(this, true);
	if (newReq->exec() == QDialog::Accepted) {

	}
}
