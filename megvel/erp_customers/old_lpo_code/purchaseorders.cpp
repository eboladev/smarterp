#include "purchaseorders.h"
#include "ui_purchaseorders.h"
#include "datapublics.h"
PurchaseOrders::PurchaseOrders(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::PurchaseOrders)
{
    ui->setupUi(this);
    db = database;
    ui->splitter->restoreState(DataPublics::getSettingValue("LPOs/OrdersSplitter").toByteArray());
    ui->splitter_2->restoreState(DataPublics::getSettingValue("LPOs/MainSplitter").toByteArray());
    reloadCustomers();
}

PurchaseOrders::~PurchaseOrders()
{
    DataPublics::setSettingValue("LPOs/OrdersSplitter", ui->splitter->saveState());
    DataPublics::setSettingValue("LPOs/MainSplitter", ui->splitter_2->saveState());
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
    ui->trvOrders->setQuery("SELECT EntryID, Date as 'Order Date', SubTotal as 'Sub Total', VAT, OrderTotal as 'Order Total', Comment FROM purchase_orders WHERE CustomerID ='" + ui->trvCustomers->getCurrentID() + "'", db, "LPOs", true);
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
}

void PurchaseOrders::on_cmdDownloadLPO_clicked()
{
    QString lpoNo = ui->trvOrders->getCurrentID();
    if (lpoNo.length() > 0) {
        QString fileName = DataPublics::getDbValue("SELECT * FROM purchase_orders WHERE EntryID = '" + lpoNo + "'", db, "FileName").toString();
        if (fileName.length() > 0) {
            QSqlQuery query(db);
            query.exec("SELECT File FROM purchase_orders WHERE EntryID = '" + lpoNo + "'");
            if (query.lastError().isValid()) {
                DataPublics::showWarning(query.lastError().text());
                return;
            }

            query.first();
            QSqlRecord rec = query.record();
            QByteArray ba = rec.value("File").toByteArray();

            QString dirName = QDir::homePath();
            QString fName = dirName + QDir::separator() + fileName;

            if (fName.length() > 0) {
                QFile f(fName);
                if (f.exists()) {
                    if (QMessageBox::question(this, "Confirm Delete", "This file already exists. Would you like to overwite it?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
                        if (f.open(QIODevice::WriteOnly)) {
                            f.write(ba);
                            DataPublics::showInformation("File saved to:<br/><br/><b>" + fName + "<b><br/>");
                        } else {
                            DataPublics::showWarning(fName + " could not be saved");
                            return;
                        }
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
