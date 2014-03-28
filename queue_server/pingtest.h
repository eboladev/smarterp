#ifndef PINGTEST_H
#define PINGTEST_H

#include <QThread>
#include <QtNetwork>
#include <QProcess>
class PingTest : public QThread
{
    Q_OBJECT
public:
    explicit PingTest(QObject *parent = 0, QString IpAddress = QString());
    void run();
    QString address;
signals:
    void succeeded();
    void failed();
    void message(QString);
public slots:
    void processError();
    void processMessage();
private:
    QProcess *process;
};

#endif // PINGTEST_H
