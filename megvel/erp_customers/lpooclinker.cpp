#include "lpooclinker.h"
#include "ui_lpooclinker.h"
#include "datapublics.h"
LPOOcLinker::LPOOcLinker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LPOOcLinker)
{
    ui->setupUi(this);
    db = QSqlDatabase::database();
}

LPOOcLinker::~LPOOcLinker()
{
    delete ui;
}
QString LPOOcLinker::orderID() const
{
    return m_orderID;
}

void LPOOcLinker::setOrderID(const QString &orderID)
{
    m_orderID = orderID;
    QSqlQuery qu = db.exec("SELECT * FROM purchase_orders WHERE EntryID = '" + m_orderID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning("There was an error while fetching the order details.\n\n" + qu.lastError().text());
        this->reject();
        return;
    }

    qu.first();
    QString customerID = qu.record().value("CustomerID").toString();
    setOrderNo(qu.record().value("OrderNo").toString());
    setCustomerName(DataPublics::getDbValue("SELECT * FROM customers WHERE CustomerID = '" + customerID + "'", db, "CompanyName").toString());


    reloadOCs();
}
QString LPOOcLinker::customerName() const
{
    return m_customerName;
}

void LPOOcLinker::setCustomerName(const QString &customerName)
{
    m_customerName = customerName;
    ui->txtCustomerName->setText(m_customerName);
}
QString LPOOcLinker::orderNo() const
{
    return m_orderNo;
}

void LPOOcLinker::setOrderNo(const QString &orderNo)
{
    m_orderNo = orderNo;
    ui->txtLPONo->setText(m_orderNo);
}

void LPOOcLinker::reloadOCs()
{
    model  = new QSqlQueryModel(this);
    model->setQuery("SELECT TicketNo as 'Order No', Date as 'Order Date',"
                    "Qty as 'Order Qty', lpo_comment as 'Comment' FROM newreport WHERE lpo_id = '"
                    + m_orderID + "' ", db);
    ui->tblOcs->setModel(model);
}




void LPOOcLinker::on_cmdDownloadLPO_clicked()
{
    QString lpoNo = m_orderID;
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

void LPOOcLinker::on_cmdAddOc_clicked()
{
    QString ocNo = QInputDialog::getText(this, "Add OC", "Enter the OC Number");
    if (ocNo.length() > 0) {
        db.exec("UPDATE newreport SET lpo_id = '" + m_orderID + "' WHERE TicketNo = '" + ocNo + "'");
        reloadOCs();
    }
}

void LPOOcLinker::on_cmdRemoveSelected_clicked()
{
    QString ocNo =
            model->data(model->index(ui->tblOcs->currentIndex().row(),
                                     0
                                     )).toString();
    if (ocNo.length() > 0) {
        db.exec("UPDATE newreport SET lpo_id = '' WHERE TicketNo = '" + ocNo + "'");
        reloadOCs();
    }
}

void LPOOcLinker::on_cmdSave_clicked()
{
    this->accept();
}
