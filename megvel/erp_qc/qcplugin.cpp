#include "qcplugin.h"


#include "qcmainwindow.h"
#include <QtPlugin>

QMainWindow *QcPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	m_qc = new QcMainWindow(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_qc);
	return mw;
}

QString QcPlugin::pluginName()
{
	return "Qc";
}

QString QcPlugin::pluginDescription()
{
	return "Used to view and enter Qc Measurements and analysis results.";
}

QString QcPlugin::pluginVersion()
{
	return "3.0";
}

QString QcPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString QcPlugin::pluginAuthor()
{
	return "MCL";
}

QStringList QcPlugin::subWindows()
{
	QStringList w;
	//    w << "Cust\tManage Users and User Roles\tMCL"
	//      << "Sales Reps\tManage Sale Representatives\tMCL";
	return w;
}

QString QcPlugin::projectName() {
	return "megvel";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_qc, QcPlugin)
#endif
