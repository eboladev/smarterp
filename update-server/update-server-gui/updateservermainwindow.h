#ifndef UPDATESERVERMAINWINDOW_H
#define UPDATESERVERMAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QThread>

namespace Ui {
class UpdateServerMainWindow;
}

class Client : public QThread {
    Q_OBJECT
public:
    explicit Client(QObject *parent);
    QTcpSocket *clientSocket() { return m_socket; }
    void setSocket(QTcpSocket *socket) { m_socket = socket; }
    QString m_hostName;
    QString m_ipAddress;
    QString m_osVersion;
    QDateTime m_firstContact;
    QDateTime m_lastContact;
private:
    QTcpSocket *m_socket;
};


class PluginSender : public QThread {
    Q_OBJECT
public:
    explicit PluginSender(QObject *parent);
    ~PluginSender();
    void run();
};

class UpdateServerMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit UpdateServerMainWindow(QWidget *parent = 0);
    ~UpdateServerMainWindow();
private slots:
    void hideShow();
    void notifyClientsOfUpdate();
    void reloadPlugins();
    void exit();
    void writeLog(QString log, bool error = false);
    void secondTimerTick();

    void newConnection();
    void readyRead();
    void clientDisconnected();

    void reloadClientList();
private:
    Ui::UpdateServerMainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QTimer *secondTimer;
    QAction *showHideMenu;
    QColor m_redColor;
    QColor m_greenColor;
    QColor m_blueColor;
    QTcpServer *m_server;
    QMap<int, Client*> m_clientList;
    Client *getClientFromSocket(QTcpSocket *sock);
};

#endif // UPDATESERVERMAINWINDOW_H
