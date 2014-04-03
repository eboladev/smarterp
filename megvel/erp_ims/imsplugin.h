#ifndef IMSPLUGIN_H
#define IMSPLUGIN_H

#include <QtGui>
#include "interfaces.h"

class ImsMainWindow;
class ims_mw;

class  ImsPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.ims")
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
    ImsMainWindow *m_ims;
    ims_mw *m_ims2;
};

#endif // IMSPLUGIN_H
