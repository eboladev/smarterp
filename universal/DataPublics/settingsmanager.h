#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QVariant>

class SettingsManager
{
public:
	SettingsManager();
	static void setSettingValue(QString settingName, QVariant value);
	static QVariant getSettingValue(QString settingName, QVariant defaultValue = QVariant());
signals:

public slots:

};

#endif // SETTINGSMANAGER_H
