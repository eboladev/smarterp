#include "suppliers.h"
#include "ui_suppliers.h"
#include "datapublics.h"
Suppliers::Suppliers(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Suppliers)
{
	ui->setupUi(this);
	db = QSqlDatabase::database();
	reloadSuppliers();
	isAdding = true;
}

Suppliers::~Suppliers()
{
	delete ui;
}

void Suppliers::reloadSuppliers()
{
	ui->trvSuppliers->setQuery("SELECT SupplierID, SupplierName as `Company Name` FROM suppliers"
				   , db, "Suppliers", true
				   );
	ui->trvSuppliers->setColumnHidden(0, true);
}

void Suppliers::on_trvSuppliers_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString suppID = ui->trvSuppliers->getCurrentID();
	if (suppID.length() > 0) {
		isAdding = false;
		currentID = suppID;
		QSqlQuery qu = QSqlDatabase::database().exec("SELECT * FROM suppliers WHERE SupplierID = '" + suppID + "'");
		if (!qu.lastError().isValid()) {
			qu.first();
			DataPublics::bindLineEditToQuery(ui->SupplierNo, qu);
			DataPublics::bindLineEditToQuery(ui->SupplierName, qu);
			DataPublics::bindLineEditToQuery(ui->Telephone, qu);
			DataPublics::bindTextEditToQuery(ui->Address, qu);
			DataPublics::bindLineEditToQuery(ui->Email, qu);
			DataPublics::bindLineEditToQuery(ui->ContactName, qu);
			DataPublics::bindLineEditToQuery(ui->Fax, qu);
			DataPublics::bindLineEditToQuery(ui->Mobile, qu);
		}
		ui->trvItemList->invisibleRootItem()->takeChildren();
		QSqlQuery qu2 = db.exec("SELECT * FROM store_requisition_master WHERE SupplierID = '" + currentID + "'");
		if (!qu2.lastError().isValid()) {
			while (qu2.next()) {
				QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvItemList);
				it->setText(0, qu2.record().value("EntryID").toString());
				it->setText(1, qu2.record().value("RequisitionDate").toString());
				it->setText(2, qu2.record().value("RequestedBy").toString());
				it->setText(3, qu2.record().value("Department").toString());
				it->setText(4, qu2.record().value("DateRequired").toString());
				it->setText(4, qu2.record().value("Status").toString());
				QString cnt = "0";
				cnt = DataPublics::getDbValue("SELECT COUNT(EntryID) AS cnt FROM store_requisition_detail WHERE MasterID = '" + qu2.record().value("EntryID").toString() + "'").toString();
				it->setText(5, cnt);
			}
		}
	}

}

void Suppliers::on_cmdSave_clicked()
{
	if (ui->SupplierName->text().trimmed().length() < 2) {
		DataPublics::showWarning("Please enter a supplier name to continue.");
		return;
	}
	if (isAdding) {
		QSqlQuery qu = QSqlDatabase::database().exec("INSERT INTO suppliers (SupplierNo) VALUES (0)");
		if (qu.lastError().isValid())
		{
			DataPublics::showWarning(qu.lastError().text());
			return;
		}
		currentID = qu.lastInsertId().toString();
		isAdding = false;
		on_cmdSave_clicked();
	} else {
		QString saveQuery = "UPDATE suppliers SET "
				+ DataPublics::addLineEditToUpdate(ui->SupplierNo) + ", "
				+ DataPublics::addLineEditToUpdate(ui->SupplierName) + ", "
				+ DataPublics::addLineEditToUpdate(ui->Telephone) + ", "
				+ DataPublics::addLineEditToUpdate(ui->Email) + ", "
				+ DataPublics::addLineEditToUpdate(ui->ContactName) + ", "
				+ DataPublics::addTextEditToUpdate(ui->Address) + ", "
				+ DataPublics::addLineEditToUpdate(ui->Fax) + ", "
				+ DataPublics::addLineEditToUpdate(ui->Mobile) + " WHERE SupplierID = '" + currentID + "'";

		QSqlQuery qu = QSqlDatabase::database().exec(saveQuery);
		if (qu.lastError().isValid())
		{
			DataPublics::showWarning(qu.lastError().text());
			return;
		} else {
			//Save successful
			reloadSuppliers();
		}
	}
}

void Suppliers::on_cmdAddNew_clicked()
{
	isAdding = true;
	DataPublics::clearInputs(ui->widget);
}

void Suppliers::on_cmdDelete_clicked()
{
	if (!isAdding) {
		if (currentID.length() > 0) {
			if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this supplier?",
						  QMessageBox::Yes, QMessageBox::No
						  ) == QMessageBox::Yes) {
				QSqlQuery qu = QSqlDatabase::database().exec("DELETE FROM suppliers WHERE SupplierID = '" + currentID + "'");
				if (qu.lastError().isValid())
				{
					DataPublics::showWarning(qu.lastError().text());
					return;
				}  else {
					reloadSuppliers();
					on_cmdAddNew_clicked();
				}
			}
		}
	}
}
