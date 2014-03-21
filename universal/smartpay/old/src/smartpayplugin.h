#ifndef SMARTPAYPLUGIN_H
#define SMARTPAYPLUGIN_H

//#include "smartpay_global.h"
#include <QtGui>
#include "interfaces.h"

class MainWindow;

class SmartPayPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
public:
    QMainWindow *pluginMainWindow(QWidget *parent, QSqlDatabase database);
    QString pluginName();
    QString pluginDescription();
    QString pluginVersion();
    QString releaseDate();
    QString pluginAuthor();
    QStringList subWindows();
    QString projectName();
private:
    MainWindow *m_payroll;
};
#endif // SMARTPAYPLUGIN_H
