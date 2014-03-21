#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>

class UpdateThread : public QThread
{
    Q_OBJECT
public:
    explicit UpdateThread(QObject *parent = 0);
    void run();
signals:
    
public slots:
    
};

#endif // UPDATETHREAD_H
