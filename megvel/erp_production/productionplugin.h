#ifndef PRODUCTIONPLUGIN_H
#define PRODUCTIONPLUGIN_H

//#include "erp_production_global.h"
#include "interfaces.h"
#include <QtGui>
#include <QtSql>

class ProductionMainWindow;

class  ProductionPlugin : public QObject, public MainWindowInterface
{
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.production")
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
    ProductionMainWindow *m_production;
    QSqlDatabase db;
};

#endif // PRODUCTIONPLUGIN_H
