#ifndef FINISHINGPLUGIN_H
#define FINISHINGPLUGIN_H

#include <QtGui>
#include "interfaces.h"

#include "finishingmainwindow.h"

class FinishingPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.finishing")
#endif
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
    FinishingMainWindow *mFinishing;
};

#endif // FINISHINGPLUGIN_H
