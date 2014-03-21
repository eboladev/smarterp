#ifndef EMAILLOOPER_H
#define EMAILLOOPER_H

#include "mailassistant.h"
#include <QThread>


//class eMail
//{
//    Q_OBJECT
//public:
//    QString subject;
//    QStringList recepients;
//};

class Mailer : public QThread {
    Q_OBJECT
public:
    explicit Mailer(QObject *parent
                    );
    void run();
signals:
    void emailStatus(QString status);
    void emailSent();
    void emailFailed();
};

class EmailLooper
{
public:
    EmailLooper();
};

#endif // EMAILLOOPER_H
