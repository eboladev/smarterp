#include "purchaseorders.h"
#include "ui_purchaseorders.h"
#include "datapublics.h"
PurchaseOrders::PurchaseOrders(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::PurchaseOrders)
{
	ui->setupUi(this);
	db = database;
	ui->splitter->restoreState(DataPublics::getSettingValue("LPOs/SplitterMain").toByteArray());
	ui->horiSplitter->restoreState(DataPublics::getSettingValue("LPOs/SplitterHori").toByteArray());
	ui->vertiSplitter->restoreState(DataPublics::getSettingValue("LPOs/SplitterVerti").toByteArray());
	ui->splitter_2->restoreState(DataPublics::getSettingValue("LPOs/Splitter2").toByteArray());
	reloadCustomers();
	reloadAllOrders();
}

PurchaseOrders::~PurchaseOrders()
{
	DataPublics::setSettingValue("LPOs/SplitterMain", ui->splitter->saveState());
	DataPublics::setSettingValue("LPOs/SplitterHori", ui->horiSplitter->saveState());
	DataPublics::setSettingValue("LPOs/SplitterVerti", ui->vertiSplitter->saveState());
	DataPublics::setSettingValue("LPOs/Splitter2", ui->splitter_2->saveState());
	delete ui;
}

void PurchaseOrders::setDatabase(QSqlDatabase database)
{
	db = database;
}

void PurchaseOrders::reloadCustomers()
{
	ui->trvCustomers->setQuery("SELECT * FROM vwcustomers ORDER BY `Company Name`", db, "Customers", true);
	ui->trvCustomers->filterModel->sort(2);
	ui->trvCustomers->setColumnHidden(0, true);
}

void PurchaseOrders::reloadAllOrders()
{
	QLocale loc(QLocale::English, QLocale::Kenya);
	ui->lstLPOs->invisibleRootItem()->takeChildren();
	QSqlQuery qu = db.exec("SELECT * FROM purchase_orders ORDER BY EntryID DESC");
	while (qu.next()) {
		QString customerName = DataPublics::getDbValue("SELECT CompanyName FROM customers WHERE CustomerID = '" + qu.record().value("CustomerID").toString() + "'", db, "CompanyName").toString();
		QTreeWidgetItem *parentItem = new QTreeWidgetItem(ui->lstLPOs->invisibleRootItem());
		parentItem->setText(0, customerName);
		parentItem->setText(1, qu.record().value("OrderNo").toString());
		parentItem->setText(2, qu.record().value("Date").toString());
		parentItem->setText(8, qu.record().value("OrderTotal").toString());

		QString custID = qu.record().value("CustomerID").toString();
		QString orderID = qu.record().value("EntryID").toString();

		parentItem->setText(100, custID);
		parentItem->setText(101, orderID);



		parentItem->setExpanded(false);
	}
}

void PurchaseOrders::reloadOrders()
{
	if (customerID.length() < 0) {
		DataPublics::showWarning("No customer selected");
		return;
	}
	ui->trvOrders->setQuery("SELECT EntryID, OrderNo as 'LPO No.', Date as 'Order Date', SubTotal as 'Sub Total', VAT, OrderTotal as 'Order Total', Comment FROM purchase_orders WHERE CustomerID ='" + customerID + "'", db, "LPOs", true);
	ui->trvOrders->setColumnHidden(0, true);
}

void PurchaseOrders::reloadOrderDetails()
{
	if (orderID.length() < 0) {
		DataPublics::showWarning("No order selected");
		return;
	}
	ui->trvOrderDetails->setQuery("SELECT EntryID, ProductName, Price, Qty, Subtotal, Comment, SuppliedSoFar, Balance FROM purchase_orders_details WHERE OrderID = '" + orderID + "'", db, "Order Details", true);
	ui->trvOrderDetails->setColumnHidden(0, true);
}

void PurchaseOrders::reloadOCs()
{
	if (ui->trvOrders->getCurrentID().length() < 0) {
		DataPublics::showWarning("No order selected");
		return;
	}
	ui->trvOcs->setQuery("SELECT     EntryID    , `Client` AS 'Customer'    , `Code` AS 'Product Code'    , `Product` AS 'Product Name'    , `Date` AS 'Order Date'    , `Qty` AS 'Order Qty' FROM    newreport"
			     " WHERE lpo_id = '" + orderID + "'", QSqlDatabase::database(), "Job Tickets In Order", true);
	ui->trvOcs->setColumnHidden(0, true);
}

void PurchaseOrders::on_trvCustomers_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	customerID = ui->trvCustomers->getCurrentID();
	reloadOrders();
}

#include "newlpo.h"
void PurchaseOrders::on_cmdNewLPO_clicked()
{
	if (customerID < 0) {
		DataPublics::showWarning("No customer selected");
		return;
	}
	NewLPO *newL = new NewLPO(this, db, customerID);
	if (newL->exec() == QDialog::Accepted) {
		reloadOrders();
		reloadAllOrders();
	}
}

void PurchaseOrders::on_trvOrders_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	orderID = ui->trvOrders->getCurrentID();
	reloadOrderDetails();
	reloadOCs();
}



void PurchaseOrders::on_cmdDownloadLPO_clicked()
{
	QString lpoNo = ui->trvOrders->getCurrentID();
	if (lpoNo.length() > 0) {
		QString fileName = DataPublics::getDbValue("SELECT * FROM purchase_orders WHERE EntryID = '" + lpoNo + "'", db, "FileName").toString();
		//DataPublics::showInformation(fileName);
		if (fileName.length() > 0) {
			QSqlQuery query(db);
			query.exec("SELECT FileName, File FROM purchase_orders WHERE EntryID = '" + lpoNo + "'");
			if (query.lastError().isValid()) {
				DataPublics::showWarning(query.lastError().text());
				return;
			}

			query.first();
			QSqlRecord rec = query.record();
			QByteArray ba = rec.value("File").toByteArray();

			QString dirName = QDir::tempPath(); //QFileDialog::getExistingDirectory(this, "Select Folder", QDir::homePath());
			if (dirName.length() < 1)
				dirName = QDir::homePath();

			QString fName = dirName + "/" + fileName;

			//QString fName = QFileDialog::getSaveFileName(this, "Save File", dirName);

			if (fName.length() > 0) {
				QFile f(fName);
				if (f.exists()) {
					//if (QMessageBox::question(this, "Confirm Delete", "This file already exists. Would you like to overwite it?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
					// bool ovr = true;
					// if (ovr) {
					f.remove();
					if (f.open(QIODevice::WriteOnly)) {
						f.write(ba);
						int res = QMessageBox::Yes; /* QMessageBox::question(this, "File Saved", "<b>" + fName + "</b> successfully saved.<br/>Would you like to open it now?",
							     QMessageBox::Yes, QMessageBox::No);*/
						if (res == QMessageBox::Yes) {
							QFile fl(fName);
							if (fl.exists()) {
								QDesktopServices::openUrl("file:///" + fName);
							}
						}
					} else {
						DataPublics::showWarning(fName + " could not be saved");
						return;
					}
					// }
				} else {
					if (f.open(QIODevice::WriteOnly)) {
						f.write(ba);
						int res = QMessageBox::Yes;  /*QMessageBox::question(this, "File Saved", "<b>" + fName + "</b> successfully saved.<br/>Would you like to open it now?",
						     QMessageBox::Yes, QMessageBox::No);*/
						if (res == QMessageBox::Yes) {
							QFile fl(fName);
							if (fl.exists()) {
								QDesktopServices::openUrl("file:///" +  fName);
							}
						}
					} else {
						DataPublics::showWarning(fName + " could not be saved");
						return;
					}
				}
			}
		} else {
			DataPublics::showWarning("No file has been uploaded for this order.");
		}
	} else {
		DataPublics::showWarning("Please select an order to download.");
	}
}

void PurchaseOrders::on_cmdEmailLPO_clicked()
{

}

//#include "generatejobticket.h"
void PurchaseOrders::on_cmdNewJobTicket_clicked()
{
	//    QString order_detail_id = ui->trvOrderDetails->getCurrentID();
	//    if (order_detail_id.length() > 0) {
	//        QSqlQuery qu = db.exec("SELECT * FROM purchase_orders_details WHERE EntryID = '" + order_detail_id + "'");
	//        if (!qu.lastError().isValid()) {
	//            qu.first();
	//            // QString order_Id = qu.record().value("OrderID").toString();
	//            QString productID = qu.record().value("ProductID").toString();

	//            GenerateJobTicket *gen = new GenerateJobTicket(this, productID);
	//            gen->setLpoID(order_detail_id);
	//            if (gen->exec() == QDialog::Accepted) {
	//                reloadOrders();
	//                reloadOrderDetails();
	//            }
	//        } else {
	//            QMessageBox::critical(this, "Error", qu.lastError().text());
	//            return;
	//        }
	//    } else {
	//        QMessageBox::warning(this, "Warning", "Select a product first.");
	//        return;
	//    }
}

#include "lpooclinker.h"
void PurchaseOrders::on_cmdAssignOCs_clicked()
{
	if (ui->trvOrders->getCurrentID().length() < 0) {
		DataPublics::showWarning("No order selected");
		return;
	}
	LPOOcLinker *lnk = new LPOOcLinker(this);
	lnk->setOrderID(ui->trvOrders->getCurrentID());
	if (lnk->exec() == QDialog::Accepted) {
		reloadOrderDetails();
		reloadOCs();
	}
}

void PurchaseOrders::on_cmdUploadLPOFile_clicked()
{
	if (ui->trvOrders->getCurrentID().length() < 0) {
		DataPublics::showWarning("No order selected");
		return;
	}
	QString fileName = QFileDialog::getOpenFileName(this, "Select a file to upload", QDir::homePath(), "*.pdf");
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
			query.prepare("UPDATE `purchase_orders` SET `File` = :fileData, `FileName` = :fileName WHERE `EntryID` = '" + ui->trvOrders->getCurrentID()  + "'");
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

void PurchaseOrders::on_cmdDelete_clicked()
{
	if (ui->trvOrders->getCurrentID().length() < 0) {
		DataPublics::showWarning("No order selected");
		return;
	}

	if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this LPO?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
		return;
	}

	db.exec("DELETE FROM purchase_orders WHERE EntryID = '" + ui->trvOrders->getCurrentID() + "'");
	reloadOrders();
	reloadOrderDetails();
	reloadOCs();
	reloadAllOrders();
}

void PurchaseOrders::on_lstLPOs_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QTreeWidgetItem *it = ui->lstLPOs->selectedItems().at(0);
	customerID = it->text(100);
	orderID = it->text(101);

	//qDebug() << customerID << orderID;

	reloadOrders();
	reloadOrderDetails();
	reloadOCs();
}
