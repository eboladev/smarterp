#include "complainsplugin.h"

#include <QtPlugin>

QMainWindow *ComplainsPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    m_complains = new Erp_Complains_MainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_complains);
    return mw;
}

QString ComplainsPlugin::pluginName()
{
    return "Complains";
}

QString ComplainsPlugin::pluginDescription()
{
    return "Used to enter and follow up on customer complains.";
}

QString ComplainsPlugin::pluginVersion()
{
    return "1.0";
}

QString ComplainsPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ComplainsPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList ComplainsPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString ComplainsPlugin::projectName() {
    return "megvel";
}

#if QT_VERSION < 0x50000
    Q_EXPORT_PLUGIN2(erp_complains, ComplainsPlugin)
#endif
//
