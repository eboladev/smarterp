#ifndef HTMLGENERATOR_H
#define HTMLGENERATOR_H

#include <QObject>
#include <QtSql>

class HtmlGenerator : public QObject
{
	Q_OBJECT
public:
	explicit HtmlGenerator(QObject *parent = 0);
	static QString showReportHtml(QString reportID, QSqlDatabase db);
	QString getReportHTMLFromQuery(QString query, QSqlDatabase db, QString ReportTitle);
	void AddSumColumn(QString colName);
	void AddHiddenColumn(QString colName);
private:
	QStringList lst_sumColumns;
	QStringList lst_hiddenColumns;
signals:

public slots:



};

#endif // HTMLGENERATOR_H
