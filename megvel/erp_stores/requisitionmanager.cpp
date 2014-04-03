#include "requisitionmanager.h"
#include "ui_requisitionmanager.h"
#include <QtSql>

RequisitionManager::RequisitionManager(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::RequisitionManager)
{
	ui->setupUi(this);
	reloadRequisitions();
}

RequisitionManager::~RequisitionManager()
{
	delete ui;
}

void RequisitionManager::reloadRequisitions()
{
	QSqlDatabase db = QSqlDatabase::database();
	ui->lstRequisitions->setQuery("SELECT * FROM vw_qt_requisitions", db, "Requisitions", true);
	ui->lstRequisitions->setColumnHidden(0, true);
}

void RequisitionManager::on_cmdApproveRequisition_clicked()
{
	QSqlDatabase db = QSqlDatabase::database();
	QString reqnID = ui->lstRequisitions->getCurrentID();
	if (reqnID.length() > 0) {
		QString status =
				DataPublics::getDbValue("SELECT status FROM qt_requisitions WHERE EntryID = '" + reqnID + "'", db, "Status").toString();
		if (status != "Pending") {
			DataPublics::showWarning("This requisition has already been approved.");
			return;
		} else {
			db.exec("UPDATE qt_requisitions SET Status = 'Approved' WHERE EntryID = '" + reqnID + "'");
			reloadRequisitions();
		}
	} else {
		DataPublics::showWarning("Please select a requisition.");
	}
}

void RequisitionManager::on_cmdPostToQuickbooks_clicked()
{
	QSqlDatabase db = QSqlDatabase::database();
	QString reqnID = ui->lstRequisitions->getCurrentID();
	if (reqnID.length() > 0) {
		QString status =
				DataPublics::getDbValue("SELECT status FROM qt_requisitions WHERE EntryID = '" + reqnID + "'", db, "Status").toString();
		if (status == "Pending") {
			DataPublics::showWarning("This requisition has not been approved.");
			return;
		} else {
			//post to quickbooks

			QSqlDatabase odbcDb = QSqlDatabase::addDatabase("QODBC", "quickbooks");
			odbcDb.setDatabaseName("Quickbooks Data");
			if (odbcDb.open()) {
				QString query = " "
						"INSERT INTO \"PurchaseOrderLine\" (\"VendorRefListID\", \"RefNumber\","
						"\"PurchaseOrderLineItemRefListID\", \"PurchaseOrderLineDesc\","
						"\"PurchaseOrderLineQuantity\", \"PurchaseOrderLineRate\","
						"\"PurchaseOrderLineAmount\", \"PurchaseOrderLineCustomerRefListID\","
						"\"FQSaveToCache\") VALUES ('80000003-1374733028', 'ERP 1', '80000003-1374733064',"
						"'Test Product (Requisition no: 1)', 10, 200, 2000, '80000004-1374737115', 0)";

				QSqlQuery quOdbc  = odbcDb.exec(query);
				if (quOdbc.lastError().isValid()) {
					DataPublics::showWarning("Quickbooks Error:\n\n" + quOdbc.lastError().text());
				} else {

					db.exec("UPDATE qt_requisitions SET Status = 'Posted to Quickbooks' WHERE EntryID = '" + reqnID + "'");
					reloadRequisitions();
				}
				odbcDb.close();
			} else {
				DataPublics::showWarning("Quickbooks Error:\n\n" + odbcDb.lastError().text());
			}


		}
	} else {
		DataPublics::showWarning("Please select a requisition.");
	}
}
