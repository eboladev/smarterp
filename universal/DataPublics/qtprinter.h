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
	explicit QtPrinter(QObject *parent);

	explicit QtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString where = QString(),
			   QString report = QString(), bool pdf = false);

	explicit QtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString where = QString(),
			   QString report = QString(), QString autoPdf = "No");

	explicit QtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
			   QString reportXml = QString(), bool pdf = false);

	void QtPdfPrinter(QSqlDatabase database, QString where, QString report,
			  QString fileName = QString(""));
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
	QString pdfFileName;
	bool silentPdf;
protected:
	QDomDocument _doc;
};

#endif // QTPRINTER_H
