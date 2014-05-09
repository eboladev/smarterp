#include "closuresplugin.h"


#include "closuresmainwindow.h"
#include <QtPlugin>

QMainWindow *ImsPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {

	QSqlDatabase closuresDB = QSqlDatabase::addDatabase("QMYSQL", "closures");
	closuresDB.setHostName(database.hostName());
	closuresDB.setUserName(database.userName());
	closuresDB.setPassword(database.password());
	closuresDB.setDatabaseName("crm");

	if (closuresDB.open()) {
		//
	}

	m_mw = new ClosuresMainWindow(parent, closuresDB);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_mw);
	return mw;
}

QString ImsPlugin::pluginName()
{
	return "Closures";
}

QString ImsPlugin::pluginDescription()
{
	return "Closures Division CRM";
}

QString ImsPlugin::pluginVersion()
{
	return "1.1 beta";
}

QString ImsPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ImsPlugin::pluginAuthor()
{
	return "Joshua";
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
Q_EXPORT_PLUGIN2(erp_closures, ClosuresPlugin)
#endif
