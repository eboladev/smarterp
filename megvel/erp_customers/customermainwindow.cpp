#include "customermainwindow.h"
#include "customers.h"
#include "datapublics.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "ocs.h"
#include <QSqlDatabase>
#include "ui_customermainwindow.h"
#include "utils/stylehelper.h"
#include "productsapproval.h"
#include "purchaseorders.h"
#include "ocregister.h"
#include "proformalist.h"
CustomerMainWindow::CustomerMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::CustomerMainWindow)
{
	ui->setupUi(this);
	Utils::StyleHelper::setBaseColor(QColor(128,128,128));
	db = database;

	cust = new Customers(this, db);
	connect (cust, SIGNAL(emitDb(QSqlDatabase)), SLOT(receiveDb(QSqlDatabase)));
	prod = new ProductsApproval(this, db);
	lpos = new PurchaseOrders(this, db);
	prof = new ProformaList(this, db);

	bool canApprove = DataPublics::getUserPermission("Approve Products", db);
	bool seeCustomers = DataPublics::getUserPermission("View Customers", db);
	bool seeProformas = DataPublics::getUserPermission("View Proforma Invoices", db);
	bool seeLPOs = DataPublics::getUserPermission("Generate LPOs", db);

	isQc =DataPublics::getUserPermission("QcView", db);

	ocs = new OcRegister(this, db);
	if (seeCustomers) {
		ui->centralwidget->insertTab(cust);
		ui->centralwidget->insertTab(ocs);
	}
	if (canApprove)
		ui->centralwidget->insertTab(prod);

	if (seeLPOs)
		ui->centralwidget->insertTab(lpos);

	if (seeProformas)
		ui->centralwidget->insertTab(prof);



	connect (ui->centralwidget, SIGNAL(currentTextChanged(QString)), SLOT(pageChanged(QString)));
}

CustomerMainWindow::~CustomerMainWindow()
{
	delete ui;
}

void CustomerMainWindow::receiveDb(QSqlDatabase database)
{
	db = database;
	db.setDatabaseName("cartons");

	prod->setDatabase(db);
	lpos->setDatabase(db);
	prof->setDatabase(db);
	ocs->setDatabase(db);
}

void CustomerMainWindow::pageChanged(QString newPage)
{
	//qDebug() << newPage + " has been selected.";
	if (newPage == "Customers") {
		cust->reloadCustomers();
	} else if (newPage == "OC Register") {
		ocs->on_cmdShowOcs_clicked();
		//ocs->reloadHistory();
	} else if (newPage == "Proformas") {
		prof->reloadProformas();
	} else if (newPage == "LPOs") {
		lpos->reloadCustomers();
		lpos->reloadAllOrders();
	}
}
