#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);
    static QString getSettingValue(QString settingName = "", QString defaultValue = "");
signals:
    
public slots:
    
};

#endif // SETTINGSMANAGER_H
