#include "inventory.h"
#include "ui_inventory.h"

#include "datapublics.h"
#include "inventoryeditor.h"
Inventory::Inventory(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Inventory)
{
	ui->setupUi(this);
	reloadInventory();
}

Inventory::~Inventory()
{
	delete ui;
}

void Inventory::reloadInventory()
{
	QSqlQuery qu = QSqlDatabase::database().exec("SELECT * FROM inventory");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}
	ui->trvInventory->invisibleRootItem()->takeChildren();
	while (qu.next()) {
		if (!itemExists(qu.record().value("ItemID").toString())) {
			QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvInventory);
			setItem(it, qu.record());
			addChildren(it->text(99), it);
		}
	}
	ui->trvInventory->resizeColumnToContents(0);
}

void Inventory::addChildren(QString id, QTreeWidgetItem *parent)
{
	QSqlQuery qu = QSqlDatabase::database().exec("SELECT * FROM inventory WHERE ParentID = '" + id + "'");
	if (qu.lastError().isValid()) {
		return;
	}
	parent->takeChildren();
	while (qu.next()) {
		if (!itemExists(qu.record().value("ItemID").toString())) {
			QTreeWidgetItem *it = new QTreeWidgetItem(parent);
			setItem(it, qu.record());
			addChildren(it->text(99), it);
		} else  {
			// QTreeWidgetItem *it = getItem(qu.record().value("ItemID").toString());
			// parent->addChild(it);
		}

	}
}

void Inventory::setItem(QTreeWidgetItem *it, QSqlRecord rec)
{
	it->setText(99, rec.value("ItemID").toString());
	it->setText(0, rec.value("ItemName").toString());
	//desc, on hand, reorder, suppl
	it->setText(1, rec.value("Description").toString());
	it->setText(2, rec.value("OnHand").toString());
	it->setText(3, rec.value("ReorderLevel").toString());
	if (rec.value("UOM").toString() != "No") {
		it->setText(2, it->text(2) + " " + rec.value("UOM").toString());
		it->setText(3, it->text(3) + " " + rec.value("UOM").toString());
	}
	QString supplierID = rec.value("PreferredSupplier").toString();
	if (supplierID.length() > 0) {
		QString supplierName = DataPublics::getDbValue(
					"SELECT * FROM suppliers WHERE SupplierID = '" + supplierID + "'",
					QSqlDatabase::database(), "SupplierName"
					).toString();
		it->setText(4, supplierName);
	}
	it->setExpanded(true);

	double qty = rec.value("OnHand").toDouble();
	double reorder = rec.value("ReorderLevel").toDouble();

	if (qty < reorder) {
		QColor redColor = QColor(255,0,0);
		it->setForeground(0, QBrush(redColor));
	}
}

bool Inventory::itemExists(QString id)
{
	bool ret = false;

	for (int i = 0; i < ui->trvInventory->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->trvInventory->invisibleRootItem()->child(i);
		if (it->text(99) == id)
			return true;

		if (checkItemInParent(id, it))
			return true;
	}

	return ret;
}

QTreeWidgetItem *Inventory::getItem(QString id)
{
	for (int i = 0; i < ui->trvInventory->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->trvInventory->invisibleRootItem()->child(i);
		if (it->text(99) == id)
			return it;

		return getItemInParent(id, it);
	}
}

bool Inventory::checkItemInParent(QString id, QTreeWidgetItem *parent)
{
	for (int i = 0; i < parent->childCount(); i++) {
		QTreeWidgetItem *it = parent->child(i);
		if (it->text(99) == id)
			return true;

		if (it->childCount() > 0) {
			if (checkItemInParent(id, it))
				return true;
		}
	}
	return false;
}

QTreeWidgetItem *Inventory::getItemInParent(QString id, QTreeWidgetItem *parent)
{
	for (int i = 0; i < parent->childCount(); i++) {
		QTreeWidgetItem *it = parent->child(i);
		if (it->text(99) == id)
			return it;

		if (it->childCount() > 0) {
			return getItemInParent(id, it);
		}
	}
}


void Inventory::on_trvInventory_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column);
	QString itemID = item->text(99);
	InventoryEditor *ed = new InventoryEditor(this, itemID);
	ed->Edit();
	if (ed->exec() == QDialog::Accepted)
		reloadInventory();
}

void Inventory::on_actionRefresh_triggered()
{
	reloadInventory();
}

void Inventory::on_actionNew_triggered()
{
	InventoryEditor *ed = new InventoryEditor(this, "");
	ed->StartAddNew();
	if (ed->exec() == QDialog::Accepted)
		reloadInventory();
}

void Inventory::on_actionEdit_triggered()
{

}

void Inventory::on_trvInventory_itemClicked(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(item);
	Q_UNUSED(column);
}

void Inventory::on_trvInventory_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
}
