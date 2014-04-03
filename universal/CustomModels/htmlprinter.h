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

class HtmlPrinter : public QObject
{
	Q_OBJECT
public:
	explicit HtmlPrinter(QObject *parent = 0, QSqlDatabase database = QSqlDatabase(), QString sqlQuery = QString(),
			     QString reportTitle = QString());

signals:

public slots:
	void printRequested(QPrinter *printer);
private:
	QSqlDatabase db;
	QPrinter *printer;
	QString sql;
	QString title;

	QSqlQuery qu;
	QStringList hiddenColumns;
};

#endif // HTMLPRINTER_H
