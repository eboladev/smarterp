#ifndef COMPLAINSPLUGIN_H
#define COMPLAINSPLUGIN_H

#include <QtGui>
#include "interfaces.h"

#include "erp_complains_mainwindow.h"

class ComplainsPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.complains")
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
    Erp_Complains_MainWindow *m_complains;
};

#endif // COMPLAINSPLUGIN_H
