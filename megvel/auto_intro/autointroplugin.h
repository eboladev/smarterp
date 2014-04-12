#ifndef AUTOINTROPLUGIN_H
#define AUTOINTROPLUGIN_H

#include <QtGui>
#include "interfaces.h"

class IntroMainWindow;

class  IntroPlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.megvel.autointro")
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
	IntroMainWindow *m_autoMW;
};


#endif // AUTOINTROPLUGIN_H
