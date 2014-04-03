#include "imsplugin.h"



#include "imsmainwindow.h"
#include <QtPlugin>
#include "ims_mw.h"
QMainWindow *ImsPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	//m_ims = new ImsMainWindow(parent, database);
	m_ims2 = new ims_mw(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_ims2);
	return mw;
}

QString ImsPlugin::pluginName()
{
	return "IMS";
}

QString ImsPlugin::pluginDescription()
{
	return "Manage Imports";
}

QString ImsPlugin::pluginVersion()
{
	return "2.0";
}

QString ImsPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ImsPlugin::pluginAuthor()
{
	return "MCL";
}

QStringList ImsPlugin::subWindows()
{
	QStringList w;
	//    w << "Cust\tManage Users and User Roles\tMCL"
	//      << "Sales Reps\tManage Sale Representatives\tMCL";
	return w;
}

QString ImsPlugin::projectName() {
	return "megvel";
}


#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_ims, ImsPlugin)
#endif
//Q_EXPORT_PLUGIN2(erp_ims, ImsPlugin)
