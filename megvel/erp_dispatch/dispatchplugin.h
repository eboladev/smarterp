#ifndef DISPATCHPLUGIN_H
#define DISPATCHPLUGIN_H

#include "erp_dispatch_global.h"
#include "interfaces.h"

class DispatchMainWindow;

class ERP_DISPATCHSHARED_EXPORT DispatchPlugin: public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.dispatch")
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
    DispatchMainWindow *m_dispatch;
};

#endif // DISPATCHPLUGIN_H
