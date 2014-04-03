#ifndef SMARTPAYPLUGIN_H
#define SMARTPAYPLUGIN_H

//#include "smartpay_global.h"
#include "interfaces.h"

class MainWindow;

class SmartPayPlugin : public QObject, public MainWindowInterface {
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.universal.smartpay")
#endif
public:
	QMainWindow *pluginMainWindow(QWidget *parent, QSqlDatabase database);
	QString pluginName();
	QString pluginDescription();
	QString pluginVersion();
	QString releaseDate();
	QString pluginAuthor();
	QStringList subWindows();
private:
	MainWindow *m_payroll;
};
#endif // SMARTPAYPLUGIN_H
