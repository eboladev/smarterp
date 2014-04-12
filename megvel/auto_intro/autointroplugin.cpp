#include "autointroplugin.h"



#include "intromainwindow.h"
#include <QtPlugin>

QMainWindow *IntroPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	m_autoMW = new IntroMainWindow(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_autoMW);
	return mw;
}

QString IntroPlugin::pluginName()
{
	return "Automatic Introduction";
}

QString IntroPlugin::pluginDescription()
{
	return "Dynamic customizable welcome screen. Shows different content based on logged in user.";
}

QString IntroPlugin::pluginVersion()
{
	return "0.0.0.1";
}

QString IntroPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString IntroPlugin::pluginAuthor()
{
	return "Joseph W Joshua <joejoshw@gmail.com>";
}

QStringList IntroPlugin::subWindows()
{
	QStringList w;
	//    w << "Cust\tManage Users and User Roles\tMCL"
	//      << "Sales Reps\tManage Sale Representatives\tMCL";
	return w;
}

QString IntroPlugin::projectName() {
	return "megvel";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_customers, CustomersPlugin)
#endif

