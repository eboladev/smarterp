#include "proformalist.h"
#include "ui_proformalist.h"

ProformaList::ProformaList(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::ProformaList)
{
    ui->setupUi(this);
    db = database;
    reloadProformas();
    ui->dtpConfirmationDate->setDate(QDate::currentDate());
}

ProformaList::~ProformaList()
{
    delete ui;
}

void ProformaList::setDatabase(QSqlDatabase database)
{
    db = database;
}

void ProformaList::reloadProformas()
{
    ui->trvProformas->setQuery("SELECT * FROM vw_proforma2", db, "Proforma Invoices", true);
    ui->trvProformas->filterModel->sort(2, Qt::DescendingOrder);
    ui->trvProformas->setColumnHidden(0, true);
}

#include "qtprinter.h"

void ProformaList::on_trvProformas_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    on_cmdPrintProforma_clicked();
}

void ProformaList::on_cmdPDF_clicked()
{
    QString id= ui->trvProformas->getCurrentID();
    if (id.length() > 0) {
        QtPrinter(this, db, id, "Proforma", true);
    }
}

void ProformaList::on_cmdPrintProforma_clicked()
{
    QString id= ui->trvProformas->getCurrentID();
    if (id.length() > 0) {
        QtPrinter(this, db, id, "Proforma", false);
    }
}

void ProformaList::on_cmdConfirmed_clicked()
{
    QString id= ui->trvProformas->getCurrentID();
    if (id.length() < 1) {
        DataPublics::showWarning("Select a proforma.");
        return;
    }
    if (DataPublics::getDbValue("SELECT * FROM ProformaEntryDetails WHERE UniqueID = '" + id + "'", db, "EmailSent").toString() == "No") {
        DataPublics::showWarning("This email has not been sent yet.");
    }

    db.exec("UPDATE ProformaEntryDetails SET EmailConfirmed = 'Yes', ConfirmationDate = '" + ui->dtpConfirmationDate->date().toString("yyyy-MM-dd") + "' WHERE UniqueID = '" + id + "'");
    reloadProformas();
}

void ProformaList::on_cmdOpenUnPassedEntry_clicked()
{
    downloadFile("Unpassed Entry");
}

void ProformaList::uploadFile(QString fileType)
{
    QString id= ui->trvProformas->getCurrentID();
    if (id.length() < 1) {
        DataPublics::showWarning("Select a proforma.");
        return;
    }
    QSqlQuery qu = db.exec("SELECT * FROM proforma_files WHERE ProformaID = '" + id + "' AND FileType = '" + fileType + "'");

    if (qu.size() > 0) {
        if (QMessageBox::question(this, "Confirm Overwrite", "This " + fileType + " has already been uploaded.\n\nWould you like to overwrite it?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
            return;
    }
    QString fileName = QFileDialog::getOpenFileName(this, "Select a file to upload", QDir::homePath(), "*.*");
    if (fileName.length() > 0) {
        QFile file(fileName);
        if (file.exists()) {
            db.exec("DELETE FROM proforma_files WHERE ProformaID = '" + id + "' AND FileType = '" + fileType + "'");
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
            query.prepare("INSERT INTO proforma_files (ProformaID, FileName, FileData, FileType) VALUES ("
                          ":id, :fileName, :fileData, :fileType)");

            query.bindValue(":id", id);
            query.bindValue(":fileType", fileType);
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

void ProformaList::downloadFile(QString fileType)
{
    QString id= ui->trvProformas->getCurrentID();
    if (id.length() < 1) {
        DataPublics::showWarning("Select a proforma.");
        return;
    }
    QSqlQuery qu = db.exec("SELECT * FROM proforma_files WHERE ProformaID = '" + id + "' AND FileType = '" + fileType + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }
    if (qu.size() < 1) {
        DataPublics::showWarning("File not uploaded.");
        return;
    }

    qu.first();
    QSqlRecord rec = qu.record();
    QByteArray ba = rec.value("FileData").toByteArray();
    QString fName = rec.value("FileName").toString();
    QString dir = QFileDialog::getExistingDirectory(this, "Select the location to save the file.", QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir.length() < 1)
        dir = QDir::homePath();


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

void ProformaList::on_cmdUploadUnPassedEntry_clicked()
{
    uploadFile("Unpassed Entry");
}

void ProformaList::on_cmdUploadPassedEntry_clicked()
{
    QString id= ui->trvProformas->getCurrentID();
    if (id.length() < 1) {
        DataPublics::showWarning("Select a proforma.");
        return;
    }
    QString entryNo  = QInputDialog::getText(this, "Entry No.", "Enter Entry Number:");
    db.exec("UPDATE ProformaEntryDetails SET EntryNo = '" + entryNo + "' WHERE UniqueID = '" + id + "'");
    uploadFile("Passed Entry");
    reloadProformas();
}

void ProformaList::on_cmdOpenPassedEntry_clicked()
{
    downloadFile("Passed Entry");
}

void ProformaList::on_cmdUploadSignedCompletedEntry_clicked()
{
    uploadFile("Signed Completed Entry");
}

void ProformaList::on_cmdOpenSignedCompletedEntry_clicked()
{
    downloadFile("Signed Completed Entry");
}

void ProformaList::on_cmdUploadDeliveryNote_clicked()
{
    uploadFile("Delivery Note");
}

void ProformaList::on_cmdOpenDeliveryNote_clicked()
{
    downloadFile("Delivery Note");
}
