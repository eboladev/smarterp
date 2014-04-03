#include "ocregister.h"
#include "ui_ocregister.h"
#include "datapublics.h"
#include <QProcess>
#include "jobticketprinter.h"
OcRegister::OcRegister(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::OcRegister)
{
	ui->setupUi(this);

	db = database;

	ui->cboCustomers->setEnabled(false);

	ui->chkIsRange->setChecked(true);
	ui->dtpEndDate->setEnabled(true);

	ui->dtpEndDate->setDate(QDate::currentDate().addDays(0));
	ui->dtpStartDate->setDate(QDate::currentDate().addDays(-30));

	DataPublics::loadQueryToComboBox("SELECT CompanyName FROM customers ORDER By CompanyName ASC", "CompanyName", db, ui->cboCustomers);



	on_cmdShowOcs_clicked();
}

OcRegister::~OcRegister()
{
	delete ui;
}

void OcRegister::setDatabase(QSqlDatabase database)
{
	db = database;
	on_cmdShowOcs_clicked();
}



void OcRegister::on_cmdShowOcs_clicked()
{

	query = "SELECT * FROM report_ocregister WHERE Date = '" + ui->dtpStartDate->date().toString("yyyy-MM-dd") + "'";

	if (ui->chkIsRange->isChecked()) {
		query = "SELECT * FROM report_ocregister WHERE Date BETWEEN '" + ui->dtpStartDate->date().toString("yyyy-MM-dd") + "'"
				" AND '" + ui->dtpEndDate->date().toString("yyyy-MM-dd") + "' ";
	}

	if (ui->chkSpecificCustomer->isChecked()) {
		query = query + " AND Client LIKE '%"  + ui->cboCustomers->currentText()  + "%'";
	}


	ui->lstOcs->setQuery(query, db, "OC Register", false);
	ui->lstOcs->addColumnToSum("Tons");



	//Setup graph
	ui->tonnageHistoryGraph->clearGraphs();
	ui->tonnageHistoryGraph->addGraph();
	ui->tonnageHistoryGraph->xAxis->setLabel("Days");

	QDate lastDate = ui->dtpEndDate->date();
	QDate firstDate = ui->dtpStartDate->date();

	int dayCount = firstDate.daysTo(lastDate);


	QVector<double> dayNums(dayCount);
	QVector<QString> dayLabels(dayCount);

	for (int i = 0; i < dayCount; i++) {
		dayNums.append(i);
		dayLabels.append(firstDate.addDays(i).toString("dd-MM"));
	}

	ui->tonnageHistoryGraph->xAxis->setRange(1, dayCount);
	ui->tonnageHistoryGraph->xAxis->setTickStep(1);
	ui->tonnageHistoryGraph->xAxis->setTickVector(dayNums);
	ui->tonnageHistoryGraph->xAxis->setTickVectorLabels(dayLabels);

	ui->tonnageHistoryGraph->xAxis->setAutoTicks(false);
	ui->tonnageHistoryGraph->xAxis->setAutoTickLabels(false);


	ui->tonnageHistoryGraph->yAxis->setLabel("Tons");
	ui->tonnageHistoryGraph->yAxis->setRange(0, 100);

	ui->tonnageHistoryGraph->graph(0)->setName("OC History");
	//Fetch data from lstOcs model and load it into an array.
	QVector<double> xData(dayCount + 1), yData(dayCount + 1);
	for (int d = 0; d < dayCount; d++) {
		xData[d] = d;
		QDate thisDate = firstDate.addDays(d);
		double dateTotal = 0;
		for (int r = 0; r < ui->lstOcs->myModel->rowCount(); r++) {
			QDate modelDate = ui->lstOcs->myModel->index(r, 3).data().toDate();
			if (modelDate == thisDate)
				dateTotal = dateTotal + ui->lstOcs->myModel->index(r, 5).data().toDouble();
		}
		yData[d] = dateTotal;
	}
	//Load the array to the graph
	ui->tonnageHistoryGraph->graph(0)->setData(xData, yData);
	//Redraw the graph
	ui->tonnageHistoryGraph->replot();
}

void OcRegister::on_lstOcs_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString id= ui->lstOcs->getCurrentID();
	if (id.length() > 0) {
		JobTicketPrinter(this, id, db);
	}
}


#include "qtprinter.h"
void OcRegister::on_cmdPrint_clicked()
{
	QtPrinter(this, db, query, "OcRegister", false);
}


