#include "companyplugin.h"
#include "company.h"
#include <QtPlugin>

QMainWindow *CompanyPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database){
	m_company = new Company(parent, database);
	QMainWindow *mw =  qobject_cast<QMainWindow *>(m_company);
	return mw;
}

QString CompanyPlugin::pluginName()
{
	return "Company Management";
}

QString CompanyPlugin::pluginDescription()
{
	return "Manage Administrative aspects of the database";
}

QString CompanyPlugin::pluginVersion()
{
	return "2.0";
}

QString CompanyPlugin::releaseDate()
{
	return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString CompanyPlugin::pluginAuthor()
{
	return "MCL";
}

QStringList CompanyPlugin::subWindows()
{
	QStringList w;
	w << "Users\tManage Users and User Roles\tMCL"
	  << "Sales Reps\tManage Sale Representatives\tMCL";
	return w;
}

QString CompanyPlugin::projectName() {
	return "megvel";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(erp_company, CompanyPlugin)
#endif
//
