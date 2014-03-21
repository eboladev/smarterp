#ifndef COMPANYPLUGIN_H
#define COMPANYPLUGIN_H

#include <QtSql>

#include <QObject>
#include <QMainWindow>
#include "interfaces.h"

class LibraryMainWindow;

class LibPlugin : public QObject,
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
    LibraryMainWindow *m_lib;
};

#endif // COMPANYPLUGIN_H
