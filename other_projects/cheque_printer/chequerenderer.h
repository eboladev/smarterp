#ifndef CHEQUERENDERER_H
#define CHEQUERENDERER_H

#include <QObject>
#include <QtSql>
#include <QPrinter>
#include <QWidget>
#include <QtXml>

class ChequeRenderer : public QObject
{
    Q_OBJECT
public:
    explicit ChequeRenderer(QWidget *parent = 0,
                              QString ocNo = QString(),
                              QSqlDatabase database = QSqlDatabase(),
                            bool makePdf = false
                              );


    bool isPdf() const;
    void setIsPdf(bool isPdf);

    static void renderOnPrinter(QPrinter *prnt, QSqlDatabase m_db, QString profile = QString());
    static QString makeXml(QSqlDatabase m_db, QString profile = QString());
private:
    QSqlDatabase db;
    QPrinter *printer;
    QString _xml;
    QString m_ocNo;
    bool m_isPdf;
protected:
    QDomDocument _doc;
};

#endif // CHEQUERENDERER_H
