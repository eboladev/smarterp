#include "imsstoreplugin.h"

#include "imsstoremainwindow.h"
#include <QtPlugin>
QMainWindow *ImsStorePlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {

    mw = new ImsStoreMainWindow(parent, database);
    QMainWindow *mw2 =  qobject_cast<QMainWindow *>(mw);
    return mw2;
}

QString ImsStorePlugin::pluginName()
{
    return "Ims-Store";
}

QString ImsStorePlugin::pluginDescription()
{
    return "Link Imports process to the stores.";
}

QString ImsStorePlugin::pluginVersion()
{
    return "13.09.09";
}

QString ImsStorePlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ImsStorePlugin::pluginAuthor()
{
    return "joejoshw@gmail.com";
}

QStringList ImsStorePlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString ImsStorePlugin::projectName() {
    return "megvel";
}

#if QT_VERSION < 0x50000
    Q_EXPORT_PLUGIN2(erp_ims_store, ImsStorePlugin)
#endif
