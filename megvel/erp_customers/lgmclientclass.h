#ifndef LGMCLIENTCLASS_H
#define LGMCLIENTCLASS_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class LGMClientClass : public QObject
{
    Q_OBJECT
public:
    explicit LGMClientClass(QObject *parent = 0);
    void startLgmClient(QString hostName = "127.0.0.1", int port = 6988);
    QAbstractSocket::SocketState currentState;
public slots:
    void sendMessageToServer(QString message);
private slots:
    void stateChanged(QAbstractSocket::SocketState state);
private:
    QTcpSocket *lgmClient;
signals:
    
signals:
    void serverResponse(QString res);
    void status(QString status);
};

#endif // LGMCLIENTCLASS_H
