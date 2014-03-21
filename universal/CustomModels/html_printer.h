#ifndef HTMLPRINTER_H
#define HTMLPRINTER_H

#include <QObject>
#include <QtSql>

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtPrintSupport/QPrinter>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrinter>
#endif
#include <QtXml>

class HTML_PRINTER : public QObject
{
    Q_OBJECT
public:
    explicit HTML_PRINTER(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString sqlQuery = QString(),
                          QString reportTitle = QString());
    explicit HTML_PRINTER(QWidget *parent = 0, QString rpt_title = QString(), QString html = QString());

signals:

public slots:
    void printRequested(QPrinter *printer);
private:
    QSqlDatabase db;
    QPrinter *printer;
    QString sql;
    QString title;
    QString rawHtml;
    QSqlQuery qu;
    void initVariables();
    bool isRaw;
    QWidget *par;
};

class DbPrinter : public QObject {
    Q_OBJECT
public:
    explicit DbPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString reportName = QString(), QString param = QString());

signals:

public slots:
    void printRequested(QPrinter *printer);

private:
    QSqlDatabase db;
    QPrinter *printer;
    QString reportName;
    QString param;
    QString _xml;
protected:
    QDomDocument _doc;
};

#endif // HTMLPRINTER_H
