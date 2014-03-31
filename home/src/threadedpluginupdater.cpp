#include "threadedpluginupdater.h"
#include "datapublics.h"
ThreadedPluginUpdater::ThreadedPluginUpdater(QObject *parent) :
    QThread(parent)
{
}


void ThreadedPluginUpdater::run()
{
    qRegisterMetaType<QAbstractSocket::SocketState>("SocketState" );
    tlmSocket = new QTcpSocket();
    tlmSocket->moveToThread(this);
    connect (tlmSocket, SIGNAL(connected()), SLOT(socketConnected()));
    connect (tlmSocket, SIGNAL(readyRead()), SLOT(socketReadyRead()));
    connect (tlmSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), SLOT(serverStateChanged(QAbstractSocket::SocketState)));

    QString tlmServerIp = "127.0.0.1";
    int tlmServerPort = 8000;
    QString fileName = QApplication::applicationDirPath() + QDir::separator() + "settings.ini";
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

                                if (lineLabel == "tlmServerIP")
                                    tlmServerIp = lineValue;

                                if (lineLabel == "tlmServerPort")
                                    tlmServerPort = lineValue.toInt();
                            }
                        }
                    }
                }
            }
            fil.close();
        }
    }
    //emit currentAction(iPluginID, "Starting sleep for " + QString::number(iPluginID) + " seconds.");
    sleep(0.1 * iPluginID);
    //emit currentAction(iPluginID, "Sleep ended");
    tlmSocket->connectToHost(QHostAddress(tlmServerIp), tlmServerPort, QIODevice::ReadWrite);
    exec();
}

void ThreadedPluginUpdater::serverStateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << state;
    if (state == QAbstractSocket::ConnectedState) {
        emit currentAction(iPluginID, "Connected to TLM server. Waiting for response");
    } else if (state == QAbstractSocket::HostLookupState) {
        emit currentAction(iPluginID, "Looking up TLM server. Please wait.");
    } else if (state == QAbstractSocket::ConnectingState) {
        emit currentAction(iPluginID, "TLM Server found...Trying connection.");
    }
}

void ThreadedPluginUpdater::socketConnected()
{
    emit currentAction(iPluginID, "Connected to TLM server. Sending plugin information");
}

void ThreadedPluginUpdater::socketReadyRead()
{
    QString sockData = tlmSocket->readAll();
    // qDebug() << sockData;
    if (sockData.contains("STX") && sockData.contains("ETX")) {
        //Data is complete
        QStringList splitData = sockData.split("|");
        if (splitData.count() > 3) {
            QString commandName = splitData.at(2);
            QString commandText = splitData.at(3);
            if (commandName == "Plugin Version") {
                emit currentAction(iPluginID, "Latest version is " + commandText + " you need an update for this plugin") ;
            }else if (commandName == "HANDSHAKE") {
                if (commandText == "OK") {
                    emit currentAction(iPluginID, "Plugin details sent.");
                    tlmSocket->write(QString("|STX|Plugin Version|" + strPluginName + "|" + strPluginVersion + "|" + strPluginReleaseDate + "|ETX|").toUtf8());
                }
            }else if (commandName == "Version") {
                emit currentAction(iPluginID, commandText);
            }
        }
    }
}

void ThreadedPluginUpdater::setVars(QString pluginName, int PluginID, QString pluginVersion, QString releaseDate) {
    strPluginName = pluginName;
    strPluginReleaseDate = releaseDate;
    strPluginVersion = pluginVersion;
    iPluginID = PluginID;
}
