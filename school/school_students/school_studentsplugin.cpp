#include "school_studentsplugin.h"
#include "studentsmainwindow.h"
#include <QtPlugin>

QMainWindow *school_studentsPlugin::pluginMainWindow(QWidget *parent, QSqlDatabase database){
    m_tt = new StudentsMainWindow(parent, database);
    QMainWindow *mw =  qobject_cast<QMainWindow *>(m_tt);
    return mw;
}

QString school_studentsPlugin::pluginName()
{
    return "Students";
}

QString school_studentsPlugin::pluginDescription()
{
    return "Student management centre. Manage student information, exam grading, class setup and timetable settings.";
}

QString school_studentsPlugin::pluginVersion()
{
    return "0.0.1a";
}

QString school_studentsPlugin::releaseDate()
{
    return QObject::tr("%1 %2").arg(__DATE__, __TIME__);
}

QString school_studentsPlugin::pluginAuthor()
{
    return "Smart Software";
}

QStringList school_studentsPlugin::subWindows()
{
    QStringList w;
    return w;
}

QString school_studentsPlugin::projectName() {
    return "school";
}

Q_EXPORT_PLUGIN2(school_students, school_studentsPlugin)
