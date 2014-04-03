#include "customersplugin.h"


#include "customermainwindow.h"
#include <QtPlugin>

QMainWindow *CustomersPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    m_customers = new CustomerMainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_customers);
    return mw;
}

QString CustomersPlugin::pluginName()
{
    return "Customer Management";
}

QString CustomersPlugin::pluginDescription()
{
    return "Manage customers, their products, costings, job tickets and other customer related aspects of the database";
}

QString CustomersPlugin::pluginVersion()
{
    return "2.0";
}

QString CustomersPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString CustomersPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList CustomersPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString CustomersPlugin::projectName() {
    return "megvel";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_customers, CustomersPlugin)
#endif

