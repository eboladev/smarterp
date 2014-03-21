#include "smartpayplugin.h"


#include "mainwindow.h"
#include <QtPlugin>

QMainWindow *SmartPayPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
    m_payroll = new MainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_payroll);
    return mw;
}

QString SmartPayPlugin::pluginName()
{
    return "SmartPay";
}

QString SmartPayPlugin::pluginDescription()
{
    return "HRM and Payroll Management. Manage HR information, attendance and payroll calculations.";
}

QString SmartPayPlugin::pluginVersion()
{
    return "1.0";
}

QString SmartPayPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString SmartPayPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList SmartPayPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString SmartPayPlugin::projectName() {
    return "universal";
}

Q_EXPORT_PLUGIN2(smartpay, SmartPayPlugin)
