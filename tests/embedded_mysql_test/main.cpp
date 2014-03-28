#include <QCoreApplication>
#include <QtSql>

#include "C:\Qt\sdk\QtSources\4.8.1\src\sql\drivers\mysql\qsql_mysql.cpp"


#include <mysql.h>
#include <QtSql/qsqldriver.h>
#include <QtSql/qsqlresult.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Starting custom mysql server";

    MYSQL *mysql;

    static char *server_options[] \
    { "mysql_test", "--defaults-file=embed/my.cnf", NULL };

    int num_elements = (sizeof(server_options) / sizeof(char *)) - 1;

    static char *server_groups[] = { "embedded", NULL };

    qDebug() << "Loading embedded";
    mysql_library_init(num_elements, server_options, server_groups);
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "embedded");
    mysql_options(mysql, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);

    mysql_real_connect(mysql, NULL, NULL, NULL, "database1", 0, NULL, 0);

    qDebug() << "Embedded mysql configuration ready. Creating Qt driver";

    return a.exec();
}
