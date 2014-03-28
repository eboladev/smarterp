#ifndef UPDATESERVICE_H
#define UPDATESERVICE_H
#include <QtSql>



class UpdateService : public QObject
{
    Q_OBJECT
public:
    explicit UpdateService(QObject *parent = 0);
    ~UpdateService();
private:
    QSqlDatabase db;
public slots:
    void startUpdateCheck();
    void connectToDb();

signals:
    void serviceStatus(QString);
    void finished();
};

#endif // UPDATESERVICE_H
