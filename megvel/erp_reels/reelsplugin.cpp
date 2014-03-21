
#include "reelsplugin.h"


#include "reelsmainwindow.h"
#include <QtPlugin>

QMainWindow *ReelsPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    m_reels = new ReelsMainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_reels);
    return mw;
}

QString ReelsPlugin::pluginName()
{
    return "Reels";
}

QString ReelsPlugin::pluginDescription()
{
    return "Used to manage paper reels, and check reel usage.";
}

QString ReelsPlugin::pluginVersion()
{
    return "1.0";
}

QString ReelsPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ReelsPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList ReelsPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString ReelsPlugin::projectName() {
    return "megvel";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_reels, ReelsPlugin)
#endif
