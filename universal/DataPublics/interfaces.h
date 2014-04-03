#ifndef INTERFACES_H
#define INTERFACES_H


#include <QMainWindow>
#include <QtPlugin>
#include <QtSql>
#include <QMainWindow>
class MainWindowInterface
{
public:
	virtual QMainWindow *pluginMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase()) {Q_UNUSED(parent); Q_UNUSED(database); return new QMainWindow(0);}
	virtual QString pluginName() { return ""; }
	virtual QString pluginDescription() {return "";}
	virtual QString pluginVersion() { return ""; }
	virtual QString releaseDate() {return QObject::tr("%1 %2").arg(__DATE__, __TIME__);}
	virtual QStringList subWindows() {return QStringList();}
	virtual QString pluginAuthor() {return "";}
	virtual void setDatabase(QSqlDatabase database = QSqlDatabase()) {db = database; }
	virtual QString projectName() { return "Megvel"; }
private:
	QSqlDatabase db;
};

Q_DECLARE_INTERFACE(MainWindowInterface, "com.panther.Megvel.ERP.MainWindowInterface/1.0")

#endif // INTERFACES_H
