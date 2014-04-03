#include "settingsmanager.h"
#include <QApplication>
SettingsManager::SettingsManager(QObject *parent) :
	QObject(parent)
{
	QSettings sett(qApp->organizationName(), qApp->applicationName());

	setOdbcDataSource(sett.value("odbcDataSource", "endeavour_ta").toString());
	setMysqlDatabaseName(sett.value("mysqlDbName", "smartpay-master").toString());
	setMysqlHostName(sett.value("mysqlHostName", "197.254.15.122").toString());
	setMysqlPassword(sett.value("mysqlPassword", "pledge").toString());
	setMysqlUserName(sett.value("mysqlUserName", "root").toString());

	saveData();
}
QString SettingsManager::odbcDataSource() const
{
	return m_odbcDataSource;
}

void SettingsManager::setOdbcDataSource(const QString &odbcDataSource)
{
	m_odbcDataSource = odbcDataSource;
}
QString SettingsManager::mysqlHostName() const
{
	return m_mysqlHostName;
}

void SettingsManager::setMysqlHostName(const QString &mysqlHostName)
{
	m_mysqlHostName = mysqlHostName;
}
QString SettingsManager::mysqlUserName() const
{
	return m_mysqlUserName;
}

void SettingsManager::setMysqlUserName(const QString &mysqlUserName)
{
	m_mysqlUserName = mysqlUserName;
}
QString SettingsManager::mysqlPassword() const
{
	return m_mysqlPassword;
}

void SettingsManager::setMysqlPassword(const QString &mysqlPassword)
{
	m_mysqlPassword = mysqlPassword;
}
QString SettingsManager::mysqlDatabaseName() const
{
	return m_mysqlDatabaseName;
}

void SettingsManager::setMysqlDatabaseName(const QString &mysqlDatabaseName)
{
	m_mysqlDatabaseName = mysqlDatabaseName;
}

void SettingsManager::saveData()
{
	QSettings sett(qApp->organizationName(), qApp->applicationName());

	setOdbcDataSource(sett.value("odbcDataSource", "endeavour_ta").toString());
	setMysqlDatabaseName(sett.value("mysqlDbName", "smartpay-master").toString());
	setMysqlHostName(sett.value("mysqlHostName", "197.254.15.122").toString());
	setMysqlPassword(sett.value("mysqlPassword", "pledge").toString());
	setMysqlUserName(sett.value("mysqlUserName", "root").toString());

	sett.setValue("odbcDataSource", odbcDataSource());
	sett.setValue("mysqlDbName", mysqlDatabaseName());
	sett.setValue("mysqlHostName", mysqlHostName());
	sett.setValue("mysqlPassword", mysqlPassword());
	sett.setValue("mysqlUserName", mysqlUserName());
}





