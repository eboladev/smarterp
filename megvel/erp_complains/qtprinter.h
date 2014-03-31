#ifndef QTPRINTER_H
#define QTPRINTER_H

#include <QObject>
#include <QtSql>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
    //#include <QPrintSupport/QPrinter>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrinter>
#endif
#include <QtXml>

#include <QPrinter>

class QtPrinter : public QObject
{
    Q_OBJECT
public:
    explicit QtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString where = QString(),
                       QString report = QString());

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

#endif // QTPRINTER_H
