#ifndef COMPANYPLUGIN_H
#define COMPANYPLUGIN_H

#include <QtSql>

#include <QObject>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include "interfaces.h"

class Company;

class CompanyPlugin : public QObject,
		public MainWindowInterface
{
	Q_OBJECT
	Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "com.erp.megvel.company")
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
signals:

public slots:

private:
	Company *m_company;
};

#endif // COMPANYPLUGIN_H
