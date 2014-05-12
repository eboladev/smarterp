#include "crmmainwindow.h"
#include "ui_crmmainwindow.h"
#include "customereditor.h"
#include "datapublics.h"
#include "producteditor.h"
#include "generatejobticket.h"
#include "newlpo.h"

CRMMainWindow::CRMMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CRMMainWindow)
{
	ui->setupUi(this);
	db = QSqlDatabase::database("closures");
	ui->splitter->restoreState(DataPublics::getSettingValue("Customers/MainSplitter").toByteArray());
	reloadCustomers();
}

CRMMainWindow::~CRMMainWindow()
{
	DataPublics::setSettingValue("Customers/MainSplitter", ui->splitter->saveState());
	delete ui;
}

void CRMMainWindow::reloadCustomers()
{
	QString query = "SELECT CustomerID,  AccountNumber as `Account No`, CompanyName as `Company Name` FROM customers WHERE Deleted = 'No'";

	qDebug() << query;
	ui->trvCustomers->setQuery(query, db, "Customers", true);
	ui->trvCustomers->setColumnHidden(0, true);
	ui->trvCustomers->sortByColumn(2);
}

void CRMMainWindow::reloadProducts()
{
	QString productsQuery = "SELECT * FROM `vw_products_basic`   WHERE `customer_id` = '" + customerID + "'";
	QSqlQuery qu = db.exec(productsQuery);

	if (!qu.lastError().isValid()) {
		for (int i = ui->tblProducts->rowCount(); i > -1; i--) {
			ui->tblProducts->removeRow(i);
		}
		while (qu.next()) {
			QTableWidgetItem *codeItem = new QTableWidgetItem(1);
			QTableWidgetItem *nameItem = new QTableWidgetItem(1);
			nameItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *pIDItem = new QTableWidgetItem(1);
			pIDItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

			QTableWidgetItem *idItem = new QTableWidgetItem(1);
			idItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

			QTableWidgetItem *weightItem = new QTableWidgetItem(1);
			weightItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

			QTableWidgetItem *printedItem = new QTableWidgetItem(1);
			printedItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

			QTableWidgetItem *colorItem = new QTableWidgetItem(1);
			colorItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


			QTableWidgetItem *rpItem = new QTableWidgetItem(1);
			rpItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *priceItem = new QTableWidgetItem(1);
			priceItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *approvedItem = new QTableWidgetItem(1);
			approvedItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QTableWidgetItem *approvalReasonItem = new QTableWidgetItem(1);
			approvalReasonItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

			codeItem->setText(qu.record().value("product_code").toString());
			codeItem->setCheckState(Qt::Unchecked);
			nameItem->setText(qu.record().value("product_name").toString());

			approvedItem->setText(qu.record().value("approved").toString());
			approvalReasonItem->setText(qu.record().value("director_comment").toString());
			weightItem->setText(qu.record().value("wt").toString());
			printedItem->setText(qu.record().value("printed").toString());
			colorItem->setText(qu.record().value("color_name").toString());
			priceItem->setText(qu.record().value("price_per_piece").toString());
			pIDItem->setText(qu.record().value("product_id").toString());

			int row  = ui->tblProducts->rowCount();
			ui->tblProducts->insertRow(row);

			ui->tblProducts->setItem(row, 0, codeItem);
			ui->tblProducts->setItem(row, 1, nameItem);
			ui->tblProducts->setItem(row, 2, printedItem);
			ui->tblProducts->setItem(row, 3, colorItem);
			ui->tblProducts->setItem(row, 4, priceItem);
			ui->tblProducts->setItem(row, 5, weightItem);
			ui->tblProducts->setItem(row, 6, approvedItem);
			ui->tblProducts->setItem(row, 7, approvalReasonItem);
			ui->tblProducts->setItem(row, 8, pIDItem);

			ui->tblProducts->setColumnHidden(8, true);

			QColor redColor(255, 57, 0);
			QColor greenColor(24, 155, 4);
			QColor col = greenColor;
			if (qu.record().value("approved").toString() != "Yes") {
				col = redColor;
			}
			//for (int i = 0; i < ui->tblProducts->rowCount(); i++) {
			for (int c = 0; c < ui->tblProducts->columnCount(); c++) {
				ui->tblProducts->item(row, c)->setBackgroundColor(col);
			}
			//}
		}
		ui->tblProducts->resizeColumnsToContents();
		ui->tblProducts->resizeRowsToContents();

		current_product_row = -1;
	} else {
		DataPublics::showWarning(qu.lastError().text());
	}
}

void CRMMainWindow::reloadOrders()
{
	ui->trvOrders->setQuery("SELECT entry_id, product_code as 'Product Code', product_name as 'Product',"
				" lpo_no as 'LPO Number', order_date as 'Order Date', required_date as 'Required Date',"
				" order_qty as 'Order Qty', price_per_piece as 'Price/Pc', price_per_k as 'Price/1000',"
				" total_price as 'Total Price', packing as 'Packing', caps_per_pack as 'Caps/Pack',"
				" hdpe as 'HDPE', master_batch as 'MB', inks as 'INKS' FROM oc WHERE customer_id = '" + customerID + "'"
				, db, "Orders", true);
	ui->trvCustomers->setColumnHidden(0, true);
}

void CRMMainWindow::on_trvCustomers_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	CustomerEditor *ed = new CustomerEditor(this);
	ed->edit(customerID);
	connect (ed, SIGNAL(reload()), SLOT(reloadCustomers()));
	if (ed->exec() == QDialog::Accepted) {
		reloadCustomers();
	}
}

void CRMMainWindow::on_trvCustomers_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	customerID = ui->trvCustomers->getCurrentID();
	reloadProducts();
	reloadOrders();
}

void CRMMainWindow::on_cmdNewCustomer_clicked()
{
	CustomerEditor *ed = new CustomerEditor(this);
	connect (ed, SIGNAL(reload()), SLOT(reloadCustomers()));
	if (ed->exec()) {
		reloadCustomers();
	}
}

void CRMMainWindow::on_cmdNewProduct_clicked()
{
	ProductEditor *ed = new ProductEditor(this);
	connect (ed, SIGNAL(changed()), SLOT(reloadProducts()));
	ed->StartNew(customerID);
	if (ed->exec()) {
		reloadProducts();
	}
}

void CRMMainWindow::on_tblProducts_itemDoubleClicked(QTableWidgetItem *item)
{
	int row = item->row();
	productID = ui->tblProducts->item(row, 8)->text();
	ProductEditor *ed = new ProductEditor(this);
	connect (ed, SIGNAL(changed()), SLOT(reloadProducts()));
	ed->Edit(productID);
	if (ed->exec()) {
		reloadProducts();
	}
}

void CRMMainWindow::on_cmdGenerateJobTicket_clicked()
{
	if (productID.length() < 1) {
		DataPublics::showWarning("Please select a product.");
		return;
	}
	GenerateJobTicket *jt = new GenerateJobTicket(this, productID);
	if (jt->exec()) {

	}
}

void CRMMainWindow::on_tblProducts_itemClicked(QTableWidgetItem *item)
{
	int row = item->row();
	productID = ui->tblProducts->item(row, 8)->text();
}

#include "../reportpreview.h"
void CRMMainWindow::on_trvOrders_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString orderID = ui->trvOrders->getCurrentID();
	if (orderID.length() > 0) {
		ReportPreview(this, db, "oc", " WHERE entry_id = '" + orderID + "'");

	}
}
