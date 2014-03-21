#ifndef CUSTOMERSPLUGIN_H
#define CUSTOMERSPLUGIN_H

#include "erp_customers_global.h"
#include <QtGui>
#include "interfaces.h"

class CustomerMainWindow;

class ERP_CUSTOMERSSHARED_EXPORT CustomersPlugin : public QObject, public MainWindowInterface {
    Q_OBJECT
    Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.megvel.customers")
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
    CustomerMainWindow *m_customers;
};

#endif // CUSTOMERSPLUGIN_H
