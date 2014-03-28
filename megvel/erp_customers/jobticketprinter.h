#ifndef JOBTICKETPRINTER_H
#define JOBTICKETPRINTER_H

#include <QObject>
#include <QtSql>
#include <QPrinter>
#include <QWidget>
#include <QtXml>
class JobTicketPrinter : public QObject
{
    Q_OBJECT
public:
    explicit JobTicketPrinter(QWidget *parent = 0,
                              QString ocNo = QString(),
                              QSqlDatabase database = QSqlDatabase()
                              );


    bool isPdf() const;
    void setIsPdf(bool isPdf);
private:
    QSqlDatabase db;
    QPrinter *printer;
    QString _xml;
    QString m_ocNo;
    bool m_isPdf;

private slots:
    void paintRequested(QPrinter *p);
protected:
    QDomDocument _doc;
};

#endif // JOBTICKETPRINTER_H
