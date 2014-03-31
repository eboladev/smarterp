#include "updateservice.h"

#include <QDir>
#include <QFile>
#include "server.h"
#include <QtWidgets/QApplication>
UpdateService::UpdateService(QObject *parent) :
    QObject(parent)
{

}

UpdateService::~UpdateService()
{
}

void UpdateService::startUpdateCheck()
{
    if (db.isOpen()) {
        emit serviceStatus("Starting update process. Querying database server for possible update servers.");
        QSqlQuery qu = db.exec("SELECT * FROM servers");
        QMap<int, Server *> servers;
        while (qu.next()) {
            Server *srv = new Server(this);
            srv->setPlatform(qu.record().value("Platform").toString());
            srv->setServerAddress(qu.record().value("Address").toString());
            srv->setServerName(qu.record().value("ServerName").toString());
            srv->setPort(qu.record().value("Port").toInt());
            servers.insert(servers.count(), srv);
        }

        emit serviceStatus(tr("Found %1 servers.").arg(servers.count()));

        for (int i = 0; i< servers.count(); i++) {
            emit serviceStatus("\n\n\nServer Name: " + servers[i]->ServerName() + "\nPlatform: " + servers[i]->Platform() + "\nAddress: " + servers[i]->Address() + "\n");
            QString osType = "Win32";
#ifdef Q_OS_WIN32
            osType = "Win32";
#endif
#ifdef Q_OS_LINUX
            osType = "Linux";
#endif

        }
        for (int i = 0; i< servers.count(); i++) {
            QString osType = "Win32";
#ifdef Q_OS_WIN32
            osType = "Win32";
#endif
#ifdef Q_OS_LINUX
            osType = "Linux";
#endif
            if (servers[i]->Platform() == osType) {
                emit serviceStatus("Using " + servers[i]->ServerName());

            }
        }
        emit finished();
    } else {
        emit serviceStatus("ERROR: List of update servers unavailable. Update cannot proceed.");
    }
}

void UpdateService::connectToDb()
{
    QString hostName = "192.168.0.8";
    QString userName = "root";
    QString password = "password";


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

                                if (lineLabel == "hostName") {
                                    if (lineLabel.contains(";")) {
                                        hostName = lineValue.split(";").at(0);
                                    } else {
                                        hostName = lineValue;
                                    }
                                }

                                if (lineLabel == "userName")
                                    userName = lineValue;

                                if (lineLabel == "password")
                                    password = lineValue;
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
        //        QString fileData = "hostName=" + hostName + lineBreaks
        //                + "userName=" + userName + lineBreaks
        //                + "password=" + password + lineBreaks;
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

    db = QSqlDatabase::addDatabase("QMYSQL", "updater");
    db.setDatabaseName("erp-update");
    db.setUserName(userName);
    if (password.length() > 0)
        db.setPassword(password);
    db.setHostName(hostName);

    if (db.open()) {
        emit serviceStatus("Database OK.");
        startUpdateCheck();
    } else {
        emit serviceStatus("ERROR: Could not connect to the database server at " + hostName + ".");
        emit finished();
    }
}

