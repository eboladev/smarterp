#include "ims_suppliers.h"
#include "ui_ims_suppliers.h"
#include "rvrsuppliereditor.h"
ims_suppliers::ims_suppliers(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::ims_suppliers)
{
	ui->setupUi(this);
	db = database;
	reloadList();
}

ims_suppliers::~ims_suppliers()
{
	delete ui;
}

void ims_suppliers::reloadList()
{
	ui->lstSuppliers->setQuery("SELECT * FROM ims.vw_suppliers", db, "Suppliers (Import System)", true);
	ui->lstSuppliers->setColumnHidden(0, true);
}

void ims_suppliers::on_lstSuppliers_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString suppID = ui->lstSuppliers->getCurrentID();
	if (suppID.length() > 0) {
		RvrSupplierEditor *ed = new RvrSupplierEditor(this, db);
		ed->Edit(suppID);
		if (ed->exec() == QDialog::Accepted)
			reloadList();
	}
}

void ims_suppliers::on_cmdNewSupplier_clicked()
{
	RvrSupplierEditor *ed = new RvrSupplierEditor(this, db);
	ed->AddNew();
	if (ed->exec() == QDialog::Accepted)
		reloadList();
}

void ims_suppliers::on_cmdDeleteSupplier_clicked()
{
	QString suppID = ui->lstSuppliers->getCurrentID();
	if (suppID.length() > 0) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this supplier?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM ims.suppliers WHERE EntryID = '" + suppID + "'");
			if (db.lastError().isValid()) {
				DataPublics::showWarning(db.lastError().text());
			} else {
				reloadList();
			}
		}
	}
}
