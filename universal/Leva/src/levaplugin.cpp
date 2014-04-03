#include "levaplugin.h"


#include "levamainwindow.h"
#include <QtPlugin>

QMainWindow *LevaPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	m_qc = new LevaMainWindow(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_qc);
	return mw;
}

QString LevaPlugin::pluginName()
{
	return "Leva SQL";
}

QString LevaPlugin::pluginDescription()
{
	return "Used to manage remote mysql database servers and their content.";
}

QString LevaPlugin::pluginVersion()
{
	return "2.0";
}

QString LevaPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString LevaPlugin::pluginAuthor()
{
	return "joejoshw@gmail.com";
}

QStringList LevaPlugin::subWindows()
{
	QStringList w;
	return w;
}

QString LevaPlugin::projectName()
{
	return "universal";
}


#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(reportmaster, ReportMasterPlugin)
#endif

