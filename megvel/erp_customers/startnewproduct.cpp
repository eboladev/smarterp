#include "startnewproduct.h"
#include "ui_startnewproduct.h"
#include "datapublics.h"
StartNewProduct::StartNewProduct(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::StartNewProduct)
{
	ui->setupUi(this);
	ui->cboSFK->setCurrentIndex(1);
	db = database;
	DataPublics::loadQueryToComboBox("SELECT CompanyName FROM customers ORDER BY CompanyName ASC", "CompanyName", db, ui->cboCustomer);
}

StartNewProduct::~StartNewProduct()
{
	delete ui;
}

void StartNewProduct::setCustomer(QString customerName)
{
	for (int i = 0;i < ui->cboCustomer->count(); i++) {
		//qDebug() << ui->cboCustomer->itemText(i) << customerName;
		if (ui->cboCustomer->itemText(i) == customerName) {
			ui->cboCustomer->setCurrentIndex(i);
			return;
		}
	}
}

void StartNewProduct::on_cmdNext_clicked()
{
	if (ui->txtProductName->text().length() < 2) {
		DataPublics::showWarning("Please enter the product name.");
		return;
	}

	QString custID = DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" +
						 ui->cboCustomer->currentText() + "'"
						 , db, "CustomerID"
						 ).toString();

	QSqlQuery qu = db.exec("INSERT INTO products (Customer, Product, PL) VALUES('"
			       + custID + "', '"
			       + ui->txtProductName->text() + "', '"
			       + ui->cboSFK->currentText() + "')");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning("There was an error while saving the product:\n\n" + qu.lastError().text());
		return;
	}

	QString newProdID = qu.lastInsertId().toString();

	emit saved(newProdID);
	this->accept();
}
