#include "productionplugin.h"
#include <QtPlugin>

#include "productionmainwindow.h"
QMainWindow *ProductionPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    m_production = new ProductionMainWindow  (parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_production);
    return mw;
}

QString ProductionPlugin::pluginName()
{
    return "Production";
}

QString ProductionPlugin::pluginDescription()
{
    return "Used for production scheduling and monitoring.";
}

QString ProductionPlugin::pluginVersion()
{
    return "2.0";
}

QString ProductionPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ProductionPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList ProductionPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString ProductionPlugin::projectName() {
    return "megvel";
}


#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_production, ProductionPlugin)
#endif
