#include "imsmainwindow.h"
#include "ui_imsmainwindow.h"
#include "datapublics.h"
#include "qtprinter.h"
#include "selectfile.h"
#include "containereditor.h"
ImsMainWindow::ImsMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::ImsMainWindow)
{
	ui->setupUi(this);
	//ui->lstContainers->setVisible(false);
	ui->tblShipmentContainers->setVisible(false);
	ui->dtpShipmentDateDue->setDate(QDate::currentDate());
	connect (ui->actionNew, SIGNAL(triggered()), this,  SLOT(newFile()));
	connect (ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFileChanges()));
	ui->dtpIDFProformaInvoiceDate->setDate(QDate::currentDate());
	db = QSqlDatabase::addDatabase("QMYSQL", "imsConnection");
	db.setHostName(database.hostName());
	db.setUserName(database.userName());
	db.setPassword(database.password());
	db.setDatabaseName("ims");
	//ui->actionMarine_Declaration_PDF->setVisible(false);

	if (!db.open()) {
		ui->lblMainStatus->setText("Database connection failed. Cannot create or view files");
		ui->menuBar->setEnabled(false);
		ui->toolBar->setEnabled(false);
		ui->mainToolBar->setEnabled(false);
	}

	connectionTimer = new QTimer(this);
	connect (connectionTimer, SIGNAL(timeout()), SLOT(keepConnectionAlive()));
	connectionTimer->start(600000);

	fileOpen = false;
	shipmentOpen = false;
	enableDisable();

	containerModel = new SqlTableModel(this, db);
}

ImsMainWindow::~ImsMainWindow()
{
	delete ui;
}

void ImsMainWindow::enableDisable()
{
	//if (fileOpen) {
	ui->stackedWidget->setEnabled(fileOpen);
	ui->lstShipments->setEnabled(fileOpen);
	ui->listWidget->setEnabled(fileOpen);
	//}

	if (!fileOpen) {
		clearBoxes();
	}

	ui->pageShipments->setEnabled(shipmentOpen);

	if (!shipmentOpen) {
		DataPublics::clearInputs(ui->pageShipments);
	}
}

void ImsMainWindow::clearBoxes()
{
}

void ImsMainWindow::on_actionOpen_triggered()
{
	SelectFile *sel = new SelectFile(this, db);
	if (sel->exec() == QDialog::Accepted) {
		openFile(sel->selectedFileId);
	}
}

void ImsMainWindow::openFile(QString fileID)
{
	currentFileId = fileID;
	fileOpen = true;
	enableDisable();
	currentFileNo = DataPublics::getDbValue("SELECT * FROM files WHERE EntryID = '" + currentFileId + "'", db, "FileNo").toString();
	ui->lblMainStatus->setText("Current File No: " + currentFileNo);


	DataPublics::loadQueryToComboBox("SELECT * FROM suppliers", "SupplierName", db, ui->cboSupplier);

	loadLPODetails();
	loadPFIDetails();
	loadIDFDetails();
	loadShipments();
}

void ImsMainWindow::newFile()
{
	QString newFileName = QInputDialog::getText(this, "New File Name", "Enter the name of the new file.");
	if (newFileName.length() > 0) {
		QSqlQuery qu =  db.exec("INSERT INTO files (FileNo, DateCreated) VALUES ('" + newFileName + "', Current_Date())");
		if (!qu.lastError().isValid()) {
			QString insertID = qu.lastInsertId().toString();
			openFile(insertID);
		} else {
			QMessageBox::warning(this, "Database Error", qu.lastError().text());
		}
	}
}

void ImsMainWindow::reloadProductList()
{
	//Load Product List
	ui->lstLPODetails->setQuery("SELECT EntryID, ProductName, Description, UnitPrice, Qty, ProductHS as 'HS', ProductFOB as 'FOB', Origin as 'Country Of Origin' FROM products WHERE FileID = '" + currentFileId + "'", db, "Product list For File No: " + currentFileNo, true);
	ui->lstLPODetails->setColumnHidden(0, true);
}

void ImsMainWindow::loadLPODetails()
{
	QSqlQuery qu = db.exec("SELECT * FROM files WHERE EntryID = '" + currentFileId + "'");
	if (!qu.lastError().isValid()) {
		qu.first();
		QSqlRecord rec = qu.record();
		ui->txtLpoNo->setText(rec.value("LPONo").toString());
		QString supplierID = rec.value("SupplierID").toString();
		ui->lblLPO_FileName->setText(rec.value("LPOFileName").toString());

		if (ui->lblLPO_FileName->text().length() < 1) {
			ui->lblLPO_FileName->setText("NO LPO File Uploaded");
			ui->cmdDownloadLpo->setEnabled(false);
		} else {
			ui->cmdDownloadLpo->setEnabled(true);
		}


		QString supplierName = DataPublics::getDbValue("SELECT * FROM suppliers WHERE EntryID = '" + supplierID + "'", db, "SupplierName").toString();
		for (int i = 0; i < ui->cboSupplier->count(); i++) {
			if (ui->cboSupplier->itemText(i) ==  supplierName)
				ui->cboSupplier->setCurrentIndex(i);
		}

		reloadProductList();

		//qDebug() << "Clearing";
		DataPublics::clearInputs(ui->grp_LPO);
		//DataPublics::setInputsEnabled(ui->grpLPO_ProductLineDetails, false);

		ui->cmdLPO_DeleteProduct->setEnabled(false);
		isAddingProduct = false;
	}
}

void ImsMainWindow::loadPFIDetails()
{
	QSqlQuery qu = db.exec("SELECT * FROM files WHERE EntryID = '" + currentFileId + "'");
	if (!qu.lastError().isValid()) {
		qu.first();
		ui->txtPFI_FileNo->setText(qu.record().value("PFIFileNo").toString());
		ui->txtPFI_Notes->setPlainText(qu.record().value("PFINotes").toString());

		ui->lblPFiFileName->setText(qu.record().value("PFIFileName").toString());
		if (ui->lblPFiFileName->text().length() < 1) {
			ui->lblPFiFileName->setText("NO PFI File Uploaded");
			ui->cmdPFI_DownloadFile->setEnabled(false);
		} else {
			ui->cmdPFI_DownloadFile->setEnabled(true);
		}
	}
}

#include "ims_producteditor.h"
void ImsMainWindow::loadProductDetails(QString productID)
{
	IMS_ProductEditor *ed = new IMS_ProductEditor(this, db);
	ed->Edit(productID);
	if (ed->exec()) {
		reloadProductList();
	}
}

void ImsMainWindow::loadIDFDetails()
{
	QSqlQuery qu = db.exec("SELECT * FROM files WHERE EntryID = '" + currentFileId + "'");
	if (!qu.lastError().isValid()) {
		qu.first();
		QSqlRecord rec = qu.record();
		ui->txtIDFCountryOfSupply->setText(rec.value("CountryOfSupply").toString());
		ui->txtIDFCurrency->setText(rec.value("Currency").toString());
		ui->txtIDFExchangeRate->setText(rec.value("ExchangeRate").toString());
		ui->txtIDFFobValue->setText(rec.value("FOBValue").toString());
		ui->txtIDFFreight->setText(rec.value("Freight").toString());
		ui->txtIDFNumber->setText(rec.value("IDFNumber").toString());
		ui->txtIDFOriginCertNo->setText(rec.value("OriginCertificateNo").toString());
		ui->txtIDFOtherCharges->setText(rec.value("OtherCharges").toString());
		ui->txtIDFProformaInvNo->setText(rec.value("ProformaInvoiceNo").toString());
		ui->dtpIDFProformaInvoiceDate->setDate(rec.value("ProformaInvoiceDate").toDate());
		ui->txtInvoiceNo->setText(rec.value("InvoiceNo").toString());
		ui->lblIDfFileName->setText(rec.value("IDFFileName").toString());
		if (ui->lblIDfFileName->text().length() < 1) {
			ui->lblIDfFileName->setText("NO File Uploaded");
			ui->cmdIDF_OpenIDF->setEnabled(false);
		} else {
			ui->cmdIDF_OpenIDF->setEnabled(true);
		}
	}
}

void ImsMainWindow::loadShipments()
{
	ui->lstShipments->setQuery("SELECT ShipmentID, ShipmentName as 'Name'"
				   ", ShipmentQty as 'Qty', InvoiceAmount as 'Amount'"
				   ", Vessel, ShippingLine "
				   "FROM shipments WHERE FileID = '" + currentFileId + "'", db, "Shipments for File No: " + currentFileNo, true);
	ui->lstShipments->setColumnHidden(0, true);
}

void ImsMainWindow::keepConnectionAlive()
{
	if (db.isOpen()) {
		db.exec("SELECT NOW()");
	} else {
		db.open();
	}
}

void ImsMainWindow::loadShipmentDetails()
{
	QSqlQuery qu = db.exec("SELECT * FROM shipments WHERE ShipmentID = '" + currentShipmentId + "'");
	if (!qu.lastError().isValid()) {
		qu.first();
		QSqlRecord rec = qu.record();
		ui->txtShipmentName->setText(rec.value("ShipmentName").toString());
		currentShipmentNo = ui->txtShipmentName->text();
		ui->txtShipmentQty->setText(rec.value("ShipmentQty").toString());
		ui->txtAmount->setText(rec.value("InvoiceAmount").toString());
		ui->txtShipmentCurrency->setText(rec.value("InvoiceCurrency").toString());
		ui->txtPaymentTerms->setText(rec.value("InvoicePaymentTerms").toString());
		ui->dtpShipmentDateDue->setDate(rec.value("InvoicePaymentDateDue").toDate());
		ui->txtVessel->setText(rec.value("Vessel").toString());
		ui->txtInvoiceNo->setText(rec.value("InvoiceNo").toString());
		ui->txtShippingLine->setText(rec.value("ShippingLine").toString());
		ui->txtDesc->setText(rec.value("Description").toString());
		ui->spingNoOfContainers->setValue(rec.value("NumberOfContainers").toInt());
		ui->spinShipmentExchangeRate->setValue(rec.value("ExchangeRate").toInt());
		ui->txtBLNo->setText(rec.value("BLNo").toString());
		ui->cboShipmentStatus->setEditText(rec.value("Status").toString());
		loadContainers();
		ui->stackedWidget->setCurrentWidget(ui->pageShipments);
		ui->pageShipments->setEnabled(true);


		ui->lblInvoiceFileName->setText(rec.value("InvoiceFileName").toString());
		if (ui->lblInvoiceFileName->text().length() < 1) {
			ui->lblInvoiceFileName->setText("No File Uploaded");
			ui->cmdOpenInvoice->setEnabled(false);
		} else {
			ui->cmdOpenInvoice->setEnabled(true);
		}

		ui->lblBlFileName->setText(rec.value("BLFileName").toString());
		if (ui->lblBlFileName->text().length() < 1) {
			ui->lblBlFileName->setText("No File Uploaded");
			ui->cmdOpenBL->setEnabled(false);
		} else {
			ui->cmdOpenBL->setEnabled(true);
		}

		ui->lblPackingListFileName->setText(rec.value("PackingListFileName").toString());
		if (ui->lblPackingListFileName->text().length() < 1) {
			ui->lblPackingListFileName->setText("No File Uploaded");
			ui->cmdOpenPackingList->setEnabled(false);
		} else {
			ui->cmdOpenPackingList->setEnabled(true);
		}

		ui->txtVoyage->setText(rec.value("Voyage").toString());
		ui->txtClearingAgent->setText(rec.value("ClearingAgent").toString());
		//ui->txtQty->setText(rec.value("Qty").toString());
		ui->txtPacking->setText(rec.value("Packing").toString());
		ui->txtWeight->setText(rec.value("Weight").toString());

		ui->dtpSailing->setDate(QDate::fromString(rec.value("SailingDate").toString(), "yyyy-MM-dd"));
		ui->dtpETA->setDate(QDate::fromString(rec.value("ETA").toString(), "yyyy-MM-dd"));

	} else {
		DataPublics::showWarning("Database Error",
					 "A database error has occured.\n\n" + qu.lastError().text());
	}
}

void ImsMainWindow::loadContainers()
{
	ui->lstContainers->setQuery("SELECT ContainerID, ContainerNo, Length, Notes FROM containers WHERE ShipmentID = '" + currentShipmentId  + "'", db, "Containers in " + currentShipmentNo, true);
	ui->lstContainers->setColumnHidden(0, true);

	containerModel = new SqlTableModel(this, db);
	containerModel->setSchema("ims");
	containerModel->setTable("containers");
	containerModel->setFilter("ShipmentID = '" + currentShipmentId  + "'");
	containerModel->select();

	ui->tblShipmentContainers->setModel(containerModel);
	ui->tblShipmentContainers->setColumnHidden(0, true);
	ui->tblShipmentContainers->setColumnHidden(1, true);
	ui->tblShipmentContainers->setColumnHidden(5, true);
	ui->tblShipmentContainers->resizeRowsToContents();
}

void ImsMainWindow::on_lstLPODetails_clicked(const QModelIndex &index)
{
	//qDebug() << "Clicked";
	Q_UNUSED(index);
	//loadProductDetails(ui->lstLPODetails->getCurrentID());
}

void ImsMainWindow::on_lstLPODetails_doubleClicked(const QModelIndex &index)
{
	//qDebug() << "Double Clicked";
	Q_UNUSED(index);
	loadProductDetails(ui->lstLPODetails->getCurrentID());
}

void ImsMainWindow::on_cmdLPO_NewProduct_clicked()
{
	IMS_ProductEditor *ed = new IMS_ProductEditor(this, db);
	ed->AddNew(currentFileId);

	if (ed->exec() == QDialog::Accepted) {
		reloadProductList();
	}
}

void ImsMainWindow::on_cmdUploadFile_clicked()
{
	uploadFile("LPOFile", "LPOFileName", currentFileId);
}

void ImsMainWindow::uploadFile(QString columnName, QString fileNameCol, QString id, QString tableName, QString idCol)
{
	QString fileName = QFileDialog::getOpenFileName(this, "Select a file to upload", QDir::homePath(), "*.*");
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
				DataPublics::showWarning("Database Error\n\n" + query.lastError().text());
			} else {
				DataPublics::showInformation("File uploaded");
			}
		}
	}
}

void ImsMainWindow::downloadFile(QString columnName, QString fileNameCol, QString id, QString tableName, QString idCol)
{
	QSqlQuery query(db);
	query.exec(tr("SELECT `%1`, `%2` FROM `%3` WHERE `%4` = %5").arg(columnName, fileNameCol, tableName, idCol, id));
	if (query.lastError().isValid()) {
		DataPublics::showWarning(query.lastError().text());
		return;
	}
	query.first();
	QSqlRecord rec = query.record();
	QByteArray ba = rec.value(columnName).toByteArray();
	QString fName = rec.value(fileNameCol).toString();

	QString dir = QDir::homePath();//QFileDialog::getExistingDirectory(this, "Select the location to save the file.", QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	//if (!dir.length() > 0)
	//    return;
	QString fileName = dir + QDir::separator() + fName;
	if (fileName.length() > 0) {
		//File Selected
		QFile f(fileName);
		if (f.exists()){
			if (QMessageBox::question(this, "Replace File", "The file already exists. Replace?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
				return;
			}
		}
		if (f.open(QIODevice::WriteOnly)) {
			f.write(ba);
			DataPublics::showInformation("File saved to:<br/><b>" + fileName + "</b>");
		} else {
			DataPublics::showWarning(fileName + " could not be opened for writing.\n\n" + f.errorString());
			return;
		}
	}
}

void ImsMainWindow::on_cmdPFI_UploadFile_clicked()
{
	uploadFile("PFIFile", "PFIFileName", currentFileId);
}

void ImsMainWindow::on_lstShipments_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString shipmentID = ui->lstShipments->getCurrentID();
	if (shipmentID.length() > 0) {
		shipmentOpen = true;
		currentShipmentId = shipmentID;
		DataPublics::clearInputs(ui->pageShipments);
		ui->pageShipments->setEnabled(true);
		loadShipmentDetails();
		ui->stackedWidget->setCurrentIndex(3);
	}
}

void ImsMainWindow::saveFileChanges()
{
	QString errors = "";
	if (fileOpen) {
		//Save LPO Details
		QString supID = DataPublics::getDbValue("SELECT * FROM ims.suppliers WHERE SupplierName = '" + ui->cboSupplier->currentText() + "'", db, "EntryID").toString();
		db.exec("UPDATE ims.files SET SupplierID = '"
			+ supID + "', LPONo = '" + ui->txtLpoNo->text() + "' WHERE EntryID = '" + currentFileId + "'");
		if (db.lastError().isValid()) {
			errors.append("<b>Error when saving LPO details:</b><br/><br/>" + db.lastError().text() + "<br/><br/>");
		}
		//Save PFI Details
		db.exec("UPDATE ims.files SET PFIFileno = '"
			+ ui->txtPFI_FileNo->text() + "', "
			" PFINotes = '" + ui->txtPFI_Notes->toPlainText() + "' WHERE EntryID = '" + currentFileId + "'");
		if (db.lastError().isValid()) {
			errors.append("<b>Error when saving PFI details:</b><br/><br/>" + db.lastError().text() + "<br/><br/>");
		}
		//Save IDF Details
		db.exec("UPDATE ims.files SET CountryOfSupply = '"
			+ ui->txtIDFCountryOfSupply->text() + "', "
			" Currency = '" + ui->txtIDFCurrency->text() + "', "
			" ExchangeRate = '" + ui->txtIDFExchangeRate->text() + "', "
			" FOBValue = '" + ui->txtIDFFobValue->text() + "', "
			" Freight = '" + ui->txtIDFFreight->text() + "', "
			" IDFNumber = '" + ui->txtIDFNumber->text() + "', "
			" OriginCertificateNo = '" + ui->txtIDFOriginCertNo->text() + "', "
			" OtherCharges = '" + ui->txtIDFOtherCharges->text() + "', "
			" ProformaInvoiceNo = '" + ui->txtIDFProformaInvNo->text() + "', "
			" ProformaInvoiceDate = '" + ui->dtpIDFProformaInvoiceDate->date().toString("yyyy-MM-dd") + "' WHERE EntryID = '" + currentFileId + "'");

		if (db.lastError().isValid()) {
			errors.append("<b>Error when saving IDF details:</b><br/><br/>" + db.lastError().text() + "<br/><br/>");
		}

		//Save Shipment
		if (shipmentOpen)
			on_actionSave_Shipment_triggered();

		if (errors.length() > 0) {
			//Errors have occurred
			QMessageBox::critical(this, "Error(s) while saving file data.", errors);
		} else {
			QMessageBox::information(this, "Success", "File details saved");
		}
	}
}

void ImsMainWindow::on_cmdLPO_DeleteProduct_clicked()
{
	QString pID = ui->lstLPODetails->getCurrentID();
	if (pID.length() > 0) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this item?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM ims.products WHERE EntryID = '" + pID + "'");
			reloadProductList();
		}
	} else {
		DataPublics::showWarning("No item selected");
	}
}

void ImsMainWindow::on_cmdIDF_PrintApplication_clicked()
{
	QSqlQuery qu = db.exec("SELECT * FROM ims.report WHERE report_name = 'IDFApplication'");
	if (!qu.lastError().isValid()) {
		qu.first();
		QSqlRecord rec = qu.record();
		QString xml = rec.value("report_source").toString();
		xml.replace("param_entryID", currentFileId);
		DataPublics::showReportPreview(xml, db);
	}
}

void ImsMainWindow::on_cmdIDF_UploadIDF_clicked()
{
	uploadFile("IDFFile", "IDFFileName", currentFileId);
}

void ImsMainWindow::on_cmdIDF_OpenIDF_clicked()
{
	downloadFile("IDFFile", "IDFFileName", currentFileId);
}

void ImsMainWindow::on_cmdPFI_DownloadFile_clicked()
{
	downloadFile("PFIFile", "PFIFileName", currentFileId);
}

void ImsMainWindow::on_cmdDownloadLpo_clicked()
{
	downloadFile("LPOFile", "LPOFileName", currentFileId);
}

void ImsMainWindow::on_actionNew_Shipment_triggered()
{
	int cnt = DataPublics::getDbValue("SELECT COUNT(ShipmentID) as cnt FROM shipments WHERE FileID = '" + currentFileId + "'", db, "cnt").toInt();
	cnt = cnt+1;
	QString ship = "Sipment " + QString::number(cnt);
	QString shipmentName = QInputDialog::getText(this, "New Shipment", "Enter the shipment name:",QLineEdit::Normal, ship);
	if (shipmentName.length() > 0) {
		QSqlQuery qu = db.exec("INSERT INTO shipments (FileID, ShipmentName) VALUES ('" + currentFileId + "', '" + shipmentName + "')");
		if (qu.lastError().isValid())
		{
			DataPublics::showWarning(qu.lastError().text());
			return;
		}
		QString shipmentID = qu.lastInsertId().toString();
		shipmentOpen = true;
		currentShipmentId = shipmentID;
		currentShipmentNo = shipmentName;
		loadShipments();
		loadShipmentDetails();

	}
}

void ImsMainWindow::on_cmdUploadInvoice_clicked()
{
	uploadFile("InvoiceFile", "InvoiceFileName", currentShipmentId, "shipments", "ShipmentID");
}

void ImsMainWindow::on_cmdUploadBL_clicked()
{
	uploadFile("BLFile", "BLFileName",currentShipmentId, "shipments", "ShipmentID" );

}

void ImsMainWindow::on_cmdUploadPackingList_clicked()
{
	uploadFile("PackingListFile", "PackingListFileName", currentShipmentId, "shipments", "ShipmentID");

}

void ImsMainWindow::on_cmdOpenInvoice_clicked()
{
	downloadFile("InvoiceFile", "InvoiceFileName", currentShipmentId, "shipments", "ShipmentID");

}

void ImsMainWindow::on_cmdOpenBL_clicked()
{
	downloadFile("BLFile", "BLFileName", currentShipmentId, "shipments", "ShipmentID");

}

void ImsMainWindow::on_cmdOpenPackingList_clicked()
{
	downloadFile("PackingListFile", "PackingListFileName", currentShipmentId, "shipments", "ShipmentID");

}

void ImsMainWindow::on_toolButton_clicked()
{
	on_actionNew_Shipment_triggered();
}

void ImsMainWindow::on_toolButton_2_clicked()
{
	on_actionSave_Shipment_triggered();
}

void ImsMainWindow::on_toolButton_3_clicked()
{

}

void ImsMainWindow::on_actionSave_Shipment_triggered()
{
	QString isForced = "No";
	if (ui->chkForcePacking->isChecked())
		isForced = "Yes";


	QSqlQuery qu =  db.exec("UPDATE shipments SET "
				" ShipmentName = '" + ui->txtShipmentName->text() + "', "
				" ShipmentQty = '" + ui->txtShipmentQty->text() + "', "
				" InvoiceAmount = '" + ui->txtAmount->text()  + "', "
				" InvoiceCurrency = '" + ui->txtShipmentCurrency->text()  + "', "
				" InvoicePaymentTerms = '" + ui->txtPaymentTerms->text()  + "', "
				" InvoicePaymentDateDue = '" + ui->dtpShipmentDateDue->date().toString("yyyy-MM-dd") + "', "
				" Vessel = '" + ui->txtVessel->text()  + "', "
				" Voyage = '"  + ui->txtVoyage->text()+ "', "
				" ClearingAgent = '" + ui->txtClearingAgent->text() + "', "
				" Description = '" + ui->txtDesc->text() + "', "
				" Packing = '" + ui->txtPacking->text() + "', "
				" Qty = '" + ui->txtShipmentQty->text() + "', "
				" isForced = '" + isForced + "', "
				" forcedText = '" + ui->txtForcedPacking->text() + "', "
				" Status = '" + ui->cboShipmentStatus->currentText() + "', "
				" Weight = '" + ui->txtWeight->text() + "', "
				" InvoiceNo = '" + ui->txtInvoiceNo->text() + "', "
				" SailingDate = '" + ui->dtpSailing->date().toString("yyyy-MM-dd")+ "', "
				" ETA = '" + ui->dtpETA->date().toString("yyyy-MM-dd")+ "', "
				" ShippingLine = '" + ui->txtShippingLine->text()  + "', "
				" NumberOfContainers = '" + QString::number(ui->spingNoOfContainers->value())  + "', "
				" ExchangeRate = '" + QString::number(ui->spinShipmentExchangeRate->value())  + "', "
				" BLNo = '" + ui->txtBLNo->text() + "' WHERE ShipmentID = '" + currentShipmentId + "'");

	// if (qu.lastError().isValid()) { //rriuroa
	//     DataPublics::showWarning(qu.lastError().text());
	// }->txtWeight->text() + "', "
	//         " SailingDate = '"
}

void ImsMainWindow::on_actionPrint_Marine_Cover_triggered()
{
	if (shipmentOpen) {
		db.exec("CALL CalculateMarineCover ('" + currentShipmentId + "');");
		QSqlQuery qu = db.exec("SELECT * FROM ims.report WHERE report_name = 'MarineCover'");
		if (!qu.lastError().isValid()) {
			qu.first();
			QSqlRecord rec = qu.record();
			QString xml = rec.value("report_source").toString();
			xml.replace("param_shipmentID", currentShipmentId);
			DataPublics::showReportPreview(xml, db);
		}
	} else {
		DataPublics::showWarning("No shipment open");
	}
}

void ImsMainWindow::on_cmdAddContainer_clicked()
{
	ContainerEditor *ed = new ContainerEditor(this, db);
	ed->shipmentID = currentShipmentId;
	if (ed->exec() == QDialog::Accepted) {
		loadContainers();
	}
}

void ImsMainWindow::on_cmdRemoveContainer_clicked()
{
	QString cID = ui->lstContainers->getCurrentID();
	if (cID.length() > 0) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this container?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM ims.containers WHERE ContainerID = '" + cID + "'");
			if (db.lastError().isValid()) {
				DataPublics::showWarning(db.lastError().text());
			} else {
				loadContainers();
			}
		}
	} else {
		DataPublics::showWarning("No container selected.");
	}
}

void ImsMainWindow::on_lstContainers_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString cID = ui->lstContainers->getCurrentID();
	if (cID.length() > 0) {
		ContainerEditor *ed = new ContainerEditor(this, db);
		ed->shipmentID = currentShipmentId;
		ed->Edit(cID);
		if (ed->exec() == QDialog::Accepted)
			loadContainers();
	}
}

void ImsMainWindow::on_actionDelete_File_triggered()
{
	if (fileOpen) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this file?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM ims.files WHERE EntryID = '" + currentFileId + "'");
		}
		currentFileId = "";
		currentFileNo = "";
		currentShipmentId = "";
		currentShipmentNo = "";
		reloadProductList();
		loadShipments();
		enableDisable();
		DataPublics::clearInputs(this);
	}
}

void ImsMainWindow::on_cmdDeleteShipment_clicked()
{
	on_actionDelete_Shipment_triggered();
}

void ImsMainWindow::on_actionDelete_Shipment_triggered()
{
	if (shipmentOpen) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this shipment?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM ims.shipments WHERE ShipmentID = '" + currentShipmentId + "'");
			loadShipments();
			shipmentOpen = false;
			DataPublics::clearInputs(ui->pageShipments);
		}
	}
}

#include "ims_kracharges.h"
void ImsMainWindow::on_actionCharges_triggered()
{
	IMS_KraCharges *chg = new IMS_KraCharges(this, db);
	chg->exec();
}
void ImsMainWindow::on_actionPrint_Marine_Declaration_triggered()
{
	generateMarineDeclaration();
}

void ImsMainWindow::on_actionMarine_Declaration_PDF_triggered()
{
	generateMarineDeclaration(true);
}

void ImsMainWindow::generateMarineDeclaration(bool pdf)
{
	if (shipmentOpen) {
		QSqlQuery qu = db.exec("CALL CalculateMarineDeclaration ('" + currentShipmentId + "');");
		if (!qu.lastError().isValid()) {
			QString param_where = " WHERE ShipmentID = '" + currentShipmentId + "'";
			QtPrinter *qp = new QtPrinter(this, db, param_where, "MarineDeclaration", pdf);
			Q_UNUSED(qp);
		} else {
			DataPublics::showWarning("Database Error:\n\n"  + qu.lastError().text());
		}
	} else {
		DataPublics::showWarning("No shipment open");
	}
}

void ImsMainWindow::on_txtShipmentQty_textChanged(const QString &arg1)
{
	updatePacking();
}

void ImsMainWindow::updatePacking()
{
	ui->txtPacking->setText(ui->txtShipmentQty->text() + " ROLLS IN " + QString::number(ui->spingNoOfContainers->value()) + "X40 FT CONTAINER(S)");
}

void ImsMainWindow::on_spingNoOfContainers_valueChanged(const QString &arg1)
{
	Q_UNUSED(arg1);
	updatePacking();
}
