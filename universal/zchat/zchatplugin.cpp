#include "zchatplugin.h"
#include "mainwindow.h"
#include <QtPlugin>

QMainWindow *ZChatPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    m_chat_window = new MainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_chat_window);
    return mw;
}

QString ZChatPlugin::pluginName()
{
    return "Network Chat";
}

QString ZChatPlugin::pluginDescription()
{
    return "Chat with other users in the Company, share files and ideas.";
}

QString ZChatPlugin::pluginVersion()
{
    return "1.0";
}

QString ZChatPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ZChatPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList ZChatPlugin::subWindows()
{
    QStringList w;
    return w;
}

QString ZChatPlugin::projectName() {
    return "universal";
}
#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(zchatplugin, ZChatPlugin)
#endif
