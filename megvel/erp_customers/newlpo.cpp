#include "newlpo.h"
#include "ui_newlpo.h"
#include "datapublics.h"

NewLPO::NewLPO(QWidget *parent, QSqlDatabase database, QString cID) :
	QDialog(parent),
	ui(new Ui::NewLPO)
{
	ui->setupUi(this);
	db = database;
	isNew = true;
	ui->dtpDeliveryDate->setDate(QDate::currentDate().addDays(14));
	ui->dtpOrderDate->setDate(QDate::currentDate());

	customerID = cID;

	QStringList productIDs;

	QSqlQuery qu = db.exec("SELECT * FROM products WHERE  Customer = '" + cID + "'");

	while (qu.next()) {
		productIDs << qu.record().value(0).toString();
	}

	prodIDs = productIDs;
	qDebug() << prodIDs;

	setCustomer();
	setProducts();

	isNew = false;
}

NewLPO::~NewLPO()
{
	delete ui;
}

void NewLPO::setCustomer()
{
	ui->txtCustomer->setText(DataPublics::getDbValue("SELECT * FROM customers WHERE CustomerID = '" + customerID + "'", db, "CompanyName").toString());
}

void NewLPO::setProducts()
{
	for (int i = 0; i < prodIDs.count(); i++) {
		QString currentID = prodIDs.at(i);
		QString productName, price;
		productName = DataPublics::getDbValue("SELECT * FROM products WHERE `Product Id` = '" + currentID + "'", db, "Product").toString();
		price = DataPublics::getDbValue("SELECT * FROM products WHERE `Product Id` = '" + currentID + "'", db, "Price").toString();

		QTableWidgetItem *productNameItem = new QTableWidgetItem(1);
		QTableWidgetItem *priceItem = new QTableWidgetItem(1);
		QTableWidgetItem *qtyItem = new QTableWidgetItem(1);
		QTableWidgetItem *vatItem = new QTableWidgetItem(1);
		QTableWidgetItem *subtotalItem = new QTableWidgetItem(1);
		QTableWidgetItem *commentItem = new QTableWidgetItem(1);
		QTableWidgetItem *idItem = new QTableWidgetItem(1);

		productNameItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		priceItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		vatItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		subtotalItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		idItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);



		productNameItem->setText(productName);
		priceItem->setText(price);
		qtyItem->setText("0.00");
		vatItem->setText("0.00");
		subtotalItem->setText("0.00");
		commentItem->setText("");
		idItem->setText(currentID);

		int r  =ui->tblOrderDetails->rowCount();
		ui->tblOrderDetails->insertRow(r);

		ui->tblOrderDetails->setItem(r, 0, productNameItem);
		ui->tblOrderDetails->setItem(r, 1, priceItem);
		ui->tblOrderDetails->setItem(r, 2, qtyItem);
		ui->tblOrderDetails->setItem(r, 3, vatItem);
		ui->tblOrderDetails->setItem(r, 4, subtotalItem);
		ui->tblOrderDetails->setItem(r, 5, commentItem);
		ui->tblOrderDetails->setItem(r, 6, idItem);

		subtotalItem->setTextAlignment(Qt::AlignRight);
	}
	ui->tblOrderDetails->setColumnHidden(6, true);
	ui->tblOrderDetails->setColumnHidden(3, true);
	ui->tblOrderDetails->resizeColumnsToContents();
	ui->tblOrderDetails->resizeRowsToContents();

	calculateTotals();
}

void NewLPO::uploadFile(QString columnName, QString fileNameCol, QString id, QString tableName, QString idCol)
{
	QString fileName = ui->txtFileName->text(); //QFileDialog::getOpenFileName(this, "Select a file to upload", QDir::homePath(), "*.*");
	if (fileName.length() > 0) {
		QFile file(fileName);
		if (file.exists()) {
			QByteArray ba;
			QStringList fileNameData = fileName.split("/");
			if (file.open(QFile::ReadOnly)) {
				ba = file.readAll();
				file.close();
			} else {
				DataPublics::showWarning("Could not upload file. File might be open elsewhere.\n\n" + file.errorString());
				return;
			}
			QSqlQuery query(db);
			query.prepare("UPDATE `" + tableName +"` SET " + columnName + " = :fileData, " + fileNameCol + " = :fileName WHERE `" + idCol +"` = '" + id  + "'");
			query.bindValue(":fileData", ba);
			query.bindValue(":fileName", fileNameData.last());

			query.exec();

			if (query.lastError().isValid()) {
				DataPublics::showWarning("File Upload Error\n\n" + query.lastError().text());
			} else {
				// DataPublics::showInformation("File uploaded");
			}
		}
	}
}


void NewLPO::on_toolButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Select the LPO file", QDir::homePath(), "*.*");
	if (fileName.length() > 0) {
		ui->txtFileName->setText(fileName);
	}
}


void NewLPO::recalculateRow(int r)
{
	QTableWidgetItem *priceIt = ui->tblOrderDetails->item(r, 1);
	QTableWidgetItem *qtyIt = ui->tblOrderDetails->item(r, 2);
	QTableWidgetItem *subtotalIt = ui->tblOrderDetails->item(r, 4);
	QTableWidgetItem *vatIt = ui->tblOrderDetails->item(r, 3);
	subtotalIt->setText(QLocale(QLocale::English).toString(priceIt->text().toDouble() * qtyIt->text().toDouble(), 'f', 0));
	vatIt->setText(QString::number(priceIt->text().toDouble() * qtyIt->text().toDouble()));
	ui->tblOrderDetails->setItem(r, 4, subtotalIt);

	calculateTotals();
}

void NewLPO::calculateTotals()
{
	QString total = "0.00";
	for (int i = 0; i < ui->tblOrderDetails->rowCount(); i++) {
		QString currentSubtotal = ui->tblOrderDetails->item(i, 3)->text();
		total = QString::number(total.toDouble() + currentSubtotal.toDouble());
	}
	QString vat = QString::number(total.toDouble() * 0.16);
	QString net = QString::number(vat.toDouble() + total.toDouble());

	ui->txtOrderTotal->setText(QLocale(QLocale::English).toString(total.toFloat(), 'f', 0));
	ui->txtVAT->setText(QLocale(QLocale::English).toString(vat.toFloat(), 'f', 0));
	ui->txtAmountDue->setText(QLocale(QLocale::English).toString(net.toFloat(), 'f', 0));
}


void NewLPO::on_tblOrderDetails_cellChanged(int row, int column)
{
	if (!isNew) {
		recalculateRow(row);
		Q_UNUSED(column);
	}
}

void NewLPO::on_cmdPostOrder_clicked()
{
	QLocale loc(QLocale::English, QLocale::Kenya);
	QString lpoQuery = "INSERT INTO purchase_orders (CustomerID, Date, OrderNo, SubTotal, VAT, OrderTotal, Comment)"
			" VALUES ('" + customerID + "', '"
			+ ui->dtpOrderDate->date().toString("yyyy-MM-dd") + "', '"
			+ ui->txtOrderNumber->text() + "', '"
			+ ui->txtOrderTotal->text()  + "', '"
			+ ui->txtVAT->text() + "', '"
			+ ui->txtAmountDue->text()  + "', '"
			+ "" + "')";

	QSqlQuery lpoQu = db.exec(lpoQuery);
	if (!lpoQu.lastError().isValid()) {
		QString lpoID = lpoQu.lastInsertId().toString();
		uploadFile("File", "FileName", lpoID, "purchase_orders", "EntryID");
		for (int i = 0; i < ui->tblOrderDetails->rowCount(); i++) {
			QString currentSubtotal = ui->tblOrderDetails->item(i, 3)->text();
			double subTotal = currentSubtotal.toDouble();

			QString qty = ui->tblOrderDetails->item(i, 2)->text();
			double d_qty = qty.toDouble();

			if (d_qty > 0) {
				QString prodName = ui->tblOrderDetails->item(i, 0)->text();
				QString price = ui->tblOrderDetails->item(i, 1)->text();

				QString id = ui->tblOrderDetails->item(i, 6)->text();
				QString comment = ui->tblOrderDetails->item(i, 5)->text();
				QString lineItemQuery  = "INSERT INTO purchase_orders_details ("
						"OrderID, ProductID, ProductName, Price, Qty, SubTotal,"
						"Comment) VALUES ('"
						+ lpoID  + "', '"
						+ id   + "', '"
						+ prodName   + "', '"
						+ price   + "', '"
						+ qty   + "', '"
						+ currentSubtotal   + "', '"
						+ comment + "')";
				db.exec(lineItemQuery);
			}
		}
		DataPublics::showInformation("Order Saved");
		this->accept();
	} else {
		DataPublics::showWarning(lpoQu.lastError().text());
	}
}
