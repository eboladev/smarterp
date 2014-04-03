#ifndef REPORTGENERATORPLUGIN_H
#define REPORTGENERATORPLUGIN_H

//#include "reportgenerator_global.h"
#include <QtGui>
#include "interfaces.h"

class MainWindow;

class  ReportGeneratorPlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.universal.generator")
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
	MainWindow *m_generator;
};
#endif // REPORTGENERATORPLUGIN_H
