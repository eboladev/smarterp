#include "settingsmanager.h"
#include <QSettings>
SettingsManager::SettingsManager()
{
}

void SettingsManager::setSettingValue(QString settingName, QVariant value)
{
	QSettings sett("Megvel Cartons Ltd", "SmartERP");
	sett.setValue(settingName, value);
}

QVariant SettingsManager::getSettingValue(QString settingName, QVariant defaultValue)
{
	QSettings sett("Megvel Cartons Ltd", "SmartERP");
	return sett.value(settingName, defaultValue);
}
