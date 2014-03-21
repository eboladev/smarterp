#ifndef THREADEDPLUGINUPDATER_H
#define THREADEDPLUGINUPDATER_H

#include <QThread>
#include <QFile>
#include <QtNetwork>
#include <QAbstractSocket>
Q_DECLARE_METATYPE(QAbstractSocket::SocketState)
class ThreadedPluginUpdater : public QThread
{
    Q_OBJECT
private:
    QString strPluginName;
    int iPluginID;
    QTcpSocket *tlmSocket;

    QString strPluginVersion;
    QString strPluginReleaseDate;
public:
    explicit ThreadedPluginUpdater(QObject *parent = 0);
    void setVars(QString pluginName, int PluginID, QString pluginVersion, QString releaseDate);
signals:
    void currentAction(int pluginID, QString actionName);
public slots:
    void run();
    void serverStateChanged(QAbstractSocket::SocketState state);
    void socketConnected();
    void socketReadyRead();
};

#endif // THREADEDPLUGINUPDATER_H
