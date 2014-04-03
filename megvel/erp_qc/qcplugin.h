#ifndef QCPLUGIN_H
#define QCPLUGIN_H

//#include "erp_qc_global.h"
#include <QtGui>
#include "interfaces.h"

class QcMainWindow;

class QcPlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.megvel.qc")
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
	QcMainWindow *m_qc;
};

#endif // QCPLUGIN_H
