#ifndef REPORTMASTERPLUGIN_H
#define REPORTMASTERPLUGIN_H

#include "reportmaster_global.h"
#include <QtGui>
#include "interfaces.h"

class MainWindow;

class REPORTMASTERSHARED_EXPORT ReportMasterPlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.universal.reportmaster")
#endif
public:
	QMainWindow *pluginMainWindow(QWidget *parent, QSqlDatabase database);
	QString pluginName();
	QString pluginDescription();
	QString pluginVersion();
	QString releaseDate();
	QString pluginAuthor();
	QStringList subWindows();
	QString projectName();
private:
	MainWindow *m_reports_mainwindow;
};
#endif // REPORTMASTERPLUGIN_H
