#include "col_ageing.h"
#include "ui_col_ageing.h"

Col_Ageing::Col_Ageing(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Col_Ageing)
{
	ui->setupUi(this);
	db = database;

	reload();
}

Col_Ageing::~Col_Ageing()
{
	delete ui;
}

void Col_Ageing::on_cmdRecalculate_clicked()
{
	db.exec("CALL QB_RecalculateCollectionAgeing()");
	if (db.lastError().isValid()) {
		DataPublics::showWarning(db.lastError().text());
	} else {
		DataPublics::showInformation("Ageing recalculated successfully.");
		reload();
	}
}

void Col_Ageing::reload()
{
	ui->lstAgeing->setQuery("SELECT * FROM qb_ageing", db, "Ageing Summary", true);
	ui->lstAgeing->setColumnHidden(0, true);
	ui->lstAgeing->addColumnToSum("Current");
	ui->lstAgeing->addColumnToSum("30");
	ui->lstAgeing->addColumnToSum("60");
	ui->lstAgeing->addColumnToSum("90");
	ui->lstAgeing->addColumnToSum("120");
	ui->lstAgeing->addColumnToSum("Above120");
	ui->lstAgeing->addColumnToSum("Total");
}

void Col_Ageing::on_lstAgeing_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString ageingID = ui->lstAgeing->getCurrentID();
	if (ageingID.length() > 0) {
		QString customerName = DataPublics::getDbValue("SELECT * FROM qb_ageing WHERE EntryID = '" + ageingID + "'", db, "CustomerName").toString();

		QString html = "";


		html.append("<h1> Ageing Details for " + customerName + "</h1>");

		html.append(getHtmlForRange("Current", QDate::currentDate(), QDate::currentDate(), customerName));

		html.append(getHtmlForRange("1-30 Days", QDate::currentDate().addDays(-30), QDate::currentDate().addDays(-1), customerName));

		html.append(getHtmlForRange("31-60 Days", QDate::currentDate().addDays(-60), QDate::currentDate().addDays(-31), customerName));

		html.append(getHtmlForRange("61-90 Days", QDate::currentDate().addDays(-90), QDate::currentDate().addDays(-161), customerName));

		html.append(getHtmlForRange("91-120 Days", QDate::currentDate().addDays(-120), QDate::currentDate().addDays(-91), customerName));

		html.append(getHtmlForRange("Over 120 Days", QDate::currentDate().addDays(-3000), QDate::currentDate().addDays(-121), customerName));

		ui->txtBrowser->setHtml(html);
	}
}

QString Col_Ageing::getHtmlForRange(QString rangeName, QDate startDate, QDate endDate, QString customerName)
{
	QString ret = "<br/>";
	ret.append("<h3>" + rangeName + "</h3>");
	QString sD = startDate.toString("yyyy-MM-dd");
	QString eD = endDate.toString("yyyy-MM-dd");
	QString qu_ery = "SELECT * FROM qb_invoices WHERE (NewInvoiceDate BETWEEN '" + sD + "' AND '" + eD + "') AND CustomerName  = '" + customerName + "'";
	QSqlQuery invQuery = db.exec(qu_ery);
	if (invQuery.lastError().isValid()) {
		ret.append("<br/>");
		ret.append(invQuery.lastError().text());
	}else {
		if (invQuery.size() < 1) {
			ret.append("No invoices in this range.");
		} else {
			ret.append("<table width=100% cellspacing=0 cellpadding=1> border=1");
			ret.append("<tr bgcolor=\"lightgray\">");
			ret.append("<td><b>Invoice No.</b></td>");
			ret.append("<td><b>Invoice Date</b></td>");
			ret.append("<td><b>Subtotal</b></td>");
			ret.append("<td><b>Tax %</b></td>");
			ret.append("<td><b>Tax Total</b></td>");
			ret.append("<td><b>Invoice Total</b></td>");
			ret.append("<td><b>Applied Amount</b></td>");
			ret.append("<td><b>Balance</b></td>");
			ret.append("</tr>");
			while (invQuery.next()) {
				QSqlRecord rec = invQuery.record();
				ret.append("<tr>");

				ret.append("<td>" + rec.value("InvoiceNo").toString() + "</td>");
				ret.append("<td>" + rec.value("InvoiceDate").toString() + "</td>");
				ret.append("<td>" + rec.value("Subtotal").toString() + "</td>");
				ret.append("<td>" + rec.value("SalesTaxPercentage").toString() + "</td>");
				ret.append("<td>" + rec.value("SalesTaxTotal").toString() + "</td>");
				ret.append("<td>" + rec.value("InvoiceTotal").toString() + "</td>");
				ret.append("<td>" + rec.value("AmountPaid").toString() + "</td>");
				ret.append("<td>" + rec.value("Balance").toString() + "</td>");

				ret.append("</tr>");
			}

			ret.append("</table>");
			ret.append("<br/>");
		}
	}


	ret.append("<br/>");

	return ret;
}
