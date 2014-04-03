#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void setServerName(QString s) { s_serverName = s; }
    void setServerAddress(QString s) { s_address = s; }
    void setPort(int p) { s_port = p; }
    void setPlatform(QString s) { s_platform = s; }

    QString ServerName() { return s_serverName; }
    QString Address() { return s_address; }
    int Port() { return s_port; }
    QString Platform() { return s_platform; }

private:
    QString s_serverName;
    QString s_address;
    int s_port;
    QString s_platform;
signals:
    
public slots:
    
};

#endif // SERVER_H
