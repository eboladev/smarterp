#include <qsqldriverplugin.h>
#include <qstringlist.h>
#include "qmysqlembeddeddriver.h"

QT_BEGIN_NAMESPACE

class QMYSQLDriverEmbeddedPlugin : public QSqlDriverPlugin
{
public:
    QMYSQLDriverEmbeddedPlugin();

    QSqlDriver* create(const QString &);
    QStringList keys() const;
};

QMYSQLDriverEmbeddedPlugin::QMYSQLDriverEmbeddedPlugin()
    : QSqlDriverPlugin()
{
}

QSqlDriver* QMYSQLDriverEmbeddedPlugin::create(const QString &name)
{
    if (name == QLatin1String("QMYSQLEMBEDDED") || name == QLatin1String("QMYSQLEMBEDDED3")) {
        QMYSQLEmbeddedDriver* driver = new QMYSQLEmbeddedDriver();
        return driver;
    }
    return 0;
}

QStringList QMYSQLDriverEmbeddedPlugin::keys() const
{
    QStringList l;
    l << QLatin1String("QMYSQLEMBEDDED3");
    l << QLatin1String("QMYSQLEMBEDDED");
    return l;
}

Q_EXPORT_STATIC_PLUGIN(QMYSQLDriverEmbeddedPlugin)
Q_EXPORT_PLUGIN2(qsqlmysql, QMYSQLDriverEmbeddedPlugin)

QT_END_NAMESPACE
