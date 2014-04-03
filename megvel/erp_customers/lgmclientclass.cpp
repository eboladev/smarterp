#include "lgmclientclass.h"

LGMClientClass::LGMClientClass(QObject *parent) :
    QObject(parent)
{

}

void LGMClientClass::startLgmClient(QString hostName, int port)
{
    emit status("Starting lgm client...");
    lgmClient = new QTcpSocket(this);
    connect (lgmClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
             this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    lgmClient->connectToHost(QHostAddress(hostName), port);
}

void LGMClientClass::sendMessageToServer(QString message)
{
    if (message.right(1) != "=")
        message+="=";

    if (lgmClient->state() == QTcpSocket::ConnectedState)
    {
        lgmClient->write(message.toLatin1());
    }
}

void LGMClientClass::stateChanged(QAbstractSocket::SocketState state)
{
    currentState = state;
    if (state != QAbstractSocket::ConnectedState) {
        emit status("Connecting to server.");
    }
    if (state == QAbstractSocket::ConnectedState) {
        emit status("Connected to " + lgmClient->peerAddress().toString() + ":" + QString::number(lgmClient->peerPort()));
    }
}
