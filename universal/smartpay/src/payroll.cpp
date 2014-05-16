#include "payroll.h"
#include "ui_payroll.h"
#include "publics.h"
#include <QTextDocument>
#include "../OpenRPT/renderer/renderobjects.h"
#include "../OpenRPT/renderer/openreports.h"
#include "../OpenRPT/renderer/orprerender.h"
#include "../OpenRPT/renderer/orprintrender.h"
#include "parameterproperties.h"
#include "data.h"
#include "parsexmlutils.h"
#include "paramlistedit.h"
#include "../OpenRPT/renderer/previewdialog.h"
#include "../OpenRPT/common/builtinSqlFunctions.h"
#include "xlsxdocument.h"
#include "quickprinter.h"
Payroll::Payroll(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Payroll)
{
	ui->setupUi(this);
	db = database;/*
    ui->widget->db = db;
    ui->widget_2->db = db;*/
	reloadMonths();

	ui->grpPayrollProgress->setVisible(false);
}

Payroll::~Payroll()
{
	delete ui;
}

void Payroll::reloadMonths()
{
	Publics::loadDbToComboBox(db, "SELECT * FROM vw_monthyear ORDER BY MonthID DESC", "Month", ui->comboBox);
}

void Payroll::loadPayroll()
{
	model = new QSqlQueryModel(this);
	fModel = new QSortFilterProxyModel(model);
	ui->lstPayroll->setQuery("SELECT * FROM vw_payroll2 WHERE MonthID = '" + monthID + "'", db, "Payroll For " + ui->comboBox->currentText(), true);
	ui->lstPayroll->setColumnHidden(0, true);
	emit recalculated();

	ui->trvBankLists->setQuery("SELECT `Roll No`, `Name`, `Bank`, `Branch`, `Account No`, `AmountDue`  FROM vw_payroll2 WHERE MonthID = '" + monthID + "' Order BY `Bank`, `Roll No`", db, "Payroll For " + ui->comboBox->currentText(), true);
	DataPublics::loadQueryToComboBox("SELECT DISTINCT(`Year`) AS 'Yr' FROM months ORDER BY Year", "Yr", db, ui->cboP1AYears);
	DataPublics::loadQueryToComboBox("SELECT DISTINCT(`Year`) AS 'Yr' FROM months ORDER BY Year", "Yr", db, ui->cboP1DYears);
	DataPublics::loadQueryToComboBox("SELECT DISTINCT(`Year`) AS 'Yr' FROM months ORDER BY Year", "Yr", db, ui->cboP9AYears);

	nssfPreview();
	nhifPreview();
}


QString Payroll::getReportXML(QString reportName, QString stringToReplace, QString replaceMent)
{
	QSqlQuery qu = db.exec("SELECT * FROM report WHERE report_name = '"  + reportName + "'");
	if (!qu.lastError().isValid()) {
		qu.last();
		QString xml = qu.record().value("report_source").toString();
		xml.replace(stringToReplace, replaceMent);
		////qDebug() << xml;
		return xml;
	}
	return "";
}

QString Payroll::getNumericalMonthNYearNSSF()
{
	QString in = ui->comboBox->currentText();
	QString year = in.right(4);
	QString mn = in.left(in.size()-5);

	QString no = "01";

	if (mn == "January")
		no = "01";
	if (mn == "February")
		no = "02";
	if (mn == "March")
		no = "03";
	if (mn == "April")
		no = "04";
	if (mn == "May")
		no = "05";
	if (mn == "June")
		no = "06";
	if (mn == "July")
		no = "07";
	if (mn == "August")
		no = "08";
	if (mn == "September")
		no = "09";
	if (mn == "October")
		no = "10";
	if (mn == "November")
		no = "11";
	if (mn == "December")
		no = "12";

	return no + year;
}

QString Payroll::getNumericalMonthNYearNHIF()
{
	QString in = ui->comboBox->currentText();
	QString year = in.right(4);
	QString mn = in.left(in.size()-5);

	QString no = "01";

	if (mn == "January")
		no = "01";
	if (mn == "February")
		no = "02";
	if (mn == "March")
		no = "03";
	if (mn == "April")
		no = "04";
	if (mn == "May")
		no = "05";
	if (mn == "June")
		no = "06";
	if (mn == "July")
		no = "07";
	if (mn == "August")
		no = "08";
	if (mn == "September")
		no = "09";
	if (mn == "October")
		no = "10";
	if (mn == "November")
		no = "11";
	if (mn == "December")
		no = "12";

	return year + "-" + no;
}

void Payroll::on_comboBox_currentIndexChanged(const QString &arg1)
{
	monthID = Publics::getDbValue(db, "SELECT * FROM vw_monthyear WHERE Month = '" + arg1 + "'", "MonthID");
	loadPayroll();
}

#include "payrollcalculator.h"
#include "threadedpayrollcalculator.h"
void Payroll::on_Recalculate_clicked()
{
	QString isClosed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
	if (isClosed == "No") {
		//        PayrollCalculator *p = new PayrollCalculator(this, db, monthID);
		//        if (p->exec() == QDialog::Accepted) {
		//            loadPayroll();
		//        }
		QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames");
		if (!qu.lastError().isValid()) {
			ui->prgPayrollProgress->setMaximum(qu.size());
			ui->prgPayrollProgress->setMinimum(0);
			ui->prgPayrollProgress->setValue(0);
			ThreadedPayrollCalculator *th = new ThreadedPayrollCalculator(this, db, monthID);
			connect (th, SIGNAL(progress(int)), SLOT(calculatorProgress(int)));
			connect (th, SIGNAL(finished()), SLOT(calculatorFinished()));
			connect (th, SIGNAL(terminated()), SLOT(calculatorFinished()));
			connect (th, SIGNAL(currentEmployee(QString)), SLOT(calculatorEmployee(QString)));
			ui->grpPayrollProgress->setVisible(true);
			ui->cmdClear->setEnabled(false);
			ui->Recalculate->setEnabled(false);
			ui->comboBox->setEnabled(false);
			th->start();
		} else {
			ui->grpPayrollProgress->setVisible(false);
			ui->cmdClear->setEnabled(true);
			ui->Recalculate->setEnabled(true);
			ui->comboBox->setEnabled(true);
		}
	} else {
		DataPublics::showWarning("This month has been closed. The payroll cannot be recalculated.");
	}
}

void Payroll::on_cmdClear_clicked()
{
	QString isClosed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
	if (isClosed == "No") {
		db.exec("DELETE FROM payroll WHERE MonthID = '" + monthID + "'");
		loadPayroll();
	} else {
		DataPublics::showWarning("This month has been closed. The payroll cannot be recalculated.");
	}
}

void Payroll::calculatorProgress(int p)
{
	ui->prgPayrollProgress->setValue(p);
}

void Payroll::calculatorFinished()
{
	ui->grpPayrollProgress->setVisible(false);
	ui->cmdClear->setEnabled(true);
	ui->Recalculate->setEnabled(true);
	ui->comboBox->setEnabled(true);
	loadPayroll();
}

void Payroll::calculatorEmployee(QString e)
{
	ui->lblPayrollProgressData->setText(e);
}



void Payroll::on_cmdShowP10A_clicked()
{
	QSqlQuery p10AQu = db.exec("SELECT EmployeeNo, `PINNo`, UPPER(`EmployeeName`) as 'Name', "
				   " SUM(`GrossPay`) AS 'Gross', SUM(`Paye`) AS 'Tax' FROM payroll WHERE `Year`  = '" + ui->cboP1AYears->currentText() + "' "
				   " GROUP BY `EmployeeID`"
				   " ORDER BY `EmployeeID`");
	db.exec("DELETE FROM `P10A`");
	while (p10AQu.next()) {
		QSqlRecord rec = p10AQu.record();
		QString insQu = QString(" INSERT INTO `P10A` ("
					"`EmployeePIN`, `EmployeeName`, `TotalPaid`,`TotalTax`,`Year`) "
					" VALUES ('%1','%2','%3','%4','%5')"
					).arg(rec.value("PINNo").toString()
					      , rec.value("Name").toString().trimmed()
					      , rec.value("Gross").toString()
					      , rec.value("Tax").toString()
					      , ui->cboP1AYears->currentText());

		db.exec(insQu);
		if (db.lastError().isValid()) {
			qDebug() << db.lastError().text();
		}
	}
	qDebug() << "Showing P10A report FOR " << ui->cboP1AYears->currentText();
	QuickPrinter(this, "P10A", ui->cboP1AYears->currentText(), db, false);
}

void Payroll::on_cmdShowP10D_clicked()
{
	QString quarterName = ui->cboP10DQuarters->currentText().left(2);
	QString quarterEnding = "";
	QString year = ui->cboP1DYears->currentText();

	QString monthWhere = "";

	if (quarterName == "Q1") {
		quarterEnding = "MARCH " + year;
		monthWhere = " AND ("
				"LEFT(MONTHNAME, 3) = 'Jan' "
				"OR LEFT(MONTHNAME, 3) = 'Feb' "
				"OR LEFT(MONTHNAME, 3) = 'Mar' "
				")";
	}
	if (quarterName == "Q2") {
		quarterEnding = "JUNE " + year;
		monthWhere = " AND ("
				"LEFT(MONTHNAME, 3) = 'Apr' "
				"OR LEFT(MONTHNAME, 3) = 'May' "
				"OR LEFT(MONTHNAME, 3) = 'Jun' "
				")";
	}
	if (quarterName == "Q3") {
		quarterEnding = "SEPTEMBER " + year;
		monthWhere = " AND ("
				"LEFT(MONTHNAME, 3) = 'Jul' "
				"OR LEFT(MONTHNAME, 3) = 'Aug' "
				"OR LEFT(MONTHNAME, 3) = 'Sep' "
				")";
	}
	if (quarterName == "Q4") {
		quarterEnding = "DECEMBER " + year;
		monthWhere = " AND ("
				"LEFT(MONTHNAME, 3) = 'Oct' "
				"OR LEFT(MONTHNAME, 3) = 'Nov' "
				"OR LEFT(MONTHNAME, 3) = 'Dec' "
				")";
	}
	QSqlQuery p10AQu = db.exec("SELECT EmployeeNo, `PINNo`, UPPER(`EmployeeName`) as 'Name', "
				   " SUM(`GrossPay`) AS 'Gross', SUM(`Paye`) AS 'Tax' FROM payroll WHERE `Year`  = '" + year + "' " + monthWhere +
				   " GROUP BY `EmployeeID`"
				   " ORDER BY `EmployeeID`");
	db.exec("DELETE FROM `P10D`");
	while (p10AQu.next()) {
		QSqlRecord rec = p10AQu.record();
		QString insQu = QString(" INSERT INTO `P10D` ("
					"`EmployeePIN`, `EmployeeName`, "
					"`Quarter`, `QuarterEnding`, "
					"`TotalPaid`,`TotalTax`,`Year`) "
					" VALUES ('%1','%2','%3','%4','%5', '%6', '%7')"
					).arg(rec.value("PINNo").toString()
					      , rec.value("Name").toString().trimmed()
					      , quarterName, quarterEnding
					      , rec.value("Gross").toString()
					      , rec.value("Tax").toString(), year
					      );


		db.exec(insQu);
		if (db.lastError().isValid()) {
			qDebug() << db.lastError().text();
		}
	}

	QuickPrinter(this, "P10D", " WHERE Year = '"
				   + year + "' AND Quarter = '" + quarterName + "'", db, false);
}

void Payroll::on_cmdShowP9A_clicked()
{
	QString year = ui->cboP9AYears->currentText();
	db.exec("DELETE FROM p9");
	QSqlQuery p9AQu = db.exec("SELECT EmployeeNo, EmployeeID, `PINNo`, UPPER(`EmployeeName`) as 'Name'"
				  " FROM payroll WHERE `Year`  = '" + year + "'"
				  " GROUP BY `EmployeeID`"
				  " ORDER BY `EmployeeID`");
	while (p9AQu.next()) {
		QString empID, empNo, empName, empPin;
		QSqlRecord rec = p9AQu.record();
		empID = rec.value("EmployeeID").toString();
		empNo = rec.value("EmployeeNo").toString();
		empName = rec.value("Name").toString().trimmed();
		QString fName, lName;
		lName = empName;

		if (empName.contains(" ")) {
			fName = empName.split(" ").at(0);
			lName = empName.right(empName.length() - fName.length()).trimmed();
		}

		empPin = rec.value("PINNo").toString();
		db.exec(tr("INSERT INTO `p9` (EmployeeID, EmployeeNo, OtherNames, EmployeePIN, Year, FirstName)"
			   "VALUES ('%1', '%2', '%3', '%4', '%5', '%6')"
			   ).arg(empID, empNo, lName, empPin, year, fName));

		if (db.lastError().isValid()) {
			qDebug() << db.lastError().text();
		}
	}
	db.exec("UPDATE p9 SET LastModified = NOW()");

	QuickPrinter(this, "P9A","  WHERE Year = '" + year + "'", db, false);
}

void Payroll::on_cmdExportNSSF_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save NSSF File", QDir::homePath(), "Excel Files (*.xlsx)");
	if (fileName.length() > 0) {
		if (!fileName.endsWith(".xlsx"))
			fileName.append(".xlsx");


		QXlsx::Document xlsx;
		//Start with company info
		xlsx.write(1, 1, "Employer No:");
		xlsx.write(1, 3, "01078895");

		xlsx.write(2, 1, "Employer Name:");
		xlsx.write(2, 3, "MEGVEL CARTONS LIMITED");

		xlsx.write(3, 1, "Month Of Contribution:");
		xlsx.write(3, 3, getNumericalMonthNYearNSSF());



		//skip the 4th row
		//
		//The 5th row has the column headers
		xlsx.write(5, 1, "PAYROLL NO");
		xlsx.write(5, 2, "FIRST NAME");
		xlsx.write(5, 3, "NSSF NO");
		xlsx.write(5, 4, "STD");
		xlsx.write(5, 5, "VOL");
		xlsx.write(5, 6, "TOTAL");
		xlsx.write(5, 7, "ID NO");

		//Starting at row no. 6, fill in the data details.
		int row = 6;
		QSqlQuery nssf_qu = db.exec("SELECT * FROM payroll WHERE MonthID = '" + monthID + "'");
		double total = 0;
		while (nssf_qu.next()) {
			QString payNo = nssf_qu.record().value("EmployeeNo").toString();
			QString Name = nssf_qu.record().value("EmployeeName").toString().trimmed();
			QString NSSF_No = nssf_qu.record().value("NSSFNo").toString();
			double NSSF_AMT = nssf_qu.record().value("NSSF").toDouble();
			QString ID_NO = nssf_qu.record().value("IDNo").toString();



			xlsx.write(row, 1, payNo);
			xlsx.write(row, 2, Name.toUpper());
			xlsx.write(row, 3, NSSF_No);
			xlsx.write(row, 4, NSSF_AMT * 2);
			xlsx.write(row, 5, 0);
			xlsx.write(row, 6, NSSF_AMT * 2);
			xlsx.write(row, 7, ID_NO);

			total += NSSF_AMT * 2;
			row ++;
		}

		//On the row below tha last entry, fill in the total
		xlsx.write(row, 4, total);
		xlsx.write(row, 6, total);

		//Save the excel file
		if (xlsx.saveAs(fileName)) {
			DataPublics::showInformation("NSSF File saved at: <br/>" + fileName);
		} else {
			DataPublics::showWarning("NSSF File Save Error:<br/>");
		}
	}
}

void Payroll::nssfPreview()
{
	QString html = "<html>";

	html += "<table border=0>";

	html += "<tr>";
	html += "<td><b>Employer No:</b></td><td>01078895</td>";
	html += "</tr>";

	html += "<tr>";
	html += "<td><b>Employer Name:</b></td><td>MEGVEL CARTONS LTD</td>";
	html += "</tr>";

	html += "<tr>";
	html += "<td><b>Month Of Contribution:</b></td><td>" + getNumericalMonthNYearNSSF() + "</td>";
	html += "</tr>";

	html += "</table>";

	html += "<br/>";

	html += "<table border=1 cellspacing=1 cellpadding=1>";

	html += "<tr>";
	html += "<td><b>Payroll No.</b></td>";
	html += "<td><b>First Name</b></td>";
	html += "<td><b>NSSF No</b></td>";
	html += "<td><b>STD</b></td>";
	html += "<td><b>VOL</b></td>";
	html += "<td><b>Total</b></td>";
	html += "<td><b>ID No.</b></td>";
	html += "</tr>";

	QSqlQuery nssf_qu = db.exec("SELECT * FROM payroll WHERE MonthID = '" + monthID + "'");
	double total = 0;
	while (nssf_qu.next()) {
		QString payNo = nssf_qu.record().value("EmployeeNo").toString();
		QString Name = nssf_qu.record().value("EmployeeName").toString().trimmed();
		QString NSSF_No = nssf_qu.record().value("NSSFNo").toString();
		double NSSF_AMT = nssf_qu.record().value("NSSF").toDouble();
		QString ID_NO = nssf_qu.record().value("IDNo").toString();

		html += "<tr>";

		html += "<td>" + payNo + "</td>";
		html += "<td>" + Name + "</td>";
		html += "<td>" + NSSF_No + "</td>";
		html += "<td>" + QString::number(NSSF_AMT * 2) + "</td>";
		html += "<td>0.00</td>";
		html += "<td>" + QString::number(NSSF_AMT * 2) + "</td>";
		html += "<td>" + ID_NO + "</td>";

		html += "</tr>";

		total += NSSF_AMT * 2;
	}
	html += "<tr>";
	html += "<td></td><td></td><td></td>";
	//std
	html += "<td><b>" + QString::number(total) + "</b></td>";

	html += "<td></td>";
	//total
	html += "<td><b>" + QString::number(total) + "</b></td>";

	html += "<td></td>";
	html += "</tr>";
	html += "</table>";

	html += "</html>";
	ui->txtNSSFView->setHtml(html);
}

void Payroll::nhifPreview()
{
	QString html = "<html>";

	html += "<table border=0>";

	html += "<tr>";
	html += "<td><b>Employer No:</b></td><td>60506</td>";
	html += "</tr>";

	html += "<tr>";
	html += "<td><b>Employer Name:</b></td><td>MEGVEL CARTONS LTD</td>";
	html += "</tr>";

	html += "<tr>";
	html += "<td><b>Month Of Contribution:</b></td><td>" + getNumericalMonthNYearNHIF() + "</td>";
	html += "</tr>";

	html += "</table>";

	html += "<br/>";

	html += "<table border=1 cellspacing=1 cellpadding=1>";

	html += "<tr>";
	html += "<td><b>Payroll No.</b></td>";
	html += "<td><b>Last Name</b></td>";
	html += "<td><b>First Name</b></td>";
	html += "<td><b>ID No.</b></td>";
	html += "<td><b>NHIF No</b></td>";
	html += "<td><b>Amount</b></td>";
	html += "</tr>";

	QSqlQuery nhif_qu = db.exec("SELECT * FROM payroll WHERE MonthID = '" + monthID + "'");
	double total = 0;
	while (nhif_qu.next()) {
		QString payNo = nhif_qu.record().value("EmployeeNo").toString();
		QString Name = nhif_qu.record().value("EmployeeName").toString().trimmed();
		QString NHIF_No = nhif_qu.record().value("NHIFNo").toString();
		double NHIF_AMT = nhif_qu.record().value("NHIF").toDouble();
		QString ID_NO = nhif_qu.record().value("IDNo").toString();

		QString firstName;
		QString lastName;
		QStringList splitName = Name.split(" ");
		lastName = splitName.at(splitName.count() - 1);

		int last = splitName.count() - 1;

		for ( int i  = 0; i < last; i++) {
			firstName += splitName.at(i) + " ";
		}

		html += "<tr>";

		html += "<td>" + payNo + "</td>";
		html += "<td>" + lastName.trimmed() + "</td>";		//last name
		html += "<td>" + firstName.trimmed() + "</td>";		//first name
		html += "<td>" + ID_NO + "</td>";
		html += "<td>" + NHIF_No + "</td>";
		html += "<td>" + QString::number(NHIF_AMT) + "</td>";

		html += "</tr>";

		total += NHIF_AMT;
	}
	html += "<tr>";
	html += "<td></td><td></td><td></td><td></td><td></td>";
	html += "<td><b>" + QString::number(total) + "</b></td>";
	html += "</tr>";
	html += "</table>";

	html += "</html>";
	ui->txtNHIFView->setHtml(html);
}

void Payroll::on_cmdExportNHIF_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save NHIF File", QDir::homePath(), "Excel Files (*.xlsx)");
	if (fileName.length() > 0) {
		if (!fileName.endsWith(".xlsx"))
			fileName.append(".xlsx");


		QXlsx::Document xlsx;
		//Start with the company information
		xlsx.write(1, 1, "Employer No:");
		xlsx.write(1, 3, "60506");

		xlsx.write(2, 1, "Employer Name:");
		xlsx.write(2, 3, "MEGVEL CARTONS LIMITED");

		xlsx.write(3, 1, "Month Of Contribution:");
		xlsx.write(3, 3, getNumericalMonthNYearNHIF());

		//skip the 4th row
		//
		//The 5th row has the column headers
		xlsx.write(5, 1, "PAYROLL NO");
		xlsx.write(5, 2, "LAST NAME");
		xlsx.write(5, 3, "FIRST NAME");
		xlsx.write(5, 4, "ID NO");
		xlsx.write(5, 5, "NHIF NO");
		xlsx.write(5, 6, "AMOUNT");

		//Starting at row no. 6, fill in the data details.
		int row = 6;
		QSqlQuery nhif_qu = db.exec("SELECT * FROM payroll WHERE MonthID = '" + monthID + "'");
		double total = 0;
		while (nhif_qu.next()) {
			QString payNo = nhif_qu.record().value("EmployeeNo").toString();
			QString Name = nhif_qu.record().value("EmployeeName").toString().trimmed();
			QString NHIF_No = nhif_qu.record().value("NHIFNo").toString();
			double NHIF_AMT = nhif_qu.record().value("NHIF").toDouble();
			QString ID_NO = nhif_qu.record().value("IDNo").toString();

			QString firstName;
			QString lastName;
			QStringList splitName = Name.split(" ");
			lastName = splitName.at(splitName.count() - 1).toUpper();

			int last = splitName.count() - 1;

			for ( int i  = 0; i < last; i++) {
				firstName += splitName.at(i) + " ";
			}

			firstName = firstName.toUpper();

			xlsx.write(row, 1, payNo);
			xlsx.write(row, 2, lastName);
			xlsx.write(row, 3, firstName);
			xlsx.write(row, 4, ID_NO);
			xlsx.write(row, 5, NHIF_No);
			xlsx.write(row, 6, NHIF_AMT);

			total += NHIF_AMT;
			row ++;
		}

		//On the row below tha last entry, fill in the total
		xlsx.write(row, 6, total);

		//Save the excel file
		if (xlsx.saveAs(fileName)) {
			DataPublics::showInformation("NHIF File saved at: <br/>" + fileName);
		} else {
			DataPublics::showWarning("NHIF File Save Error:<br/>");
		}
	}
}
