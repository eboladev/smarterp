#ifndef REPORTPREVIEW_H
#define REPORTPREVIEW_H

#include <QObject>
#include <QtSql>
#include <QPrinter>
#include <QWidget>
#include <QtXml>

class ReportPreview : public QObject
{
	Q_OBJECT
public:
	explicit ReportPreview(QObject *parent = 0
			, QSqlDatabase database = QSqlDatabase()
			, QString reportName = QString()
			, QString where = QString()
			);

signals:

public slots:
	void printRequested(QPrinter *);
private:
	QSqlDatabase db;
	QPrinter *printer;
	QString reportName;
	QString param;
	QString _xml;
protected:
	QDomDocument _doc;

};


#endif // REPORTPREVIEW_H
