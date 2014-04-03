#include "storesplugin.h"


#include "storesmainwindow.h"
#include <QtPlugin>

QMainWindow *StoresPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	m_stores = new StoresMainWindow(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_stores);
	return mw;
}

QString StoresPlugin::pluginName()
{
	return "Stores";
}

QString StoresPlugin::pluginDescription()
{
	return "Inventory management.";
}

QString StoresPlugin::pluginVersion()
{
	return "3.0";
}

QString StoresPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString StoresPlugin::pluginAuthor()
{
	return "MCL";
}

QStringList StoresPlugin::subWindows()
{
	QStringList w;
	//    w << "Cust\tManage Users and User Roles\tMCL"
	//      << "Sales Reps\tManage Sale Representatives\tMCL";
	return w;
}

QString StoresPlugin::projectName() {
	return "megvel";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_stores, StoresPlugin)
#endif

