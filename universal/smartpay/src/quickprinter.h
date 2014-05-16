#ifndef QUICKPRINTER_H
#define QUICKPRINTER_H

#include <QObject>
#include <QtSql>
#include <QPrinter>
#include <QWidget>
#include <QtXml>

class QuickPrinter : public QObject
{
	Q_OBJECT
public:
	explicit QuickPrinter(QObject *parent = 0,
			      QString reportName = QString(),
			      QString where = QString(),
			      QSqlDatabase database = QSqlDatabase(),
			      bool createPdf = false
			      );
	bool isPdf() const;
	void setIsPdf(bool isPdf);
private:
	QSqlDatabase db;
	QPrinter *printer;
	QString _xml;
	QString m_where;
	QString m_reportName;
	bool m_isPdf;
private slots:
	void paintRequested(QPrinter *p);
protected:
	QDomDocument _doc;

};

#endif // QUICKPRINTER_H
