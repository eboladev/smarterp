#include "importfromsql.h"
#include <QMessageBox>
ImportFromSQL::ImportFromSQL(QObject *parent, QString fileName, QSqlDatabase mysql) :
    QObject(parent)
{
    prg = new QProgressDialog(0);
    prg->setWindowTitle("Data Preparation schedule");
    fName = fileName;
    prg->show();
    ThreadedImporter *th = new ThreadedImporter(this, mysql, fileName);
    connect (th, SIGNAL(error(QString)), SLOT(error(QString)));
    connect (th, SIGNAL(finished()), prg, SLOT(close()));
    connect (th, SIGNAL(minMax(int,int)), SLOT(threadMinMax(int,int)));
    connect (th, SIGNAL(progress(int)), SLOT(threadProgress(int)));
    connect (th, SIGNAL(terminated()), prg, SLOT(close()));

    th->start();
}

void ImportFromSQL::threadProgress(int p)
{
    prg->setValue(p);
}


ThreadedImporter::ThreadedImporter(QObject *parent, QSqlDatabase mysql, QString fileName)
    : QThread(parent)
{
    db = mysql;
    fName = fileName;


}

#include <QFile>
void ThreadedImporter::run()
{
    static char *server_options[] \
    {
        "mysql_test",
        "--datadir=./embedded/data",
        "--language=./embedded/language",
        "--key-buffer-size=256M",
        NULL };
    int num_elements = (sizeof(server_options) / sizeof(char *)) - 1;
    static char *server_groups[] = { "mysql_test", NULL };
    mysql_library_init(num_elements, server_options, server_groups);
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);
    emit status("Connecting to mysqld");
    if (mysql_real_connect(&mysql, NULL, NULL, NULL, "mysql", 0, NULL, 0))
    {
        emit status("Connected to mysqld");

        QFile f(fName);
        quint64 readd;
        readd = 0;
        QString currentDelimiter = ";";
        QString readQuery = "";
        if (f.open(QIODevice::ReadOnly)) {
            quint64 byte_count = f.size();
            emit minMax(0, byte_count);
            while (!f.atEnd()) {
                QByteArray line = f.readLine();
                bool isComment = false;
                if (QString(line).startsWith("/*")) {
                    isComment = true;
                }
                if (QString(line).startsWith("/*!5")) {
                    isComment = false;
                }
                if (!isComment) {
                    if (line.trimmed().startsWith("DELIMITER")) {
                        currentDelimiter = line.trimmed().right(line.trimmed().length() - 10);
                    }
                    if (!QString(line).contains(currentDelimiter)) {
                        readQuery.append(line);
                    } else {
                        readQuery.append(line);
                        runQuery(readQuery);
                        readQuery = "";
                    }
                    if (line.trimmed().startsWith("DELIMITER")) {
                        currentDelimiter = line.trimmed().right(line.trimmed().length() - 10);
                    }
                    readd = readd + line.size();
                    emit progress(readd);
                }
            }
        } else {
            emit(error("File Error: " + f.errorString()));
        }
    } else {
        emit(error("Database Error: " + QString(mysql_error(&mysql))));
    }

    qDebug() << "File read finished";
}



void ImportFromSQL::threadMinMax(quint64 min, quint64 max)
{
    prg->setMinimum(min);
    prg->setMaximum(max);
}

void ImportFromSQL::error(QString err)
{
    QMessageBox::critical(0, "Database Error", err);
}


void ImportFromSQL::threadStatus(QString s)
{
    prg->setLabelText(s);
}


void ThreadedImporter::runQuery(QString q)
{

    //   qDebug() << q;
    //    db.exec(q);
    //    if (db.lastError().isValid()) {
    //        qDebug() << db.lastError().text();
    //    } else {
    //        qDebug() << "OK";
    //    }
    if (mysql_query(&mysql, q.toLocal8Bit().data()) > 0){
        qDebug() << mysql_error(&mysql) << "{" << q << "}";
    } else {
        //qDebug() << "OK";
    }
}

