#include "pingtest.h"
#include <iostream>
PingTest::PingTest(QObject *parent, QString IpAddress) :
    QThread(parent)
{
    address = IpAddress;
    process = new QProcess(this);
    connect (process, SIGNAL(readyReadStandardError())
             , this, SLOT(processError()));
    connect (process, SIGNAL(readyReadStandardOutput())
             , this, SLOT(processMessage()));
    if(process)
        process->start("ping.exe", QStringList() << address << "-n" << "2", QIODevice::ReadWrite);

    emit message("Pinging " + address);
}

void PingTest::run()
{

}

void PingTest::processError()
{
    if(process)
    {
        QByteArray s = process->readAllStandardError();
        QString str(s);
        qDebug() << str;
        emit message(str);
        emit failed();
    }
}

void PingTest::processMessage()
{
    if(process)
    {
        QByteArray s = process->readAllStandardOutput();
        QString str(s);
        qDebug() << str;
        if (s.contains("unreachable")) {
            emit message("Ping Failed...");
            emit failed();
        }else if (s.contains("bytes") || s.contains("(0% loss)")) {
            emit message("Server responding...");
            emit succeeded();
        } else {
            emit message ("Ping in progress...");
            emit failed();
        }
    }
}
