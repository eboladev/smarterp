#include "clientlistener.h"

/*!
 * \brief ClientListener::ClientListener
 *This is a local tcp server. All instances of the ERP running on this PC will connect to
 *this server and send actions to it. This server will in return send the actions to the
 *remote Queue Server.
 *
 *This server listens on local port 4310, and the client tries to connect to remote_address:4317
 *
 * \param parent
 */
ClientListener::ClientListener(QObject *parent) :
    QThread(parent)
{
    db =  QSqlDatabase::addDatabase("QSQLITE", ":memory");
    db.exec("CREATE table actions (message TEXT, sent TEXT)");
    running  = false;

    lastServerMessage = QDateTime::currentDateTime().addMonths(-1);
    emit statusChanged(false);

    clientServer = new QTcpServer(this);
    connect (clientServer, SIGNAL(newConnection()), this, SLOT(newErpInstance()));
    clientServer->listen(QHostAddress::Any, 4310);

    clientSocket = new QTcpSocket(this);
    connect (clientSocket, SIGNAL(readyRead()), SLOT(remoteRead()));
    clientSocket->connectToHost("192.168.0.124", 4317);

    clientTimer = new QTimer(this);
    connect (clientTimer, SIGNAL(timeout()), this, SLOT(timerOut()));
    clientTimer->start(1000);
}

void ClientListener::run()
{
    running = true;
}

void ClientListener::timerOut()
{
    if (lastServerMessage.secsTo(QDateTime::currentDateTime()) > 30) {
        emit statusChanged(false);
    }
}

void ClientListener::newErpInstance()
{
//    while (clientServer->hasPendingConnections()) {
//        clientServer->nextPendingConnection()->
//    }
}

void ClientListener::remoteRead()
{

}
