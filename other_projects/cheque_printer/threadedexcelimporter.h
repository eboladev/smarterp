#ifndef THREADEDEXCELIMPORTER_H
#define THREADEDEXCELIMPORTER_H

#include <QThread>
#include <QtSql>

class ThreadedExcelImporter : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedExcelImporter(QObject *parent = 0);
    void run();
    void setFileName(QString path);
private:
    QSqlDatabase db;
    QString m_fileName;
signals:
    void message(QString m);
    void error(QString e);
public slots:

};

#endif // THREADEDEXCELIMPORTER_H
