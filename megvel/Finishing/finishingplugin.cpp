#include "finishingplugin.h"

#include <QtPlugin>


QMainWindow *FinishingPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	mFinishing = new FinishingMainWindow(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(mFinishing);
	return mw;
}

QString FinishingPlugin::pluginName()
{
	return "Finishing";
}

QString FinishingPlugin::pluginDescription()
{
	return "Used to enter finishing data (Peeling, Stitching and Gluing).";
}

QString FinishingPlugin::pluginVersion()
{
	return "2.0";
}

QString FinishingPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString FinishingPlugin::pluginAuthor()
{
	return "MCL";
}

QStringList FinishingPlugin::subWindows()
{
	QStringList w;
	//    w << "Cust\tManage Users and User Roles\tMCL"
	//      << "Sales Reps\tManage Sale Representatives\tMCL";
	return w;
}

QString FinishingPlugin::projectName() {
	return "megvel";
}


#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_production_finishing, FinishingPlugin)
#endif
