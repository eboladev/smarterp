#include "containereditor.h"
#include "ui_containereditor.h"
#include "ims_reels.h"
ContainerEditor::ContainerEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::ContainerEditor)
{
    ui->setupUi(this);
    db = database;
    isAdding = true;
    ui->grpReels->setEnabled(false);
}

ContainerEditor::~ContainerEditor()
{
    delete ui;
}

void ContainerEditor::Edit(QString sID)
{
    isAdding = false;
    currentID = sID;
    ui->grpReels->setEnabled(true);
    loadReels();

    QSqlQuery qu = db.exec("SELECT * FROM containers WHERE ContainerID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
    } else {
        qu.first();
        QSqlRecord rec = qu.record();
        ui->txtContainerNo->setText(rec.value("ContainerNo").toString());
        ui->cboType->setEditText(rec.value("Length").toString());
        ui->txtNotes->setText(rec.value("Notes").toString());
    }
}

void ContainerEditor::on_cmdSave_clicked()
{
    QString query ="SELECT NOW()";
    if (isAdding) {
        query = "INSERT INTO ims.containers (ShipmentID, ContainerNo, Length, Notes) VALUES ('"
                + shipmentID + "', '"
                + ui->txtContainerNo->text() + "', '"
                + ui->cboType->currentText()  + "', '"
                + ui->txtNotes->toPlainText() + "')";
    } else {
        query = "UPDATE ims.containers SET "
                " ShipmentID = '" + shipmentID + "', "
                " ContainerNO = '" + ui->txtContainerNo->text()  + "', '"
                " Length = '" + ui->cboType->currentText()  + "', '"
                " Notes = '" + ui->txtNotes->toPlainText() + "' WHERE ContainerID = '" + currentID + "'";
    }

    db.exec(query);

    if (db.lastError().isValid()) {
        DataPublics::showWarning(db.lastError().text());
    } else {
        this->accept();
    }
}

void ContainerEditor::loadReels()
{
    ui->lstReels->setQuery("SELECT ReelID, SupplierReelNumber as 'Supp. Reel No.', MCLNo as 'MCL Reel No.', Size, Type, GSM, Weight FROM ims.reels WHERE ContainerID = '" + currentID + "'", db, "Reels in " + ui->txtContainerNo->text(), true);
    ui->lstReels->setColumnHidden(0, true);
    ui->lstReels->addColumnToSum("Weight");
}

void ContainerEditor::on_cmdAddReel_clicked()
{
    IMS_Reels *rl  = new IMS_Reels(this, db);
    rl->containerID = currentID;
    if (rl->exec() == QDialog::Accepted)
        loadReels();
}

void ContainerEditor::on_cmdRemoveReel_clicked()
{
    QString rID = ui->lstReels->getCurrentID();
    if (rID.length() > 0) {
        if (QMessageBox::question(this, "Confirm Delete","Are you sure you want to delete this reel?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            db.exec("DELETE FROM ims.reels WHERE ReelID = '" + rID + "'");
            if (db.lastError().isValid()) {
                DataPublics::showWarning(db.lastError().text());
            } else {
                loadReels();
            }
        }
    }
}

void ContainerEditor::on_lstReels_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString rID = ui->lstReels->getCurrentID();
    if (rID.length() > 0) {
        IMS_Reels *rl  = new IMS_Reels(this, db);
        rl->containerID = currentID;
        rl->reelID = rID;
        rl->Edit();
        if (rl->exec() == QDialog::Accepted)
            loadReels();
    }
}

void ContainerEditor::on_cmdPostToReelStock_clicked()
{
    QString containerPosted =
            DataPublics::getDbValue("SELECT ReelsPosted FROM ims.containers WHERE ContainerID = '"  + currentID + "'", db, "ReelsPosted").toString();
    if (containerPosted == "Yes") {
        DataPublics::showWarning("This container has already been posted.");
        return;
    }
    QSqlQuery qu = db.exec("SELECT * FROM ims.vw_reel_info WHERE ContainerID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }
    while (qu.next()) {
        db.exec("INSERT INTO cartons.reels (ReelNumber, SupplierReelNumber, Supplier,"
                "Size,Type,GSM,Weight,ImportFileNo,ImportShipment) VALUES ('" +
                qu.record().value("MCLNo").toString() + "', '" +
                qu.record().value("SupplierReelNumber").toString() + "', '" +
                qu.record().value("SupplierName").toString() + "', '" +
                qu.record().value("Size").toString() + "', '" +
                qu.record().value("Type").toString() + "', '" +
                qu.record().value("GSM").toString() + "', '" +
                qu.record().value("Weight").toString() + "', '" +
                qu.record().value("FileNo").toString() + "', '" +
                qu.record().value("ShipmentName").toString() + "')");
    }


    db.exec("UPDATE ims.containers SET ReelsPosted = 'Yes' WHERE ContainerID = '" + currentID + "'");
}
