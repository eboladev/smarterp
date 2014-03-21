#ifndef SMARTPAYEMBEDDEDDATABASEMANAGER_H
#define SMARTPAYEMBEDDEDDATABASEMANAGER_H

#include <QObject>
#include <QtSql>
class SmartPayEmbeddedDatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit SmartPayEmbeddedDatabaseManager(QObject *parent = 0, QSqlDatabase database = QSqlDatabase());
    bool checkMaster();
    bool checkDemoDb();
    bool initMaster();
    bool initDemoDb();
    bool runSqlScript(QString scriptName, QString dbName);
private:
    QSqlDatabase db;
signals:
    
public slots:
    void threadsFinished();
};

#endif // SMARTPAYEMBEDDEDDATABASEMANAGER_H
