#ifndef CLIENTLISTENER_H
#define CLIENTLISTENER_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtSql>
#include <QTimer>



class ClientListener : public QThread
{
    Q_OBJECT
public:
    explicit ClientListener(QObject *parent = 0);
    void run();
signals:
    void statusChanged(bool online);
public slots:
    void timerOut();
private slots:
    void newErpInstance();
    void remoteRead();
private:
    QSqlDatabase db;
    QTimer *clientTimer;
    bool running;
    QTcpServer *clientServer;
    QTcpSocket *clientSocket;
    QDateTime lastServerMessage;
};

#endif // CLIENTLISTENER_H
