#include "ims_reels.h"
#include "ui_ims_reels.h"

IMS_Reels::IMS_Reels(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::IMS_Reels)
{
    ui->setupUi(this);
    db = database;
    isAdding = true;
}

IMS_Reels::~IMS_Reels()
{
    delete ui;
}

void IMS_Reels::Edit()
{
    isAdding = false;
    QSqlQuery qu = db.exec("SELECT * FROM ims.reels WHERE ReelID = '" + reelID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        this->reject();
    }

    qu.first();
    QSqlRecord rec = qu.record();
    containerID = rec.value("ContainerID").toString();
    ui->txtSupplierReelNo->setText(rec.value("SupplierReelNumber").toString());
    ui->txtSize->setText(rec.value("Size").toString());
    ui->txtType->setText(rec.value("Type").toString());
    ui->txtGSM->setText(rec.value("GSM").toString());
    ui->txtWieght->setText(rec.value("Weight").toString());
    ui->txtMCLReelNo->setText(rec.value("MCLNo").toString());
}

void IMS_Reels::on_cmdSave_clicked()
{
    QString query = "SELECT NOW()";
    if (isAdding) {
        query = "INSERT INTO ims.reels (ContainerID, SupplierReelNumber, "
                "Size, Type, GSM, MCLNo, Weight) VALUES ('"
                + containerID + "', '"
                + ui->txtSupplierReelNo->text()  + "', '"
                + ui->txtSize->text() + "', '"
                + ui->txtType->text() + "', '"
                + ui->txtGSM->text() + "', '"
                + ui->txtMCLReelNo->text() + "', '"
                + ui->txtWieght->text() + "')";
    } else {
        query = "UPDATE ims.reels SET "
                "SupplierReelNumber = '" + ui->txtSupplierReelNo->text() + "', "
                "Size = '" + ui->txtSize->text() + "', "
                "Type = '" + ui->txtType->text() + "', "
                "GSM = '" + ui->txtGSM->text() + "', "
                "MCLNo = '" + ui->txtMCLReelNo->text() + "', "
                "Weight = '" + ui->txtWieght->text() + "' WHERE ReelID = '" + reelID + "'";
    }
    db.exec(query);
    if (db.lastError().isValid()) {
        DataPublics::showWarning(db.lastError().text());
    }else {
        this->accept();
    }
}
