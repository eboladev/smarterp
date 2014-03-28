#ifndef LGMQUEUE_H
#define LGMQUEUE_H

#include <QObject>
#include "lgmclientclass.h"
#include <QTimer>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
class LGMQueue : public QObject
{
    Q_OBJECT
public:
    explicit LGMQueue(QObject *parent = 0);
    QList<QString> unprocessedCommands;
    void addCommand(QString command);
    void printOC(QString oc);
private:
    LGMClientClass *lgm;
    QTimer *fiveSecondTimer;

private slots:
    void timeOut();
signals:
    
public slots:
    
};

#endif // LGMQUEUE_H
