#ifndef STORESPLUGIN_H
#define STORESPLUGIN_H

//#include "erp_stores_global.h"
#include <QtGui>
#include "interfaces.h"

class StoresMainWindow;

class StoresPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.stores")
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
    StoresMainWindow *m_stores;
};

#endif // QCPLUGIN_H
