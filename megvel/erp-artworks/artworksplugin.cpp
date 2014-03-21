#include "artworksplugin.h"


#include "artworksmainwindow.h"
#include <QtPlugin>

QMainWindow *ArtworksPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    m_artworks = new ArtworksMainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_artworks);
    return mw;
}

QString ArtworksPlugin::pluginName()
{
    return "Artworks";
}

QString ArtworksPlugin::pluginDescription()
{
    return "Artworks Management";
}

QString ArtworksPlugin::pluginVersion()
{
    return "3.0";
}

QString ArtworksPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ArtworksPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList ArtworksPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString ArtworksPlugin::projectName() {
    return "megvel";
}

#if QT_VERSION < 0x50000
    Q_EXPORT_PLUGIN2(erp_stores_artworks, ArtworksPlugin)
#endif
//Q_EXPORT_PLUGIN2(erp_qc, QcPlugin)
