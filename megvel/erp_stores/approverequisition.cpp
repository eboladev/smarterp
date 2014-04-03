#include "approverequisition.h"
#include "ui_approverequisition.h"
#include <QtSql>
#include "datapublics.h"
ApproveRequisition::ApproveRequisition(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ApproveRequisition)
{
	ui->setupUi(this);
	reloadNewRequisitions();
	reloadPostedRequisitions();
}

ApproveRequisition::~ApproveRequisition()
{
	delete ui;
}

void ApproveRequisition::reloadNewRequisitions()
{
	ui->trvNewRequisitionDetails->invisibleRootItem()->takeChildren();
	ui->trvNewRequisitions->invisibleRootItem()->takeChildren();

	QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery qu = db.exec("SELECT * FROM store_requisition_master WHERE Status = 'Pending'");
	while (qu.next()) {
		QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvNewRequisitions);
		it->setText(0, qu.record().value("EntryID").toString());
		it->setText(1, qu.record().value("RequestedBy").toString());
		it->setText(2, qu.record().value("RequisitionDate").toString());
		it->setText(3, qu.record().value("DateRequired").toString());
		QString supplierName =
				DataPublics::getDbValue(
					"SELECT * FROM suppliers WHERE SupplierID = '" + qu.record().value("SupplierID").toString() + "'"
					, db, "SupplierName"
					).toString();
		it->setText(4, supplierName);
		it->setCheckState(0, Qt::Unchecked);
	}
}

void ApproveRequisition::on_trvNewRequisitions_itemClicked(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column);
	QString masterID = item->text(0);
	ui->trvNewRequisitionDetails->invisibleRootItem()->takeChildren();
	QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery qu = db.exec("SELECT * FROM store_requisition_detail WHERE MasterID = '" + masterID + "'");
	while (qu.next()) {
		QString itemID = qu.record().value("ItemID").toString();
		QString qty = qu.record().value("Qty").toString();
		QString itemName = DataPublics::getDbValue("SELECT * FROM inventory WHERE ItemID = '" +
							   itemID + "'", db, "ItemName").toString();
		QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvNewRequisitionDetails);
		it->setText(0, qu.record().value("ItemName").toString());
		if (qu.record().value("ItemName").toString().length() < 1) {
			it->setText(0, itemName);
		}
		it->setText(1, qty);
	}
}

void ApproveRequisition::reloadPostedRequisitions()
{
	QSqlDatabase db = QSqlDatabase::database();
	ui->trvOldRequisitions->setQuery("SELECT EntryID as 'Rqn No.', RequestedBy as 'Requested By', RequisitionDate as 'Reqn Date' , DateRequired as 'Date Required', suppliers.SupplierName as 'Supplier' FROM store_requisition_master, suppliers WHERE (Status = 'Posted') AND (store_requisition_master.SupplierID = suppliers.supplierID)", db, "Posted Requisitions", true);
	//ui->trvOldRequisitions->setColumnHidden(0, true);
}

void ApproveRequisition::on_trvOldRequisitions_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QSqlDatabase db = QSqlDatabase::database();
	QString masterID = ui->trvOldRequisitions->getCurrentID();

	ui->trvOldRequisitionDetails->setQuery(
				"SELECT inventory.ItemName, store_requisition_detail.Qty FROM store_requisition_detail, inventory WHERE (store_requisition_detail.MasterID = '" + masterID + "') AND (store_requisition_detail.ItemID = inventory.ItemID)", db, "Posted Requisition Details (Requisition no. " + masterID + ")", false);


}

/*
 *
 *QString query = " "
			"INSERT INTO \"PurchaseOrderLine\" (\"VendorRefListID\", \"RefNumber\","
			"\"PurchaseOrderLineItemRefListID\", \"PurchaseOrderLineDesc\","
			"\"PurchaseOrderLineQuantity\", \"PurchaseOrderLineRate\","
			"\"PurchaseOrderLineAmount\", \"PurchaseOrderLineCustomerRefListID\","
			"\"FQSaveToCache\") VALUES ('80000003-1374733028', 'ERP 1', '80000003-1374733064',"
			"'Test Product (Requisition no: 1)', 10, 200, 2000, '80000004-1374737115', 0)";

 *
 *
 */
void ApproveRequisition::on_cmdPost_clicked()
{
	QSqlDatabase odbcDb = QSqlDatabase::addDatabase("QODBC", "quickbooks");
	odbcDb.setDatabaseName("Quickbooks Data");
	if (!odbcDb.open()) {
		DataPublics::showWarning("Could not open quickbooks connection.\n\n" + odbcDb.lastError().text());
		return;
	}

	QSqlDatabase db = QSqlDatabase::database();
	int cnt = 0;
	for (int i = 0; i < ui->trvNewRequisitions->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->trvNewRequisitions->invisibleRootItem()->child(i);
		if (it->checkState(0) == Qt::Checked) {
			cnt++;
			QString masterID = it->text(0);
			QString qb_supplierID = "80000003-1374733028"; //TEST vendor
			QString customerID = "80000004-1374737115"; //Main store

			QString reqSupplierID = DataPublics::getDbValue("SELECT SupplierID FROM store_requisition_master WHERE EntryID = '" + masterID + "'", db, "SupplierID").toString();
			QString mysqlSupplierQBId = DataPublics::getDbValue("SELECT QuickbooksID FROM suppliers WHERE SupplierID = '" + reqSupplierID + "'", db, "QuickbooksID").toString();
			QString suppName = DataPublics::getDbValue("SELECT * FROM suppliers WHERE SupplierID = '" + reqSupplierID + "'", db, "SupplierName").toString();

			if (mysqlSupplierQBId.length() > 0) {
				qb_supplierID = mysqlSupplierQBId;
			} else {
				QSqlQuery suppQu = odbcDb.exec("SELECT ListID, Name FROM Vendor WHERE Name = '" + suppName + "'");
				if (!suppQu.lastError().isValid()) {
					suppQu.first();
					qb_supplierID = suppQu.record().value("ListID").toString();
					db.exec("UPDATE suppliers SET QuickbooksID = '" + qb_supplierID  + "' WHERE SupplierID = '" + reqSupplierID + "'");
				}
			}

			QSqlQuery itemQuery = db.exec(
						"SELECT inventory.QuickbooksID, inventory.QuickbooksCost, inventory.ItemID as 'InvItemID', store_requisition_detail.ItemName, store_requisition_detail.Qty FROM store_requisition_detail, inventory WHERE (store_requisition_detail.MasterID = '" + masterID + "') AND (store_requisition_detail.ItemID = inventory.ItemID)"
						);
			if (itemQuery.lastError().isValid())
			{
				DataPublics::showWarning(itemQuery.lastError().text());
				return;
			}
			int rowCnt = itemQuery.size();
			int pos = 0;
			while (itemQuery.next()) {
				pos++;
				QString itemName = itemQuery.record().value("ItemName").toString();
				QString qty = itemQuery.record().value("Qty").toString();
				QString erpQbID = itemQuery.record().value("QuickbooksID").toString();
				QString invItemID = itemQuery.record().value("InvItemID").toString();
				QString erpQbCost = itemQuery.record().value("QuickbooksCost").toString();
				QString qbItemID = erpQbID;
				if (erpQbID.length() < 1 || erpQbCost == "-1") {
					//This item does not have a quickbooks item id on mysql, or mysql cost is not defined. Fetch it from quickbooks.
					QString  qbItemQueryString = "SELECT ListID, SalesOrPurchasePrice FROM Item WHERE Name = '" + itemName + "'";
					QSqlQuery qbItemQuery = odbcDb.exec(qbItemQueryString);
					if (qbItemQuery.lastError().isValid()) {
						DataPublics::showWarning("Aborting. Please ensure that all items exist in quickbooks.\n\n" + qbItemQuery.lastError().text());
						return;
					}
					qbItemQuery.first();
					qbItemID = qbItemQuery.record().value("ListID").toString();
					erpQbCost = qbItemQuery.record().value("SalesOrPurchasePrice").toString();
					db.exec("UPDATE inventory SET QuickbooksID = '" + qbItemID + "', QuickbooksCost = '" + erpQbCost +"' WHERE ItemID = '" + invItemID  + "'");
				}

				QString tempID = "1";
				if (pos == rowCnt)
					tempID = "0";

				if (erpQbCost.length() < 1)
					erpQbCost = "0";

				float total = qty.toFloat() * erpQbCost.toFloat();

				QString qbQuery = " "
						"INSERT INTO \"PurchaseOrderLine\" (\"VendorRefListID\", \"RefNumber\","
						"\"PurchaseOrderLineItemRefListID\", \"PurchaseOrderLineDesc\","
						"\"PurchaseOrderLineQuantity\", \"PurchaseOrderLineRate\","
						"\"PurchaseOrderLineAmount\", \"PurchaseOrderLineCustomerRefListID\","
						"\"FQSaveToCache\") VALUES ('" + qb_supplierID + "', 'ERP  "+ masterID + "', '"
						+ qbItemID + "',"
						"'" + itemName + "', " + qty + ", " + erpQbCost + ", "+ QString::number(total) +", '"
						+ customerID + "', "+ tempID +")";
				//DataPublics::showInformation(qbQuery);
				odbcDb.exec(qbQuery);
			}
			db.exec("UPDATE store_requisition_master SET Status = 'Posted' WHERE EntryID = '"  + masterID + "'");
		}
	}
	if (cnt == 0) {
		DataPublics::showWarning("Please tick at least one requisition to post.");
	} else {
		DataPublics::showInformation(tr("%1 requisition(s) successfully posted to quickbooks.").arg(cnt));
		reloadNewRequisitions();
		reloadPostedRequisitions();
	}
}

void ApproveRequisition::on_trvNewRequisitions_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
}
