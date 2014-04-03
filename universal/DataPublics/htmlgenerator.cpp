#include "htmlgenerator.h"

HtmlGenerator::HtmlGenerator(QObject *parent) :
	QObject(parent)
{
}

QString HtmlGenerator::showReportHtml(QString reportID, QSqlDatabase db)
{
	QSqlQuery qu = db.exec("SELECT * FROM scheduled_reports WHERE ReportID = '" + reportID + "'");
	qu.first();
	QString sql = qu.record().value("ReportSQL").toString();
	QString s_title = qu.record().value("ReportTitle").toString();

	QStringList sumColumns = qu.record().value("SumColumns").toString().split(",");
	QStringList hiddenColumns = qu.record().value("HiddenColumns").toString().split(",");

	sumColumns.removeLast();
	hiddenColumns.removeLast();

	bool hideFirstColumn = false;

	qu = db.exec(sql);
	//qDebug() << sql;
	QString html ="";
	//Add Heading
	html += "<h1>" + s_title + "</h1>";
	//Start Table
	html += "<table width=100% Border=1 CellSpacing=0 CellPadding=0>";
	//Add Header
	html += "<tr bgcolor=\"lightgray\">";

	int start = 0;
	if (hideFirstColumn)
		start = 1;

	start = 0;

	int total = qu.record().count() - hiddenColumns.count();
	total = total  + 1;

	for (int i = start; i < total; i++) {
		if (!hiddenColumns.contains( qu.record().fieldName(i)))
			html += "<td><b>" + qu.record().fieldName(i) + "</b></td>";
	}


	html += "</tr>";
	//Add Body
	int cnt = 0;
	while (qu.next()) {
		cnt = cnt + 1;
		//        if (cnt == 0) {
		//            if (qu.record().count() > 4) {
		//                printer->setOrientation(QPrinter::Landscape);
		//            }
		//        }
		html += "<tr>";
		for (int i = start; i < total; i++) {
			if (!hiddenColumns.contains( qu.record().fieldName(i))) {
				QSqlRecord rec = qu.record();
				QString txt = rec.value(i).toString();

				if (sumColumns.contains(qu.record().fieldName(i))) {
					//txt = QLocale(QLocale::English).toString(txt.toDouble());
					html += "<td>" + txt + "</td>";
				} else {
					html += "<td>" + txt + "</td>";
				}
			}
		}
		html += "</tr>";
	}
	//Add Sum row
	html += "<tr bgcolor=\"lightgray\">";

	for (int i = start; i < total; i++) {
		QString sumText = "";
		if (sumColumns.contains(qu.record().fieldName(i))) {
			double sum = 0;
			QSqlQuery sumQuery = qu;
			sumQuery.seek(-1);
			while (sumQuery.next()) {
				QString thisColText = qu.record().value(qu.record().fieldName(i)).toString();
				//qDebug() << sum << thisColText << sum + thisColText.toDouble();
				sum = sum + thisColText.toDouble();
			}
			//sumText =  QLocale(QLocale::English).toString(sum);
			sumText = QString::number(sum);
		}
		html += "<td><b>" + sumText + "</b></td>";
	}
	//Close table
	html += "</table>";
	html += "<br/>";
	html += "<br/>";
	html += "<br/>";
	//Add Footer

	html += "Report Generated On " + QDate::currentDate().toString("dd-MMM-yyyy") + " at " + QTime::currentTime().toString("hh:mm:ss");

	html.replace("{UserDate}", QDate::currentDate().toString("dd MMM yyyy"));

	return html;

}

QString HtmlGenerator::getReportHTMLFromQuery(QString query, QSqlDatabase db, QString ReportTitle)
{
	QSqlQuery qu;
	QString sql = query;
	QString s_title = ReportTitle;

	QStringList sumColumns = lst_sumColumns;
	QStringList hiddenColumns = lst_hiddenColumns;

	//sumColumns.removeLast();
	//hiddenColumns.removeLast();

	bool hideFirstColumn = false;

	qu = db.exec(sql);
	//qDebug() << sql;
	QString html ="";
	//Add Heading
	html += "<h1>" + s_title + "</h1>";
	//Start Table
	html += "<table width=100% Border=1 CellSpacing=0 CellPadding=0>";
	//Add Header
	html += "<tr bgcolor=\"lightgray\">";

	int start = 0;
	if (hideFirstColumn)
		start = 1;

	start = 0;

	int total = qu.record().count() - hiddenColumns.count();
	total = total  + 1;

	for (int i = start; i < total; i++) {
		if (!hiddenColumns.contains( qu.record().fieldName(i)))
			html += "<td><b>" + qu.record().fieldName(i) + "</b></td>";
	}


	html += "</tr>";
	//Add Body
	int cnt = 0;
	while (qu.next()) {
		cnt = cnt + 1;
		//        if (cnt == 0) {
		//            if (qu.record().count() > 4) {
		//                printer->setOrientation(QPrinter::Landscape);
		//            }
		//        }
		html += "<tr>";
		for (int i = start; i < total; i++) {
			if (!hiddenColumns.contains( qu.record().fieldName(i))) {
				QSqlRecord rec = qu.record();
				QString txt = rec.value(i).toString();

				if (sumColumns.contains(qu.record().fieldName(i))) {
					//txt = QLocale(QLocale::English).toString(txt.toDouble());
					html += "<td>" + txt + "</td>";
				} else {
					html += "<td>" + txt + "</td>";
				}
			}
		}
		html += "</tr>";
	}
	//Add Sum row
	html += "<tr bgcolor=\"lightgray\">";

	for (int i = start; i < total; i++) {
		QString sumText = "";
		if (sumColumns.contains(qu.record().fieldName(i))) {
			double sum = 0;
			QSqlQuery sumQuery = qu;
			sumQuery.seek(-1);
			while (sumQuery.next()) {
				QString thisColText = qu.record().value(qu.record().fieldName(i)).toString();
				//qDebug() << sum << thisColText << sum + thisColText.toDouble();
				sum = sum + thisColText.toDouble();
			}
			//sumText =  QLocale(QLocale::English).toString(sum);
			sumText = QString::number(sum);
		}
		html += "<td><b>" + sumText + "</b></td>";
	}
	//Close table
	html += "</table>";
	html += "<br/>";
	html += "<br/>";
	html += "<br/>";
	//Add Footer

	html += "Report Generated On " + QDate::currentDate().toString("dd-MMM-yyyy") + " at " + QTime::currentTime().toString("hh:mm:ss");

	html.replace("{UserDate}", QDate::currentDate().toString("dd MMM yyyy"));

	return html;

}

void HtmlGenerator::AddSumColumn(QString colName)
{
	lst_sumColumns.append(colName);
}

void HtmlGenerator::AddHiddenColumn(QString colName)
{
	lst_hiddenColumns.append(colName);
}
