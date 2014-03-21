#include "helperdialog.h"
#include "ui_helperdialog.h"
#include "settingsmanager.h"

#include <QFile>
#include <QDir>

HelperDialog::HelperDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelperDialog)
{
    ui->setupUi(this);
    loadSettings();
}

HelperDialog::~HelperDialog()
{
    delete ui;
}

void HelperDialog::loadSettings()
{
    ui->lstMySQLServers->clear();
    //ui->lstMySQLServers->insertItem(0, SettingsManager::getSettingValue("hostName"));

    QString hostNames = SettingsManager::getSettingValue("hostName", "192.168.0.8;192.168.0.251;192.168.0.241;192.168.0.231");

    if (hostNames.contains(";")) {
        QStringList lst_names = hostNames.split(";");
        for (int i = 0; i < lst_names.count(); i++) {
            if (lst_names.at(i).length() > 0)
                ui->lstMySQLServers->insertItem(i, lst_names.at(i));
        }
    } else {
        ui->lstMySQLServers->insertItem(0, hostNames);
    }

    ui->txtMySQLuserName->setText(SettingsManager::getSettingValue("userName"));
    ui->txtMySQLPassword->setText(SettingsManager::getSettingValue("password"));
    ui->txtTlmServerAddress->setText(SettingsManager::getSettingValue("tlmServerIP"));
    ui->spinMySQlPort->setValue(SettingsManager::getSettingValue("mysqlPort").toInt());
    ui->spinTlmServerPort->setValue(SettingsManager::getSettingValue("tlmServerPort").toInt());
    ui->spinSMTPServerPort->setValue(SettingsManager::getSettingValue("smtpPort").toInt());
    ui->txtSMTPServerName->setText(SettingsManager::getSettingValue("smtpHostName"));
    ui->txtSMTPUSerName->setText(SettingsManager::getSettingValue("smptUserName"));
    ui->txtSMTPPassword->setText(SettingsManager::getSettingValue("smtpPassword"));
}

void HelperDialog::on_cmdSave_clicked()
{
    QString lineBreaks = "\n";
#ifdef Q_OS_WIN
    lineBreaks = "\r\n";
#endif
    QFile fil(qApp->applicationDirPath() + QDir::separator() + "settings.cfg");

    QString hostNames = "";
    for (int i = 0; i < ui->lstMySQLServers->count(); ++i) {
        hostNames.append(ui->lstMySQLServers->item(i)->text() + ";");
    }

    QString fileData = "hostName=" + hostNames + lineBreaks
            + "userName=" + ui->txtMySQLuserName->text() + lineBreaks
            + "password=" + ui->txtMySQLPassword->text() + lineBreaks
            + "mysqlPort=3306" + lineBreaks
            + "tlmServerIP=192.168.0.188" + lineBreaks
            + "tlmServerPort=4317" + lineBreaks
            + "smtpHostName=192.168.0.245" + lineBreaks
            + "smtpPort=110" + lineBreaks
            + "smtpUserName=admin@mcl.co.ke" + lineBreaks
            + "smptPassword=meg123!!" + lineBreaks
            + "smtpSSL=yes" + lineBreaks;
    if (fil.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        fil.write(fileData.toUtf8());
        fil.close();
    }
}

#include <QInputDialog>
void HelperDialog::on_cmdAddMySqlServer_clicked()
{
    QString newHost = QInputDialog::getText(this, "New MySQL Host", "Enter the host name");
    if (newHost.length() > 0) {
        ui->lstMySQLServers->addItem(newHost);
    }
}
