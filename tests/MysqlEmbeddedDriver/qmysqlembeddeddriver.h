
#ifndef QMYSQLEMBEDDEDDRIVER_H
#define QMYSQLEMBEDDEDDRIVER_H

#include <QtSql/qsqldriver.h>
#include <QtSql/qsqlresult.h>

#if defined (Q_OS_WIN32)
#include <QtCore/qt_windows.h>
#endif

#include <mysql.h>

#ifdef QT_PLUGIN
#define Q_EXPORT_SQLDRIVER_MYSQL
#else
#define Q_EXPORT_SQLDRIVER_MYSQL Q_SQL_EXPORT
#endif

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QMYSQLEmbeddedDriverPrivate;
class QMYSQLEmbeddedResultPrivate;
class QMYSQLEmbeddedDriver;
class QSqlRecordInfo;

class QMYSQLEmbeddedResult : public QSqlResult
{
    friend class QMYSQLEmbeddedDriver;
    friend class QMYSQLEmbeddedResultPrivate;
public:
    explicit QMYSQLEmbeddedResult(const QMYSQLEmbeddedDriver* db);
    ~QMYSQLEmbeddedResult();

    QVariant handle() const;
protected:
    void cleanup();
    bool fetch(int i);
    bool fetchNext();
    bool fetchLast();
    bool fetchFirst();
    QVariant data(int field);
    bool isNull(int field);
    bool reset (const QString& query);
    int size();
    int numRowsAffected();
    QVariant lastInsertId() const;
    QSqlRecord record() const;
    void virtual_hook(int id, void *data);
    bool nextResult();

#if MYSQL_VERSION_ID >= 40108
    bool prepare(const QString& stmt);
    bool exec();
#endif
private:
    QMYSQLEmbeddedResultPrivate* d;
};

class Q_EXPORT_SQLDRIVER_MYSQL QMYSQLEmbeddedDriver : public QSqlDriver
{
    Q_OBJECT
    friend class QMYSQLEmbeddedResult;
public:
    explicit QMYSQLEmbeddedDriver(QObject *parent=0);
    explicit QMYSQLEmbeddedDriver(MYSQL *con, QObject * parent=0);
    ~QMYSQLEmbeddedDriver();
    bool hasFeature(DriverFeature f) const;
    bool open(const QString & db,
               const QString & user,
               const QString & password,
               const QString & host,
               int port,
               const QString& connOpts);
    void close();
    QSqlResult *createResult() const;
    QStringList tables(QSql::TableType) const;
    QSqlIndex primaryIndex(const QString& tablename) const;
    QSqlRecord record(const QString& tablename) const;
    QString formatValue(const QSqlField &field,
                                     bool trimStrings) const;
    QVariant handle() const;
    QString escapeIdentifier(const QString &identifier, IdentifierType type) const;

protected Q_SLOTS:
    bool isIdentifierEscapedImplementation(const QString &identifier, IdentifierType type) const;

protected:
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
private:
    void init();
    QMYSQLEmbeddedDriverPrivate* d;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QMYSQLEMBEDDEDDRIVER_H
