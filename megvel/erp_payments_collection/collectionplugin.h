#ifndef COLLECTIONPLUGIN_H
#define COLLECTIONPLUGIN_H

#include <QtGui>
#include "interfaces.h"

#include "collectionmainwindow.h"
class CollectionPlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
	Q_PLUGIN_METADATA(IID "com.erp.megvel.collections")
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
	CollectionMainWindow *mCollection;
};

#endif // COLLECTIONPLUGIN_H
