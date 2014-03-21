#ifndef REELSPLUGIN_H
#define REELSPLUGIN_H


//#include "erp_qc_global.h"
#include <QtGui>
#include "interfaces.h"

class ReelsMainWindow;

class ReelsPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.reels")
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
    ReelsMainWindow *m_reels;
};


#endif // REELSPLUGIN_H
