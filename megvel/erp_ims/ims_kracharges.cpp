#include "ims_kracharges.h"
#include "ui_ims_kracharges.h"

IMS_KraCharges::IMS_KraCharges(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::IMS_KraCharges)
{
    ui->setupUi(this);
    db = database;
    QSqlQuery qu = db.exec("SELECT * FROM ims.charges");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        this->reject();
    } else {
        qu.first();
        QSqlRecord rec = qu.record();
        ui->txtKPA->setText(rec.value("KPACharge").toString());
        ui->txtShipping->setText(rec.value("ShippingCharge").toString());
        ui->txtContainer->setText(rec.value("ContainerCharge").toString());
        ui->txtMisc->setText(rec.value("MiscCharge").toString());

        currentID = rec.value("SettingsID").toString();
    }

}

IMS_KraCharges::~IMS_KraCharges()
{
    delete ui;
}

void IMS_KraCharges::on_cmdSave_clicked()
{
    QString query = "UPDATE ims.charges SET KPACharge = '" + ui->txtKPA->text() +
            "', ShippingCharhe = '" + ui->txtShipping->text() +
            ", TransportCharge = '" + ui->txtTransport->text() +
            ", MiscCharge = '" + ui->txtMisc->text() + "' WHERE SettingsID = '" + currentID + "'";

    db.exec(query);
    if (db.lastError().isValid()) {
        DataPublics::showWarning(db.lastError().text());
    } else
    {
        DataPublics::showInformation("Settings Saved");
    }
}
