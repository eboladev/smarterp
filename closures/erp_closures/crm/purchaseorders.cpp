#include "purchaseorders.h"
#include "ui_purchaseorders.h"
#include "datapublics.h"
PurchaseOrders::PurchaseOrders(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::PurchaseOrders)
{
    ui->setupUi(this);
    db = database;
    ui->mainSplitter->restoreState(DataPublics::getSettingValue("LPOs/SplitterMain").toByteArray());
    ui->horiSplitter->restoreState(DataPublics::getSettingValue("LPOs/SplitterHori").toByteArray());
    ui->vertiSplitter->restoreState(DataPublics::getSettingValue("LPOs/SplitterVerti").toByteArray());
    reloadCustomers();
}

PurchaseOrders::~PurchaseOrders()
{
    DataPublics::setSettingValue("LPOs/SplitterMain", ui->mainSplitter->saveState());
    DataPublics::setSettingValue("LPOs/SplitterHori", ui->horiSplitter->saveState());
    DataPublics::setSettingValue("LPOs/SplitterVerti", ui->vertiSplitter->saveState());
    delete ui;
}

void PurchaseOrders::reloadCustomers()
{
    ui->trvCustomers->setQuery("SELECT * FROM vwcustomers ORDER BY `Company Name`", db, "Customers", true);
    ui->trvCustomers->setColumnHidden(0, true);
}

void PurchaseOrders::reloadOrders()
{
    if (ui->trvCustomers->getCurrentID().length() < 0) {
        DataPublics::showWarning("No customer selected");
        return;
    }
    ui->trvOrders->setQuery("SELECT EntryID, OrderNo as 'LPO No.', Date as 'Order Date', SubTotal as 'Sub Total', VAT, OrderTotal as 'Order Total', Comment FROM purchase_orders WHERE CustomerID ='" + ui->trvCustomers->getCurrentID() + "'", db, "LPOs", true);
    ui->trvOrders->setColumnHidden(0, true);
}

void PurchaseOrders::reloadOrderDetails()
{
    if (ui->trvOrders->getCurrentID().length() < 0) {
        DataPublics::showWarning("No order selected");
        return;
    }
    ui->trvOrderDetails->setQuery("SELECT EntryID, ProductName, Price, Qty, Subtotal, Comment, SuppliedSoFar, Balance FROM purchase_orders_details WHERE OrderID = '" + ui->trvOrders->getCurrentID() + "'", db, "Order Details", true);
    ui->trvOrderDetails->setColumnHidden(0, true);
}

void PurchaseOrders::reloadOCs()
{
    if (ui->trvOrders->getCurrentID().length() < 0) {
        DataPublics::showWarning("No order selected");
        return;
    }
    ui->trvOcs->setQuery("SELECT     entry_id    , `customer_name` AS 'Customer'    , `product_code` AS 'Product Code'    , `product_name` AS 'Product Name'    , `order_date` AS 'Order Date'    , `order_qty` AS 'Order Qty' FROM    crm.oc"
                         " WHERE lpo_id = '" + ui->trvOrders->getCurrentID() + "'", QSqlDatabase::database(), "Job Tickets In Order", true);
    ui->trvOcs->setColumnHidden(0, true);
}

void PurchaseOrders::on_trvCustomers_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    reloadOrders();
}

#include "newlpo.h"
void PurchaseOrders::on_cmdNewLPO_clicked()
{
    if (ui->trvCustomers->getCurrentID().length() < 0) {
        DataPublics::showWarning("No customer selected");
        return;
    }
    NewLPO *newL = new NewLPO(this, db, ui->trvCustomers->getCurrentID());
    if (newL->exec() == QDialog::Accepted) {
        reloadOrders();
    }
}

void PurchaseOrders::on_trvOrders_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
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

            QString dirName = QFileDialog::getExistingDirectory(this, "Select Folder", QDir::homePath());
            if (dirName.length() < 1)
                dirName = QDir::homePath();

            QString fName = dirName + "/" + fileName;

            //QString fName = QFileDialog::getSaveFileName(this, "Save File", dirName);

            if (fName.length() > 0) {
                QFile f(fName);
                if (f.exists()) {
                    if (QMessageBox::question(this, "Confirm Delete", "This file already exists. Would you like to overwite it?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
                        if (f.open(QIODevice::WriteOnly)) {
                            f.write(ba);
                            int res =  QMessageBox::question(this, "File Saved", "<b>" + fName + "</b> successfully saved.<br/>Would you like to open it now?",
                                                             QMessageBox::Yes, QMessageBox::No);
                            if (res == QMessageBox::Yes) {
                                QFile fl(fName);
                                if (fl.exists()) {
                                    QDesktopServices::openUrl(fName);
                                }
                            }
                        } else {
                            DataPublics::showWarning(fName + " could not be saved");
                            return;
                        }
                    }
                } else {
                    if (f.open(QIODevice::WriteOnly)) {
                        f.write(ba);
                        int res =  QMessageBox::question(this, "File Saved", "<b>" + fName + "</b> successfully saved.<br/>Would you like to open it now?",
                                                         QMessageBox::Yes, QMessageBox::No);
                        if (res == QMessageBox::Yes) {
                            QFile fl(fName);
                            if (fl.exists()) {
                                QDesktopServices::openUrl(fName);
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

#include "generatejobticket.h"
void PurchaseOrders::on_cmdNewJobTicket_clicked()
{
    QString order_detail_id = ui->trvOrderDetails->getCurrentID();
    if (order_detail_id.length() > 0) {
        QSqlQuery qu = db.exec("SELECT * FROM purchase_orders_details WHERE EntryID = '" + order_detail_id + "'");
        if (!qu.lastError().isValid()) {
            qu.first();
            // QString order_Id = qu.record().value("OrderID").toString();
            QString productID = qu.record().value("ProductID").toString();

            GenerateJobTicket *gen = new GenerateJobTicket(this, productID);
            gen->setLpoID(order_detail_id);
            if (gen->exec() == QDialog::Accepted) {
                reloadOrders();
                reloadOrderDetails();
            }
        } else {
            QMessageBox::critical(this, "Error", qu.lastError().text());
            return;
        }
    } else {
        QMessageBox::warning(this, "Warning", "Select a product first.");
        return;
    }
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
