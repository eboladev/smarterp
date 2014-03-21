#include "queueclientdialog.h"
#include "ui_queueclientdialog.h"

QueueClientDialog::QueueClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueueClientDialog)
{
    ui->setupUi(this);
    readSettings();
}

QueueClientDialog::~QueueClientDialog()
{
    saveSettings();
    delete ui;
}

void QueueClientDialog::readSettings()
{
    QSettings sett(qApp->organizationName(), qApp->applicationDisplayName());
    ui->txtServerIP->setText(sett.value("ServerIP", "192.168.0.124").toString());
    ui->txtERPLocation->setText(sett.value("ERPLocation", "C:\Program Files\Megvel Cartons Ltd").toString());
    ui->spinServerPort->setValue(sett.value("ServerPort", 4317).toInt());
}

void QueueClientDialog::saveSettings()
{
    QSettings sett(qApp->organizationName(), qApp->applicationDisplayName());
    sett.setValue("ServerIP", ui->txtServerIP->text());
    sett.setValue("ERPLocation", ui->txtERPLocation->text());
    sett.setValue("ServerPort", ui->spinServerPort->value());
}
