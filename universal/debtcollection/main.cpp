#include <QApplication>
#include "dcmainwindow.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QtSql>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QString hostName = "192.168.0.34";
    QString userName = "root";
    QString password = "pledge";
    QString dbName = "debt-collection";


    QFile file(qApp->applicationDirPath() + QDir::separator() + "dcsettings.ini");
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            QString fileData = file.readAll();
            QStringList settings = fileData.split(";");
            for (int i = 0; i < settings.count(); i++) {
                QString thisSetting = settings.at(i).trimmed();
                if (thisSetting.contains("=")) {
                    QStringList settingData = thisSetting.split("=");
                    QString setting = settingData.at(0);
                    QString value = settingData.at(1);

                    if (setting == "h")
                        hostName = value;

                    if (setting == "u")
                        userName = value;

                    if (setting == "p")
                        password = value;

                    if (setting == "d")
                        dbName = value;

                    qDebug() << userName << "@" << hostName << "/" << dbName;
                }
            }
        }
    } else {
        QString fileData = "h=192.168.0.34;u=root;p=pledge;d=debt-collection";
        if (file.open(QIODevice::WriteOnly)) {
            file.write(fileData.toUtf8());
            file.close();
        }
    }

    db.setHostName(hostName);
    db.setUserName(userName);
    db.setPassword(password);
    db.setDatabaseName(dbName);
    if (db.open()) {
        DCMainWindow w;
        w.showMaximized();
        return a.exec();
    } else {
        QMessageBox::critical(0, "Database Error", "<h3>Could not connect to database.</h3> <br/>" + db.lastError().text());
        return 0;
    }
}
