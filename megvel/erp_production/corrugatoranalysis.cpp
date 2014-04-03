#include "corrugatoranalysis.h"
#include "ui_corrugatoranalysis.h"

CorrugatorAnalysis::CorrugatorAnalysis(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::CorrugatorAnalysis)
{
	ui->setupUi(this);
	db = database;
	ui->dtpEndDate->setDate(QDate::currentDate());
	ui->dtpStartDate->setDate(QDate::currentDate().addDays(-1));
}

CorrugatorAnalysis::~CorrugatorAnalysis()
{
	delete ui;
}

void CorrugatorAnalysis::on_cmdView_clicked()
{
	QString html = "";

	for (int i = 0; i < ui->dtpStartDate->date().daysTo(ui->dtpEndDate->date()); i++) {
		QDate dt = ui->dtpStartDate->date().addDays(i);
		html += "<h1>Analysis for " + dt.toString("dd MMM yyyy") + "</h1>";
		QSqlQuery qu = db.exec("SELECT * FROM newreport WHERE `ScheduleDate` = '" + dt.toString("yyyy-MM-dd") + "'");
		while (qu.next()) {
			html += "<br/><br/><br/><table border=0>";
			html += "<tr><td><b>OC No:</b></td><td>" + qu.record().value("TicketNo").toString() + "</td></tr>";
			html += "<tr><td><b>Client:</b></td><td>" + qu.record().value("Client").toString() + "</td></tr>";
			html += "<tr><td><b>Product:</b></td><td>" + qu.record().value("Product").toString() + "</td></tr></table>";

			html += "<table width=100% cellspacing=0 cellpadding=0 border=1>";
			html += "<tr><td>";

			html += "<table width=100% cellspacing=0 cellpadding=0 border=0>";
			html += "<tr>";
			html += "<td colspan=8 align=center><b>Planned</b></td>";
			html += "</tr>";
			html += "<tr>";
			html += "<td><b>P/Spec</b></td>";
			html += "<td><b>W</b></td>";
			html += "<td><b>Tr</b></td>";
			html += "<td><b>T.W.</b></td>";
			html += "<td><b>Approx</b></td>";
			html += "<td><b>Total</b></td>";
			html += "<td><b>O/Q</b></td>";
			html += "<td><b>Target</b></td>";
			html += "</tr>";

			html += "</table>";

			html += "</td><td>";
			html += "Actual data will appear here";
			html += "</tr>";
			html += "</table>";
		}
	}

	ui->txtAnalysis->setHtml(html);
}
