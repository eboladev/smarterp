#include "generatorplugin.h"


#include "mainwindow.h"
#include <QtPlugin>

QMainWindow *ReportGeneratorPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database) {
   m_generator  = new MainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_generator);
    return mw;
}

QString ReportGeneratorPlugin::pluginName()
{
    return "Report Generator";

}

QString ReportGeneratorPlugin::pluginDescription()
{
    return "Report Generator. Create reports and save then in the database. View, Print or Export existing reports.";
}

QString ReportGeneratorPlugin::pluginVersion()
{
    return "1.6";
}

QString ReportGeneratorPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString ReportGeneratorPlugin::pluginAuthor()
{
    return "MCL";
}

QStringList ReportGeneratorPlugin::subWindows()
{
    QStringList w;
//    w << "Cust\tManage Users and User Roles\tMCL"
//      << "Sales Reps\tManage Sale Representatives\tMCL";
    return w;
}

QString ReportGeneratorPlugin::projectName() {
    return "universal";
}

#if QT_VERSION < 0x50000
Q_EXPORT_PLUGIN2(reportgenerator, ReportGeneratorPlugin)
#endif
