#include "reportmasterplugin.h"


#include "mainwindow.h"
#include <QtPlugin>

QMainWindow *ReportMasterPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
	m_reports_mainwindow = new MainWindow(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_reports_mainwindow);
	return mw;
}

QString ReportMasterPlugin::pluginName()
{
	return "Report Master";
}

QString ReportMasterPlugin::pluginDescription()
{
	return "Report viewer. View database reports, print them, and export them to popular formats such as PDF, HTML, etc.";
}

QString ReportMasterPlugin::pluginVersion()
{
	return "1.0";
}

QString ReportMasterPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ReportMasterPlugin::pluginAuthor()
{
	return "MCL";
}

QStringList ReportMasterPlugin::subWindows()
{
	QStringList w;
	return w;
}

QString ReportMasterPlugin::projectName() {
	return "universal";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(reportmaster, ReportMasterPlugin)
#endif
