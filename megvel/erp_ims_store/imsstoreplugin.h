#ifndef IMSSTOREPLUGIN_H
#define IMSSTOREPLUGIN_H

#include <QtGui>
#include "interfaces.h"

class ImsStoreMainWindow;


class  ImsStorePlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.megvel.ims_store")
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
	ImsStoreMainWindow *mw;
};


#endif // IMSSTOREPLUGIN_H
