#include "customers.h"
#include "ui_customers.h"
#include "datapublics.h"

#include "customereditor.h"
#include "editproduct.h"

Customers::Customers(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Customers)
{
	ui->setupUi(this);
	current_product_row = -1;
	db = database;
	isQc = DataPublics::getUserPermission("QcView", db);
	ui->splitter->restoreState(DataPublics::getSettingValue("Customers/MainSplitter").toByteArray());

	m_productsModel = new ProductsModel(this);
	m_productsSorter = new QSortFilterProxyModel(this);
	m_productsSorter->setSourceModel(m_productsModel);
	m_productsSorter->setSortCaseSensitivity(Qt::CaseInsensitive);
	m_productsSorter->setFilterCaseSensitivity(Qt::CaseInsensitive);
	m_productsSorter->setFilterKeyColumn(-1);
	ui->tblProducts->setModel(m_productsSorter);


	m_customersModel = new CustomersModel(this);
	m_customersSorter = new QSortFilterProxyModel(this);
	m_customersSorter->setSourceModel(m_customersModel);
	m_customersSorter->setSortCaseSensitivity(Qt::CaseInsensitive);
	m_customersSorter->setFilterCaseSensitivity(Qt::CaseInsensitive);
	m_customersSorter->setFilterKeyColumn(-1);
	ui->tblCustomers->setModel(m_customersSorter);


	connect (ui->tblProducts->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex))
		 , SLOT(currentProductChanged(QModelIndex,QModelIndex)));

	connect (ui->tblCustomers->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
		 SLOT(currentCustomerChanged(QModelIndex,QModelIndex)));

	reloadCustomers();

	tenSecondTimer = new QTimer(this);
	connect (tenSecondTimer, SIGNAL(timeout()), SLOT(keepDbAlive()));
	tenSecondTimer->start(10000);

	ui->lblExport->setVisible(false);

	if (isQc) {
		ui->cmdCostingCalc->setEnabled(false);
		ui->cmdGenerateJobTicket->setEnabled(false);
		ui->cmdNewCustomer->setEnabled(false);
		ui->cmdNewProduct->setEnabled(false);
		ui->cmdProforma->setEnabled(false);
	}
}
Customers::~Customers()
{
	DataPublics::setSettingValue("Customers/MainSplitter", ui->splitter->saveState());
	delete ui;
}

void Customers::reloadCustomers()
{
	QString salesRep = DataPublics::getDbValue(
				"SELECT FullName FROM users WHERE UserID = '" + DataPublics::getCurrentUserID() + "'"
				, db, "FullName").toString();
	QString query = "SELECT * FROM vw_cust ORDER BY `Company Name` Asc";

	if (!DataPublics::checkUserAccess("View All Customers", db)) {
		//qDebug() << "Not allowed to view all customers.";
		query = "SELECT CustomerID, `Company Name`, `Account No`  FROM vw_cust WHERE `Sales Rep` = '" + salesRep + "' OR `Secondary Sales Rep` = '" + salesRep + "' ORDER BY `Company Name`";
	}

	m_customersModel->setQuery(query, db);
	ui->txtCustomerSearch->setText("");

	ui->tblCustomers->setColumnHidden(0, true);
	ui->tblCustomers->resizeColumnsToContents();
	ui->tblCustomers->resizeRowsToContents();
}

void Customers::currentProductChanged(QModelIndex newIndex, QModelIndex oldIndex)
{
	Q_UNUSED(oldIndex);
	productID = newIndex.model()->index(newIndex.row(), 0).data().toString();
}

void Customers::reloadProducts()
{
	if (isQc) {
		m_productsModel->setQuery("SELECT `Product ID`, `Product Code`, Product, "
					  "PL as 'Type', ID, BL, BW, GSM, WT FROM products   WHERE `customer` = '" + customerID + "'"
					  , db);
	} else {
		//
		m_productsModel->setQuery("SELECT `Product ID`, `Product Code`, Product, RetailPrice as 'RP', Price, "
					  "PL as 'Type', ID, BL, BW, GSM, WT, DirectorApproved as 'Approved' FROM products   WHERE `customer` = '" + customerID + "'"
					  , db);

	}
	ui->txtProductsSearch->setText("");
	m_productsSorter->setFilterCaseSensitivity(Qt::CaseInsensitive);
	m_productsSorter->setFilterKeyColumn(-1);
	//productsSorter->sort(0, Qt::AscendingOrder);
	ui->tblProducts->setColumnHidden(0, true);
	ui->tblProducts->resizeColumnsToContents();
	ui->tblProducts->resizeRowsToContents();
}

void Customers::reloadOrders()
{
	ui->trvOrders->setQuery("SELECT TicketNo as 'OC #',Date,  Client, Product, "
				"CONCAT(Qty, 'x', ROUND(Weight, 3)) AS 'Weight', Round(Tons, 3) AS 'Tons' "
				"FROM newreport WHERE Client LIKE '%" + ui->lblCustName->text() + "'", db, "Order List (" + ui->lblCustName->text() + ")", false);
	QStringList srt;
	srt << "Tons";
	ui->trvOrders->addSumColumns(srt);
}

void Customers::customerChanged()
{
	companyName = DataPublics::getDbValue("SELECT * FROM vwcustomers WHERE CustomerID = '" + customerID + "'", db, "Company Name").toString();
	ui->lblCustName->setText(companyName);
	reloadProducts();
	reloadOrders();
}




void Customers::on_cmdNewCustomer_clicked()
{
	CustomerEditor *ed = new CustomerEditor(this, db);

	if (ed->exec() == QDialog::Accepted) {
		reloadCustomers();
	}
}



#include "startnewproduct.h"
void Customers::on_cmdNewProduct_clicked()
{
	StartNewProduct *st = new StartNewProduct(this, db);
	st->setCustomer(companyName);
	connect (st, SIGNAL(saved(QString)), this, SLOT(editProduct(QString)));
	st->exec();
}

void Customers::editProduct(QString m_productID)
{
	productID = m_productID;
	EditProduct *prg = new  EditProduct(this, db);
	connect (prg, SIGNAL(changed()), this, SLOT(reloadProducts()));
	prg->Edit(productID);
	prg->exec();
}

#include "generatejobtickets.h"
void Customers::on_cmdGenerateJobTicket_clicked()
{    
	if (productID.length() > 0) {

		QString approved = DataPublics::getDbValue("SELECT * FROM products WHERE `Product Id` = '" + productID + "'", db, "DirectorApproved").toString();

		if (approved == "No") {
			DataPublics::showWarning("This product has not been approved.");
			return;
		}

		GenerateJobTickets *gen = new GenerateJobTickets(this, db, productID);
		if (gen->exec() == QDialog::Accepted)
			reloadOrders();

	} else {
		DataPublics::showWarning("Please select a product.");
	}
}

#include "generateproformainvoice.h"
void Customers::on_cmdProforma_clicked()
{

	int ticked = 0;
	GenerateProformaInvoice *gen = new GenerateProformaInvoice(this, db);
	gen->setCustomerID(customerID);

	for (int i = 0; i < m_productsModel->rowCount(); i++) {
		QModelIndex codeColumnIndex = m_productsModel->index(i, 1);
		QModelIndex idColumnIndex = m_productsModel->index(i, 0);
		if (codeColumnIndex.data(Qt::CheckStateRole) == Qt::Checked) {
			ticked ++;
			gen->addProduct(idColumnIndex.data().toString());
		}
	}

	if (ticked > 0) {
		gen->exec();
	} else {
		DataPublics::showWarning("Please select products to use.");
		return;
	}
}

void Customers::keepDbAlive()
{
	qDebug() << "Checking db availability...";
	if (db.isOpen()) {
		qDebug() << "Db is open. Running a test query.";
		db.exec("SELECT NOW()");
		if (db.lastError().isValid()) {
			qDebug() << "Test query failed.";
			reconnectDb();
		} else {
			qDebug() << "Test query successful. All is OK";
		}
	} else {
		qDebug() << "Db not open.";
		reconnectDb();
	}
}

void Customers::reconnectDb()
{
	QString uName, hName, pWord;
	uName = db.userName();
	hName = db.hostName();
	pWord = db.password();
	QSqlDatabase testDb = QSqlDatabase::addDatabase("QMYSQL", "customersConnection");
	testDb.setHostName(hName);
	testDb.setUserName(uName);
	testDb.setPassword(pWord);
	testDb.setDatabaseName("cartons");
	qDebug() << "Reconnecting...";
	if (!testDb.open()) {
		qDebug() << "Reconnection failed.";
	}else {
		db = testDb;
		db.setDatabaseName("cartons");
		//emitDb(testDb);
		qDebug() << "Db Reconnected";
	}
}

void Customers::on_lblExport_linkActivated(const QString &link)
{
	Q_UNUSED(link);
	CustomQueryView *cust = new CustomQueryView(0);
	cust->setVisible(false);
	cust->setQuery( "SELECT `Product ID`, `Product Code`, Product, RetailPrice as 'RP', Price, "
			"PL as 'Type', ID, BL, BW, GSM, WT, DirectorApproved as 'Approved' FROM products   WHERE `customer` = '" + customerID + "'", db, "Product list for " + ui->lblCustName->text(), true);
	cust->actionExport();
	delete(cust);
}

void Customers::on_tblProducts_clicked(const QModelIndex &index)
{
	productID = index.model()->index(index.row(), 0).data().toString();
	if (index.row() == 1) {
		bool checkedAlready = index.data(Qt::CheckStateRole).toBool();
		if (checkedAlready) {
			m_productsModel->setData(index, Qt::Unchecked, Qt::CheckStateRole);
		} else {
			m_productsModel->setData(index, Qt::Checked, Qt::CheckStateRole);
		}
	}
}

void Customers::on_tblProducts_doubleClicked(const QModelIndex &index)
{
	if (isQc)
		return;

	productID = index.model()->index(index.row(), 0).data().toString();
	editProduct(productID);
}


void Customers::currentCustomerChanged(QModelIndex newRow, QModelIndex oldRow)
{
	Q_UNUSED(oldRow);
	customerID = newRow.model()->index(newRow.row(), 0).data().toString();
	customerChanged();
}

#include "jobticketprinter.h"
void Customers::on_trvOrders_doubleClicked(const QModelIndex &index)
{
	if (isQc)
		return;

	QString ocNo = index.model()->index(index.row(), 0).data().toString();
	if (ocNo.length() > 0) {
		JobTicketPrinter(this, ocNo, db);
	}
}

void Customers::on_cmdCostingCalc_clicked()
{
	QSqlQuery qu = db.exec("INSERT INTO products (Product,  Customer, PL) VALUES "
			       "('Costing Calc " +  ui->lblCustName->text() + "','65866', '3 Ply')");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}

	QString prodID = qu.lastInsertId().toString();
	EditProduct *prod = new EditProduct(this, db, true);
	prod->Edit(prodID);
	prod->exec();
	db.exec("DELETE FROM products WHRE `Product ID` = '" + prodID + "'");
}

void Customers::on_tblCustomers_doubleClicked(const QModelIndex &index)
{
	if (isQc)
		return;

	Q_UNUSED(index);
	CustomerEditor *ed = new CustomerEditor(this, db);
	ed->edit(customerID);
	if (ed->exec() == QDialog::Accepted) {
		reloadCustomers();
	}
}

void Customers::on_txtProductsSearch_textChanged(const QString &arg1)
{
	//qDebug() << arg1;
	m_productsSorter->setFilterRegExp(arg1);
}

void Customers::on_txtCustomerSearch_textChanged(const QString &arg1)
{
	m_customersSorter->setFilterRegExp(arg1);
}

void Customers::on_trvOrders_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString ocNo = ui->trvOrders->getCurrentID();
	QString html;
	html += "<h2>Order Trail: " + ocNo + "</h2>";
	QString ocQuery = "SELECT * FROM newreport WHERE TicketNo = '" + ocNo + "'";
	html += QString("<p><b>Order Qty: </b> %1</p>").arg(DataPublics::getDbValue(ocQuery, db, "Qty").toString());

	QString finishingQuery = "SELECT OcNo, `Date`, Shift, Section, Produced FROM finishingdataentry WHERE Deleted = 'No' AND OcNo = '" + ocNo + "'";

	QSqlQuery quFinishing = db.exec(finishingQuery);

	if (quFinishing.size() > 0) {
		html += "<h3>Finishing Summary</h3>";
		html += "<table border=1 width=50%>";

		html += "<tr> <td><b>Date</b></td> <td><b>Shift</b></td> <td><b>Section</b></td> <td><b>Qty Produced</b></td></tr>";

		while (quFinishing.next()) {
			QSqlRecord rec = quFinishing.record();
			html += QString("<tr> <td>%1</td> <td>%2</td> <td>%3</td> <td>%4</td></tr>")
					.arg(rec.value("Date").toDate().toString("dd-MMM-yyyy")
					     , rec.value("Shift").toString()
					     , rec.value("Section").toString()
					     , rec.value("Produced").toString());
		}
		html += QString("<tr><td></td><td></td><td></td><td>%1</td></tr>")
				.arg(DataPublics::getDbValue("SELECT SUM(Produced) as 'Sum' FROM finishingdataentry WHERE Deleted = 'No' AND OcNo = '" + ocNo + "'", db , "Sum").toString());
		html += "</table>";
	}

	QString dispatchQuery = "SELECT JobTicketNumber, `Date`, InvoiceNumber, QtyDispatched,  DeliveryConfirmed, DeliveryDate,"
			" VehicleNo, DeliveryComment "
			"FROM dispatch WHERE JobTicketNumber = '" + ocNo + "'";
	QSqlQuery quDispatch = db.exec(dispatchQuery);

	if (quDispatch.size() > 0) {
		html += "<h3>Dispatch Summary</h3>";
		html += "<table border=1 width=70%>";

		html += "<tr> <td><b>Date</b></td> <td><b>Invoice No.</b></td> <td><b>Qty Dispatched</b></td> "
				"<td><b>Delivery Confirmed</b></td> "
				"<td><b>Delivery Date</b></td> "
				"<td><b>Vehicle Used</b></td> "
				"<td><b>Customer Comments</b></td> "
				"</tr>";

		while (quDispatch.next()) {
			QSqlRecord rec = quDispatch.record();
			html += QString("<tr> <td>%1</td> <td>%2</td> <td><b>%3</b></td> <td>%4</td> <td>%5</td> <td>%6</td> <td>%7</td></tr>")
					.arg(rec.value("Date").toDate().toString("dd-MMM-yyyy")
					     , rec.value("InvoiceNumber").toString()
					     , rec.value("QtyDispatched").toString()
					     , rec.value("DeliveryConfirmed").toString()
					     , rec.value("DeliveryDate").toString()
					     , rec.value("VehicleNo").toString()
					     , rec.value("DeliveryComment").toString());
		}
		html += QString("<tr><td>-</td><td>-</td><td><b>%1</b></td><td>-</td><td>-</td><td>-</td><td>-</td></tr>")
				.arg(DataPublics::getDbValue("SELECT SUM(QtyDispatched) as 'Sum' FROM dispatch WHERE JobTicketNumber = '" + ocNo + "'", db , "Sum").toString());
		html += "</table>";
	}



	ui->txtOrderDetails->setHtml(html);
}
