#ifndef LEVAPLUGIN_H
#define LEVAPLUGIN_H


#include <QtGui>
#include "interfaces.h"

class LevaMainWindow;

class LevaPlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.universal.leva")
#endif
public:
	QMainWindow     *pluginMainWindow(QWidget *parent, QSqlDatabase database);
	QString         pluginName();
	QString         pluginDescription();
	QString         pluginVersion();
	QString         releaseDate();
	QString         pluginAuthor();
	QStringList     subWindows();
	QString         projectName();
private:
	LevaMainWindow  *m_qc;
};

#endif // LEVAPLUGIN_H
