#include "inventoryeditor.h"
#include "ui_inventoryeditor.h"
#include "datapublics.h"
InventoryEditor::InventoryEditor(QWidget *parent, QString ItemID) :
	QDialog(parent),
	ui(new Ui::InventoryEditor)
{
	ui->setupUi(this);

	connect (ui->cmdSave, SIGNAL(clicked()), SLOT(Save()));

	currentID = ItemID;

	DataPublics::loadQueryToComboBox("SELECT * FROM suppliers", "SupplierName" ,
					 QSqlDatabase::database(), ui->PreferredSupplier
					 );
	DataPublics::loadQueryToComboBox("SELECT ItemName FROM inventory WHERE ItemName != '" + ui->ItemName->text() + "'"
					 , "ItemName", QSqlDatabase::database(), ui->cboParent);
	isAdding = false;
	ui->checkBox_2->setVisible(false);
	ui->cboParent->setVisible(false);
}

InventoryEditor::~InventoryEditor()
{
	delete ui;
}

void InventoryEditor::Save()
{
	if (isAdding) {
		QSqlQuery qu = QSqlDatabase::database().exec("INSERT INTO inventory (ItemName) VALUES('New Item')");
		if (qu.lastError().isValid()) {
			DataPublics::showWarning(qu.lastError().text());
			return;
		}
		currentID = qu.lastInsertId().toString();
	}
	QString parentID = "";
	QString isActive = "No";
	QString supplierID = "";

	supplierID = DataPublics::getDbValue(
				"SELECT * FROM suppliers WHERE SupplierName = '" + ui->PreferredSupplier->currentText()
				+ "'", QSqlDatabase::database(), "SupplierID"
				).toString();

	if (ui->checkBox_2->isChecked()) {
		parentID = DataPublics::getDbValue(
					"SELECT * FROM inventory WHERE ItemName = '" + ui->cboParent->currentText()
					+ "'", QSqlDatabase::database(), "ItemID"
					).toString();
	}

	if (ui->checkBox->isChecked())
		isActive = "Yes";

	QString query = "UPDATE inventory SET "
			+ DataPublics::addLineEditToUpdate(ui->ItemName) + ", "
			// + DataPublics::addLineEditToUpdate(ui->OurNumber) + ", "
			//  + DataPublics::addLineEditToUpdate(ui->ManufacturerNumber) + ", "
			//  + DataPublics::addLineEditToUpdate(ui->OnHand) + ", "
			//  + DataPublics::addLineEditToUpdate(ui->ReorderLevel) + ", "
			+ DataPublics::addTextEditToUpdate(ui->Description) + ", "
			//  + DataPublics::addComboBoxToUpdate(ui->UOM) + ", "
			+ " ParentID = '" + parentID + "', "
			+ " isActive = '" + isActive + "', "
			+ " unitPrice = '" + QString::number(ui->spinPrice->value()) + "', "
			+ " preferredSupplier = '" + supplierID + "' WHERE ItemID = '" + currentID + "'";

	QSqlQuery qu = QSqlDatabase::database().exec(query);
	if (!qu.lastError().isValid()) {
		this->accept();
	} else {
		DataPublics::showWarning(qu.lastError().text());
	}

}

void InventoryEditor::Edit()
{
	isAdding = false;
	QSqlQuery qu = QSqlDatabase::database().exec("SELECT * FROM inventory WHERE ItemID = '" +
						     currentID + "'"
						     );
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}

	qu.first();

	DataPublics::bindLineEditToQuery(ui->ItemName, qu);
	// DataPublics::bindComboBoxToQuery(ui->UOM, qu);
	DataPublics::bindForeignComboToQuery(ui->PreferredSupplier, qu,
					     "SupplierID", "SupplierName", "Suppliers"
					     );
	// DataPublics::bindLineEditToQuery(ui->OurNumber, qu);
	// DataPublics::bindLineEditToQuery(ui->ManufacturerNumber, qu);
	// DataPublics::bindLineEditToQuery(ui->OnHand, qu);
	// DataPublics::bindLineEditToQuery(ui->ReorderLevel, qu);

	ui->checkBox_2->setChecked(false);
	if (qu.record().value("ParentID").toString().length() > 0) {
		//Has a parent
		QString parentName =
				DataPublics::getDbValue("SELECT * FROM inventory WHERE ItemID = '" + qu.record().value("ParentID").toString() + "'"
							, QSqlDatabase::database(), "ItemName"
							).toString();
		if(parentName.length() > 0) {
			ui->checkBox_2->setChecked(true);
			for (int i = 0; i < ui->cboParent->count(); i++) {
				if (ui->cboParent->itemText(i) == parentName)
					ui->cboParent->setCurrentIndex(i);
			}
		}
	}

	ui->checkBox->setChecked(qu.record().value("IsActive").toString() == "Yes");
	ui->spinPrice->setValue(qu.record().value("UnitPrice").toDouble());
}


void InventoryEditor::StartAddNew()
{
	isAdding = true;
}


void InventoryEditor::on_cmdDelete_clicked()
{

}

void InventoryEditor::on_cmdSave_clicked()
{

}
