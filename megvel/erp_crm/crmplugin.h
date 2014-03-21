#ifndef CRMPLUGIN_H
#define CRMPLUGIN_H

#include "erp_crm_global.h"
#include <QtGui>
#include "interfaces.h"

class CRMMainWindow;

class ERP_CRMSHARED_EXPORT CrmPlugin : public QObject, public MainWindowInterface
{
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.crm")
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
    CRMMainWindow   *m_crm;
};

#endif // CRMPLUGIN_H
