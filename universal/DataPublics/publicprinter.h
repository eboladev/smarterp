#ifndef PUBLICPRINTER_H
#define PUBLICPRINTER_H

#include <QObject>
#include <QtSql>
#if QT_VERSION >= 0x050000
#include <QtPrintSupport/QPrinter>
#endif
#if QT_VERSION < 0x50000
#include <QPrinter>
#endif

#include <QWidget>
#include <QtXml>


class PublicPrinter : public QObject
{
	Q_OBJECT
public:
	explicit PublicPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString where = QString(),
			       QString report = QString());

signals:

public slots:
	void printRequested(QPrinter *p);
private:
	QSqlDatabase db;
	QPrinter *printer;
	QString reportName;
	QString param;
	QString _xml;
protected:
	QDomDocument _doc;
};

#endif // PUBLICPRINTER_H
