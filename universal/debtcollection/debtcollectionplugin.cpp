#include "debtcollectionplugin.h"

#include "dcmainwindow.h"
#include <QtPlugin>

QMainWindow *DebtCollectionPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	Q_UNUSED(database)
	m_debt  = new DCMainWindow(parent);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_debt);
	return mw;
}

QString DebtCollectionPlugin::pluginName()
{
	return "Debt Collection";
}

QString DebtCollectionPlugin::pluginDescription()
{
	return "Debt collection and scheduling.";
}

QString DebtCollectionPlugin::pluginVersion()
{
	return "13.09.09";
}

QString DebtCollectionPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString DebtCollectionPlugin::pluginAuthor()
{
	return "MCL";
}

QStringList DebtCollectionPlugin::subWindows()
{
	QStringList w;
	//    w << "Cust\tManage Users and User Roles\tMCL"
	//      << "Sales Reps\tManage Sale Representatives\tMCL";
	return w;
}

QString DebtCollectionPlugin::projectName() {
	return "universal";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(debtcollection, DebtCollectionPlugin)
#endif
//
