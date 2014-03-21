#ifndef TTPLUGIN_H
#define TTPLUGIN_H

#include <QtSql>

#include <QObject>
#include <QMainWindow>
#include "interfaces.h"

class StudentsMainWindow;

class school_studentsPlugin : public QObject,
        public MainWindowInterface
{
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
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
    StudentsMainWindow *m_tt;
};

#endif // TTPLUGIN_H
