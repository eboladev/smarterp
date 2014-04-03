#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);

    QString odbcDataSource() const;
    void setOdbcDataSource(const QString &odbcDataSource);

    QString mysqlHostName() const;
    void setMysqlHostName(const QString &mysqlHostName);

    QString mysqlUserName() const;
    void setMysqlUserName(const QString &mysqlUserName);

    QString mysqlPassword() const;
    void setMysqlPassword(const QString &mysqlPassword);

    QString mysqlDatabaseName() const;
    void setMysqlDatabaseName(const QString &mysqlDatabaseName);

    void saveData();
signals:

private:
    QString m_odbcDataSource;
    QString m_mysqlHostName;
    QString m_mysqlUserName;
    QString m_mysqlPassword;
    QString m_mysqlDatabaseName;

public slots:

};

#endif // SETTINGSMANAGER_H
