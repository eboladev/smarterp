#include "newwasteentry.h"
#include "ui_newwasteentry.h"
#include <QtSql>
#include <QMessageBox>

NewWasteEntry::NewWasteEntry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewWasteEntry)
{
    ui->setupUi(this);
    ui->dtpDate->setDate(QDate::currentDate());
}

NewWasteEntry::~NewWasteEntry()
{
    delete ui;
}

void NewWasteEntry::on_cmdSave_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    QString query = "INSERT INTO `cartons`.`paras_waste`(`EntryDate`, "
            "`Tonnage`,`CorrugatorWetEnd`,`CorrugatorDryEnd`,`PrintingReject`,"
            "`CorrugatorTrimWaste`,`PrintingTrimWaste`,`PrintingSetUp`,"
            "`GluingReject`,`StitchingReject`,`PeelingReject`) VALUES ( '"
            + ui->dtpDate->date().toString("yyyy-MM-dd") + "', '"
            + QString::number(ui->spinTonnage->value()) + "', '"
            + QString::number(ui->spinCorrugatorWetEnd->value()) + "', '"
            + QString::number(ui->spinCorrugatorDryEnd->value()) + "', '"
            + QString::number(ui->spinPrintingrejectBoards->value()) + "', '"
            + QString::number(ui->spinCorrugatorTrinWaste->value()) + "', '"
            + QString::number(ui->spinPrintingTrimWaste->value()) + "', '"
            + QString::number(ui->spinPrintingSetUp->value()) + "', '"
            + QString::number(ui->spinGluingRejectBoards->value()) + "', '"
            + QString::number(ui->spinStichingRejectBoards->value()) + "', '"
            + QString::number(ui->spinPeelingRejectBoards->value()) + "')";

    QSqlQuery qu = db.exec(query);
    if (qu.lastError().isValid()) {
        QMessageBox::critical(this, "Error", qu.lastError().text());
    } else {
        this->accept();
    }

}
