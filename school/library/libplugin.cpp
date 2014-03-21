#include "../library/libplugin.h"
#include "../library/librarymainwindow.h"
#include <QtPlugin>

QMainWindow *LibPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database){
    m_lib = new LibraryMainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_lib);
    return mw;
    //(c) JWJ
}

QString LibPlugin::pluginName()
{
    return "Library";
}

QString LibPlugin::pluginDescription()
{
    return "School library management, book keeping and loaning.";
}

QString LibPlugin::pluginVersion()
{
    return "0.0.1a";
}

QString LibPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString LibPlugin::pluginAuthor()
{
    return "Smart Software";
}

QStringList LibPlugin::subWindows()
{
    QStringList w;
    return w;
}

QString LibPlugin::projectName() {
    return "school";
}

Q_EXPORT_PLUGIN2(library, LibPlugin)
