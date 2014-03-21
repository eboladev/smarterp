#include "welcomescreenplugin.h"
#include "erpwelcomescreen.h"
#include <QtPlugin>

QMainWindow *WelcomeScreenPlugin::pluginMainWindow(QWidget *parent) {
    QMainWindow *mw =  qobject_cast<QMainWindow *>(new ERPWelcomeScreen(parent));
    return mw;
}

Q_EXPORT_PLUGIN2(erp_welcome_screen, WelcomeScreenPlugin)
