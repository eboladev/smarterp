#ifndef TLMMAINWINDOW_H
#define TLMMAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class TLMMainWindow;
}

class ClientInformation {
public:
    QTcpSocket *clientID;
    QString c_serverIP;
    int c_serverPort;
    QString c_pluginName;
    QString c_pluginVersion;
    QString c_pluginReleaseDate;

    QString p_version;
    QString p_releaseDate;

    QString c_hostName;
};

class TLMMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TLMMainWindow(QWidget *parent = 0);
    ~TLMMainWindow();
    
private slots:
    void on_actionExit_triggered();

    void on_actionPreferences_triggered();
    void loadServerPlugins();
    void writeLog(QString logAction);

    void newTcpConnection();

    void readyRead();

    void updateClientList();
    void clientDisconnected();
    void getHostNameFromIP(QString ipAddress, QTcpSocket *client);
    //void getIPFromHostName(QString hostName);

    void lookedUp(const QHostInfo &host, QTcpSocket *client);
private:
    Ui::TLMMainWindow *ui;
    QTcpServer *server;
    QList <QTcpSocket *> clients;
    QMap <QTcpSocket *, ClientInformation *> clientInfos;
};

#endif // TLMMAINWINDOW_H
