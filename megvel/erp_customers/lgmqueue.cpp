#include "lgmqueue.h"

LGMQueue::LGMQueue(QObject *parent) :
    QObject(parent)
{
    lgm = new LGMClientClass(this);
    timeOut();
    fiveSecondTimer = new QTimer(this);
    connect (fiveSecondTimer, SIGNAL(timeout(QPrivateSignal)), SLOT(timeOut()));
    fiveSecondTimer->start(2000);
}

void LGMQueue::addCommand(QString command)
{
    if (lgm->currentState == QAbstractSocket::ConnectedState) {
        lgm->sendMessageToServer(command);
    } else {
        unprocessedCommands.append(command);
    }
}

void LGMQueue::printOC(QString oc)
{
    if (lgm->currentState == QAbstractSocket::ConnectedState) {
        lgm->sendMessageToServer("PrintOC=" + oc + "=");
    } else {
        addCommand("PrintOC=" + oc + "=");
    }
}

void LGMQueue::timeOut()
{
    if (lgm->currentState != QAbstractSocket::ConnectedState) {
        lgm->startLgmClient();
    } else {
        for (int i = 0; i < unprocessedCommands.count(); i++) {
            lgm->sendMessageToServer(unprocessedCommands.at(i));
            unprocessedCommands.removeAt(i);
        }
    }
}

