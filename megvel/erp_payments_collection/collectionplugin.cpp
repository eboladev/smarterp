#include "collectionplugin.h"

#include <QtPlugin>


QMainWindow *CollectionPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    mCollection = new CollectionMainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(mCollection);
    return mw;
}

QString CollectionPlugin::pluginName()
{
    return "Collection";
}

QString CollectionPlugin::pluginDescription()
{
    return "Used to fetch quickbooks customer data, modify it and generate usable cash collection reports.";
}

QString CollectionPlugin::pluginVersion()
{
    return "1.0";
}

QString CollectionPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString CollectionPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList CollectionPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString CollectionPlugin::projectName() {
    return "megvel";
}


//Q_EXPORT_PLUGIN2(erp_payments_collection, CollectionPlugin)
