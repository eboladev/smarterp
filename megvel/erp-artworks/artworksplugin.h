#ifndef STORESPLUGIN_H
#define STORESPLUGIN_H

//#include "erp-artworks_global.h"

#include "interfaces.h"

class ArtworksMainWindow;

class ArtworksPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.artworks")
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
    ArtworksMainWindow *m_artworks;
};

#endif // QCPLUGIN_H
