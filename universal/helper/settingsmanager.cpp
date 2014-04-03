#include "datapublics.h"
#include "settingsmanager.h"
#include <QApplication>
#include <QFile>
#include <QDir>
SettingsManager::SettingsManager(QObject *parent) :
    QObject(parent)
{
}

QString SettingsManager::getSettingValue(QString settingName, QString defaultValue)
{
    QString fileName = QApplication::applicationDirPath() + QDir::separator() + "settings.cfg";
    QFile fil(fileName);
    QString lineBreaks = "\n";
#ifdef Q_OS_WIN
    lineBreaks = "\r\n";
#endif
    if (fil.exists()) {
        if (fil.open(QIODevice::Text | QIODevice::ReadOnly)) {
            //File successfully open
            QString fileData = fil.readAll();
#ifdef Q_OS_WIN
            if (fileData.contains("\r\n")) { //using windows line breaks

            } else {
                fileData.replace("\n", "\r\n");
            }
#endif
            QStringList fileLines = fileData.split(lineBreaks);
            if (fileLines.count() > 0) {
                for (int i = 0; i < fileLines.count(); i++) {

                    QString thisLine = fileLines.at(i);

                    if (!thisLine.startsWith("#")) {
                        if (thisLine.contains("=")) {
                            if (thisLine.split("=").count() > 0) {
                                QString lineLabel = thisLine.split("=").at(0);
                                QString lineValue = thisLine.split("=").at(1);

                                if (lineLabel == settingName)
                                    return lineValue;

                            }
                        }
                    }
                }
            }
            fil.close();
        } else {
            //File open error.
        }
    } else {
        //File not found. Create It
        QString fileData = "hostName=192.168.0.8" + lineBreaks
                + "userName=root" + lineBreaks
                + "password=pledge" + lineBreaks
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
    return defaultValue;
}
