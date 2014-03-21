#include "CrmPlugin.h"


#include  "crmmainwindow.h"


QMainWindow *CrmPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    m_crm = new CRMMainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_crm);
    return mw;
}

QString CrmPlugin::pluginName()
{
    return "Customer Management";
}

QString CrmPlugin::pluginDescription()
{
    return "Manage customers, their products, costings, job tickets and other customer related aspects of the database";
}

QString CrmPlugin::pluginVersion()
{
    return "2.0";
}

QString CrmPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString CrmPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList CrmPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString CrmPlugin::projectName() {
    return "megvel";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_crm, CrmPlugin)
#endif

