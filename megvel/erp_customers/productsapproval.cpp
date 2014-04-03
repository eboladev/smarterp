#include "productsapproval.h"
#include "ui_productsapproval.h"

ProductsApproval::ProductsApproval(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::ProductsApproval)
{
	ui->setupUi(this);
	db = database;
	reloadCustomers();
	QSettings sett2(qApp->organizationName(), qApp->applicationName());
	ui->splitter->restoreState(sett2.value("SmartERP/Megvel/Customers/Approvals/splitter1").toByteArray());
	ui->splitter_2->restoreState(sett2.value("SmartERP/Megvel/Customers/Approvals/splitter2").toByteArray());
}

ProductsApproval::~ProductsApproval()
{
	QSettings sett2(qApp->organizationName(), qApp->applicationName());
	sett2.setValue("SmartERP/Megvel/Customers/Approvals/splitter1", ui->splitter->saveState());
	sett2.setValue("SmartERP/Megvel/Customers/Approvals/splitter2", ui->splitter_2->saveState());

	delete ui;
}

void ProductsApproval::setDatabase(QSqlDatabase database)
{
	db = database;
}

void ProductsApproval::reloadCustomers()
{
	ui->trvCustomers->setQuery("SELECT CustomerID, CompanyName FROM customers ORDER BY CompanyName", db, "Customers", true);
	ui->trvCustomers->setColumnHidden(0, true);
}

void ProductsApproval::loadProducts()
{
	ui->lblCustomerName->setText(DataPublics::getDbValue("SELECT CompanyName FROM customers WHERE CustomerID = '" + currentCustomerID + "'", db, "CompanyName").toString());
	ui->trvApprovedProducts->invisibleRootItem()->takeChildren();
	for (int i = ui->tblUnapproved->rowCount(); i > -1; i--) {
		ui->tblUnapproved->removeRow(i);
	}
	QSqlQuery qu = db.exec("SELECT * FROM products WHERE Customer = '" + currentCustomerID + "'");
	while (qu.next()) {
		QTreeWidgetItem *it = new QTreeWidgetItem(0);
		it->setText(0, qu.record().value("Product Code").toString());
		it->setText(1, qu.record().value("Product").toString());
		it->setText(2, qu.record().value("Spec").toString());
		it->setText(3, qu.record().value("RetailPrice").toString());
		it->setText(4, qu.record().value("Price").toString());
		it->setText(99, qu.record().value("Product ID").toString());
		it->setCheckState(0, Qt::Unchecked);
		if (qu.record().value("DirectorApproved").toString() == "Yes") {
			//Approved
			ui->trvApprovedProducts->invisibleRootItem()->addChild(it);
		} else {
			//Not approved
			//ui->trvUnapprovedProducts->invisibleRootItem()->addChild(it);
			int row = ui->tblUnapproved->rowCount();
			ui->tblUnapproved->insertRow(row);
			QTableWidgetItem *checkItem = new QTableWidgetItem(1);
			QTableWidgetItem *codeItem = new QTableWidgetItem(1);
			codeItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *nameItem = new QTableWidgetItem(1);
			nameItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *specItem = new QTableWidgetItem(1);
			specItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *wtItem = new QTableWidgetItem(1);
			wtItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *rpItem = new QTableWidgetItem(1);
			rpItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *priceItem = new QTableWidgetItem(1);
			priceItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *idItem = new QTableWidgetItem(1);
			idItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *commentItem = new QTableWidgetItem(1);

			checkItem->setCheckState(Qt::Unchecked);
			codeItem->setText(qu.record().value("Product Code").toString());
			nameItem->setText(qu.record().value("Product").toString());
			specItem->setText(qu.record().value("Spec").toString());
			wtItem->setText(qu.record().value("WT").toString());
			rpItem->setText(qu.record().value("RetailPrice").toString());
			priceItem->setText(qu.record().value("Price").toString());
			idItem->setText(qu.record().value("Product ID").toString());
			commentItem->setText(qu.record().value("DirectorComment").toString());

			checkItem->setToolTip(qu.record().value("Product ID").toString());
			ui->tblUnapproved->setItem(row, 0, checkItem);
			ui->tblUnapproved->setItem(row, 1, codeItem);
			ui->tblUnapproved->setItem(row, 2, nameItem);
			ui->tblUnapproved->setItem(row, 3, specItem);
			ui->tblUnapproved->setItem(row, 4, wtItem);
			ui->tblUnapproved->setItem(row, 6, priceItem);
			ui->tblUnapproved->setItem(row, 5, rpItem);
			ui->tblUnapproved->setItem(row, 7, commentItem);
			ui->tblUnapproved->setItem(row, 99, idItem);
		}
	}
	ui->tblUnapproved->resizeColumnsToContents();
	ui->tblUnapproved->resizeRowsToContents();
}

void ProductsApproval::on_trvCustomers_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString id = ui->trvCustomers->getCurrentID();
	if (id.length() > 0) {
		currentCustomerID = id;
		on_cmdApprove_clicked();
		// loadProducts();
	}
}

void ProductsApproval::on_cmdApprove_clicked()
{
	for (int i = 0; i < ui->tblUnapproved->rowCount(); i++) {
		QTableWidgetItem *child = ui->tblUnapproved->item(i, 0);
		QString id = child->toolTip();
		if (child->checkState() == Qt::Checked) {
			db.exec("UPDATE products SET DirectorApproved = 'Yes', DirectorComment = '' WHERE `Product Id` = '" + id + "'");
		} else {
			db.exec("UPDATE products SET DirectorComment = '" +  ui->tblUnapproved->item(i, 7)->text() + "' WHERE `Product Id` = '" + id + "'");
		}
	}
	loadProducts();
}

void ProductsApproval::on_cmdUnapprove_clicked()
{
	for (int i = 0; i < ui->trvApprovedProducts->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *child = ui->trvApprovedProducts->invisibleRootItem()->child(i);
		if (child->checkState(0) == Qt::Checked) {
			QString id = child->text(99);
			db.exec("UPDATE products SET DirectorApproved = 'No' WHERE `Product Id` = '" + id + "'");
		}
	}
	loadProducts();
}
