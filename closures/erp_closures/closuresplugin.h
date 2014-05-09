#ifndef CLOSURESPLUGIN_H
#define CLOSURESPLUGIN_H

#include <QtGui>
#include "interfaces.h"

class ClosuresMainWindow;

class  ImsPlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.megvel.closures")
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
	ClosuresMainWindow *m_mw;
};


#endif // CLOSURESPLUGIN_H
