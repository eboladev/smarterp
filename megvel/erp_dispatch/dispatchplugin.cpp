#include "dispatchplugin.h"

#include "dispatchmainwindow.h"
#include <QtPlugin>


QMainWindow *DispatchPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	m_dispatch = new DispatchMainWindow(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_dispatch);
	return mw;
}

QString DispatchPlugin::pluginName()
{
	return "Dispatch";
}

QString DispatchPlugin::pluginDescription()
{
	return "Dispatch data entry and delivery confirmation.";
}

QString DispatchPlugin::pluginVersion()
{
	return "2.0 beta";
}

QString DispatchPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString DispatchPlugin::pluginAuthor()
{
	return "MCL";
}

QStringList DispatchPlugin::subWindows()
{
	QStringList w;
	//    w << "Cust\tManage Users and User Roles\tMCL"
	//      << "Sales Reps\tManage Sale Representatives\tMCL";
	return w;
}

QString DispatchPlugin::projectName() {
	return "megvel";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_dispatch, DispatchPlugin)
#endif

