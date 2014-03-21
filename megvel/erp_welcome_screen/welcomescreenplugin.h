#ifndef WELCOMESCREENPLUGIN_H
#define WELCOMESCREENPLUGIN_H

#include <QtSql>

#include <QObject>
#include <QMainWindow>
#include "interfaces.h"

class WelcomeScreenPlugin : public QObject,
        public MainWindowInterface
{
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
public:
    QMainWindow *pluginMainWindow(QWidget *parent);
signals:
    
public slots:
    
private:
};

#endif // WELCOMESCREENPLUGIN_H
