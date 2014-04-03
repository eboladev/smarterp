#ifndef QTPRINTER_H
#define QTPRINTER_H

#include <QObject>
#include <QtSql>
#include <QPrinter>
#include <QWidget>
#include <QtXml>


class QtPrinter : public QObject
{
    Q_OBJECT
public:
    explicit QtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString where = QString(),
                       QString report = QString(), bool pdf = false);

    explicit QtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString where = QString(),
                       QString report = QString(), QString autoPdf = "No");

    explicit QtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
                        QString reportXml = QString(), bool pdf = false);
signals:
    
public slots:
    void printRequested(QPrinter *printer);
private:
    QSqlDatabase db;
    QPrinter *printer;
    QString reportName;
    QString param;
    QString _xml;
    bool makePdf;
    bool openPdf;
protected:
    QDomDocument _doc;
};

#endif // QTPRINTER_H
