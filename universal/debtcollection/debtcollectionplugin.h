#ifndef DEBTCOLLECTIONPLUGIN_H
#define DEBTCOLLECTIONPLUGIN_H


#include "interfaces.h"
#include <QtSql>

class DCMainWindow;

class  DebtCollectionPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.debtcollection")
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
    DCMainWindow *m_debt;
};

#endif // DEBTCOLLECTIONPLUGIN_H
