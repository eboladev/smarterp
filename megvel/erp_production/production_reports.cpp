#include "production_reports.h"
#include "ui_production_reports.h"
#include "htmlgenerator.h"
production_reports::production_reports(QWidget *parent, QSqlDatabase d) :
	QMainWindow(parent),
	ui(new Ui::production_reports)
{
	ui->setupUi(this);
	db = d;
	ui->dtpEndDate->setDate(QDate::currentDate());
	ui->dtpStartDate->setDate(QDate::currentDate().addDays(-7));
}

production_reports::~production_reports()
{
	delete ui;
}

void production_reports::on_cmdShow_clicked()
{
	if (ui->dtpStartDate->date() > ui->dtpEndDate->date()) {
		QDate edate = ui->dtpEndDate->date();
		ui->dtpEndDate->setDate(ui->dtpStartDate->date());
		ui->dtpStartDate->setDate(edate);
	}
	QString html = "<html>";
	html += "<h2>Corrugator Reel Usage (" + ui->dtpStartDate->date().toString("dd-MMM-yyyy")
			+ " - " +  ui->dtpStartDate->date().toString("dd-MMM-yyyy") + ") </h2>";

	double totalUsed, totalDry, totalWet;
	totalUsed = 0;
	totalDry = 0;
	totalWet = 0;

	//    for (int i = 0; i < ui->dtpStartDate->date().daysTo(ui->dtpEndDate->date()); i++) {
	//        QDate date = ui->dtpStartDate->date().addDays(i);
	//        double dayUsed, dayDry, dayWet;

	//        dayUsed = 0;
	//        dayDry  = 0;
	//        dayWet = 0;

	//        totalUsed += dayUsed;
	//        totalDry += dayDry;
	//        totalWet += dayWet;

	//        QString dayUseQuery = "SELECT "
	//                " paper_master.Date"
	//                ", paper_reels.ReelNo"
	//                ", paper_reels.Supplier"
	//                ", paper_reels.Size"
	//                ", paper_reels.GSM"
	//                ", paper_reels.FullBit"
	//                ", paper_reels.Section"
	//                ", paper_reels.Issue"
	//                ", paper_reels.Used"
	//                ", paper_reels.Balance"
	//            " FROM "
	//                "cartons.paper_reels"
	//                " INNER JOIN cartons.paper_master "
	//                "    ON (paper_reels.MasterID = paper_master.EntryID)"
	//                "    "
	//                " WHERE paper_reels.Deleted = 'No'    AND paper_master.Date = '" + date.toString("yyyy-MM-dd") + "'";



	//    }


	QString query = "SELECT"
			" paper_master.Date"
			", paper_reels.ReelNo"
			", paper_reels.Supplier"
			", paper_reels.Size"
			", paper_reels.GSM"
			", paper_reels.FullBit"
			", paper_reels.Section"
			", paper_reels.Issue"
			", paper_reels.Used"
			", paper_reels.Balance"
			" FROM "
			"cartons.paper_reels"
			" INNER JOIN cartons.paper_master "
			"    ON (paper_reels.MasterID = paper_master.EntryID)"
			"    "
			" WHERE paper_reels.Deleted = 'No'    AND paper_master.Date BETWEEN '" + ui->dtpStartDate->date().toString("yyyy-MM-dd") + "' AND '" + ui->dtpEndDate->date().toString("yyyy-MM-dd") + "'";

	HtmlGenerator *gen = new HtmlGenerator(this);
	gen->AddSumColumn("Used");
	QString ht2 = gen->getReportHTMLFromQuery(query, db, "Reel Usage");

	html += ht2;




	html += "</html>";

	ui->txtResult->setHtml(html);
}

void production_reports::on_cmdShow_2_clicked()
{
	HtmlGenerator *gen = new HtmlGenerator(this);
	QString html =    gen->getReportHTMLFromQuery("SELECT * FROM corrugator_excel WHERE `C. Date` BETWEEN '" +
						      ui->dtpStartDate_2->date().toString("yyyy-MM-dd") + "' AND '"
						      + ui->dtpEndDate_2->date().toString("yyyy-MM-dd") + "'", db, "Corrugator Data Entry");
	ui->txtCorrugatorBrowser->setHtml(html);
}
