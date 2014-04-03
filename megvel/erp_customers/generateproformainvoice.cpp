#include "generateproformainvoice.h"
#include "ui_generateproformainvoice.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include "datapublics.h"
#include "qtprinter.h"
GenerateProformaInvoice::GenerateProformaInvoice(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::GenerateProformaInvoice)
{
	ui->setupUi(this);
	db = database;
}

GenerateProformaInvoice::~GenerateProformaInvoice()
{
	delete ui;
}
QString GenerateProformaInvoice::customerID() const
{
	return m_customerID;
}

void GenerateProformaInvoice::setCustomerID(const QString &customerID)
{
	m_customerID = customerID;
	QSqlQuery customerQu = db.exec("SELECT * FROM customers WHERE "
				       " CustomerID = '" + m_customerID + "'");
	while (customerQu.next()) {
		QString txt = customerQu.record().value("CompanyName").toString()
				+ "\n" + customerQu.record().value("Address").toString()
				+ "\n" + customerQu.record().value("Town").toString()
				+ "\n" + customerQu.record().value("Postcode").toString()
				+ "\n" + customerQu.record().value("Country").toString();

		ui->txtCustomer->setPlainText(txt);
		return;
	}
}

void GenerateProformaInvoice::addProduct(QString productID)
{
	QSqlQuery qu = db.exec("SELECT * FROM products WHERE `Product ID` = '" + productID + "'");
	qu.first();


	QSqlRecord rec = qu.record();

	QString spec = rec.value("Gram1").toString() +
			+ "/" + rec.value("Type1").toString() +
			+ " " + rec.value("Type2").toString() +
			+ "/" + rec.value("Type2").toString() +
			+ " " + rec.value("Type3").toString() +
			+ "/" + rec.value("Type3").toString();

	if (rec.value("PL").toString().contains("5")) {
		spec = spec + " " + rec.value("Type4").toString() +
				+ "/" + rec.value("Type4").toString() +
				+ " " + rec.value("Type5").toString() +
				+ "/" + rec.value("Type5").toString();
	}


	QTableWidgetItem *it_product =          new QTableWidgetItem(1);
	QTableWidgetItem *it_id =               new QTableWidgetItem(1);
	QTableWidgetItem *it_paper_spec =       new QTableWidgetItem(1);
	QTableWidgetItem *it_qty =              new QTableWidgetItem(1);
	QTableWidgetItem *it_packing =          new QTableWidgetItem(1);
	QTableWidgetItem *it_weight =           new QTableWidgetItem(1);
	QTableWidgetItem *it_package =          new QTableWidgetItem(1);
	QTableWidgetItem *it_unit_price =       new QTableWidgetItem(1);
	QTableWidgetItem *it_total_price =      new QTableWidgetItem(1);
	QTableWidgetItem *it_product_id =       new QTableWidgetItem(1);

	it_product->setText(qu.record().value("Product").toString());
	it_id->setText(qu.record().value("ID").toString());
	it_paper_spec->setText(spec);
	it_qty->setText("1");
	it_packing->setText("25");
	it_weight->setText(qu.record().value("WT").toString());
	it_package->setText("1");
	it_unit_price->setText(qu.record().value("Price").toString());
	it_total_price->setText(qu.record().value("Price").toString());
	it_product_id->setText(qu.record().value("Product ID").toString());

	int row = ui->tableWidget->rowCount();
	ui->tableWidget->insertRow(row);

	ui->tableWidget->setItem(row, 0, it_product);
	ui->tableWidget->setItem(row, 1, it_id);
	ui->tableWidget->setItem(row, 2, it_paper_spec);
	ui->tableWidget->setItem(row, 3, it_qty);
	ui->tableWidget->setItem(row, 4, it_packing);
	ui->tableWidget->setItem(row, 5, it_weight);
	ui->tableWidget->setItem(row, 6, it_package);
	ui->tableWidget->setItem(row, 7, it_unit_price);
	ui->tableWidget->setItem(row, 8, it_total_price);
	ui->tableWidget->setItem(row, 9, it_product_id);



	ui->tableWidget->setColumnHidden(9, true);
}

double GenerateProformaInvoice::round_nplaces(double &value, const uint32_t &to)
{
	double ret = value;
	uint32_t places = 1, whole = *(&ret);
	for(uint32_t i = 0; i < to; i++) places *= 10;
	ret -= whole; //leave decimals
	ret *= places;  //0.1234 -> 123.4
	ret  = round2(ret);//123.4 -> 123
	ret /= places;  //123 -> .123
	ret += whole; //bring the whole value back

	return ret;
}

void GenerateProformaInvoice::recalculateTotals()
{
	double d_totalWeight = 0;
	double d_totalPackage = 0;
	double d_totalAmount = 0;
	double d_totalPcs = 0;

	QString str_packing = "0";
	for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
		QString productID = ui->tableWidget->item(i, 9)->text();
		QString wt =
				DataPublics::getDbValue(
					"SELECT * FROM products WHERE `product id` = '"
					+ productID + "'", db, "WT").toString();
		QString pl =
				DataPublics::getDbValue(
					"SELECT * FROM products WHERE `product id` = '"
					+ productID + "'", db, "PL").toString();
		double d_qty = ui->tableWidget->item(i, 3)->text().toDouble();
		double d_unit_price = ui->tableWidget->item(i, 7)->text().toDouble();
		double d_packing = ui->tableWidget->item(i, 4)->text().toDouble();
		double d_wt = wt.toDouble();
		double d_package = (d_qty / d_packing );
		double d_price = 0;
		Q_UNUSED(pl);
		d_wt = ((d_wt * d_qty) * 1.5);
		d_price = d_qty * d_unit_price;

		ui->tableWidget->item(i, 5)->setText(QString::number(round_nplaces(d_wt)));
		ui->tableWidget->item(i, 8)->setText(QString::number(round_nplaces(d_price)));
		ui->tableWidget->item(i, 6)->setText(QString::number(round_nplaces(d_package, 0)));

		d_totalWeight = d_totalWeight + d_wt;
		d_totalPackage = d_totalPackage + d_package;
		d_totalAmount = d_totalAmount + d_price;
		d_totalPcs = d_totalPcs + d_qty;
	}



	ui->txtTotalWeight->setText(QString::number(round_nplaces(d_totalWeight)));
	ui->txtTotalPackage->setText(QString::number(round_nplaces(d_totalPackage, 0)));
	ui->txtTotalAmount->setText(QString::number(round_nplaces(d_totalAmount)));
	ui->txtTotalPcs->setText(QString::number(round_nplaces(d_totalPcs)));
}


void GenerateProformaInvoice::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	Q_UNUSED(currentColumn);
	Q_UNUSED(currentRow);
	Q_UNUSED(previousColumn);
	Q_UNUSED(previousRow);
	recalculateTotals();
}

void GenerateProformaInvoice::on_tableWidget_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	recalculateTotals();
}

void GenerateProformaInvoice::on_cmdGenerate_clicked()
{
	if (QMessageBox::question(this, "Confirm Save", "Are you sure you want to save this proforma?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
		return;
	}
	QString unique = QDateTime::currentDateTime().toString("yyyyMMhhmmsszzz");
	QString cnt = DataPublics::getDbValue("SELECT Number from proforma_numbers", db, "Number").toString();
	for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
		QString query = "INSERT INTO proforma (UniqueID, CustomerID, ProductID, "
				"Qty, Specs, UnitWeight, TotalWeight, Package, UnitPrice, TotalPrice, "
				"ProformaNo, ProformaWeight, ProformaPackage, ProformaQty, "
				"ProformaPrice, Currency, Packing, ProformaDate) VALUES ('"
				+ unique + "', '" +
				customerID() + "', '" +
				ui->tableWidget->item(i, 9)->text() + "', '" +
				ui->tableWidget->item(i, 3)->text() + "', '" +
				ui->tableWidget->item(i, 2)->text() + "', '0', '" +
				ui->tableWidget->item(i, 5)->text() + "', '" +
				ui->tableWidget->item(i, 6)->text() + "', '" +
				ui->tableWidget->item(i, 7)->text() + "', '" +
				ui->tableWidget->item(i, 8)->text() + "', '" +
				"MCL-" + DataPublics::getDbValue("SELECT DATE_FORMAT(NOW(), '%y') AS 'Year'", db, "Year").toString() +"-" + cnt +  "', '" +
				ui->txtTotalWeight->text() + "', '" +
				ui->txtTotalPackage->text() + "', '" +
				ui->txtTotalPcs->text() + "', '" +
				ui->txtTotalAmount->text() + "', '" +
				ui->cboCurrency->currentText() + "', '" +
				ui->tableWidget->item(i, 4)->text() + "', '" +
				DataPublics::getDbValue("SELECT NOW() as 'Now'", db, "Now").toString() + "')";

		QSqlQuery qu = db.exec(query);
		if (qu.lastError().isValid()) {
			DataPublics::showWarning("Error:\n\n" + qu.lastError().text());
			db.exec("DELETE FROM proforma WHERE UniqueID = '" + unique + "'");
			return;
		}
	}
	db.exec("UPDATE proforma_numbers SET Number = Number + 1");
	db.exec("INSERT INTO ProformaDetails (UniqueID) VALUES ('" + unique + "')");
	db.exec("INSERT INTO ProformaEntryDetails (UniqueID) VALUES ('" + unique + "')");

	if (QMessageBox::question(this, "Print", "Would you like to print this proforma now?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
		QtPrinter(this, db, unique, "Proforma", false);
	}

	this->close();
}

void GenerateProformaInvoice::on_GenerateProformaInvoice_accepted()
{

}

double GenerateProformaInvoice::round2(double number)
{
	return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}
