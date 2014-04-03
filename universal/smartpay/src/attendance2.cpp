#include "attendance2.h"
#include "ui_attendance2.h"
#include "datapublics.h"
Attendance2::Attendance2(QWidget *parent, QSqlDatabase d) :
	QMainWindow(parent),
	ui(new Ui::Attendance2)
{
	ui->setupUi(this);
	db = d;

	DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex  ORDER BY MonthID DESC", "Month", db, ui->cboMonths);
	DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex  ORDER BY MonthID DESC", "Month", db, ui->cboEmpMonth);
	DataPublics::loadQueryToComboBox("SELECT * FROM vw_employeenames_ex", "Name", db, ui->cboEmpName);

	ui->dtpProcessed->setDate(QDate::currentDate().addDays(-1));

	db.exec("UPDATE `biometric_attendance` SET `Reason` = 'Clock-In Missing' WHERE DELETED = 'No' AND `Status` = 'Pending' AND `InOut` = 'O'");
	db.exec("UPDATE biometric_attendance SET `Reason` = 'Clock-Out Missing' WHERE DELETED = 'No' AND `Status` = 'Pending' AND `InOut` = 'I'");
	reloadAttendance();
	ui->treeView->setVisible(false);

	connect (ui->cboEmpName, SIGNAL(currentIndexChanged(int)), SLOT(generateEmployeeMonthlyAttendanceReport()));
	connect (ui->cboEmpMonth, SIGNAL(currentIndexChanged(int)), SLOT(generateEmployeeMonthlyAttendanceReport()));

	ui->frameBiometricProcessing->setVisible(false);

	dbTimer = new QTimer(this);
	connect (dbTimer, SIGNAL(timeout()), SLOT(on_dbTimer()));
	dbTimer->start(2000);

	//timer = new QTimer(this);
	//connect (timer, SIGNAL(timeout()), SLOT(on_cmdProcessUnprocessed_clicked()));
	//timer->start(60000);

	//ui->cmdProcessUnprocessed->setVisible(false);

	DataPublics::loadQueryToComboBox("SELECT Name FROM vw_employeenames_all", "Name", db, ui->cboAttendanceEmployee);
}

Attendance2::~Attendance2()
{
	delete ui;
}

void Attendance2::reloadProcessedandMain()
{
	reloadAttendance(true, false, true);
}

void Attendance2::reloadAttendance(bool mainAttendance, bool rawAttendance, bool processedAttendance)
{
	// ui->treeView->setQuery("SELECT * FROM vw_attendance_2", db, "Employee Attendance", true);
	// ui->treeView->setColumnHidden(0, true);

	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
	if (monthID.length() > 0) {
		isClosed = true;
		QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
		if (closed == "No")
			isClosed = false;

		QString startDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "StartDate").toString();
		QString endDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "EndDate").toString();

		if (mainAttendance) {
			ui->lstAttendance->invisibleRootItem()->takeChildren();
			QString s_query = "SELECT * FROM vw_attendance WHERE DateIn BETWEEN '" + startDate + "' AND '" + endDate + "'";
			if (!ui->chkAttendanceAllEmployees->isChecked()) {
				s_query.append(" AND `NAME` = '" + ui->cboAttendanceEmployee->currentText() + "'");
			}
			QSqlQuery qu = db.exec(s_query);
			while (qu.next()) {
				QSqlRecord rec  = qu.record();
				QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstAttendance);
				it->setText(99, rec.value("EntryID").toString());
				it->setText(0, rec.value("#").toString());
				it->setText(1, rec.value("Name").toString());
				it->setText(2, rec.value("ShiftName").toString());
				it->setText(3, rec.value("DateIn").toString());
				it->setText(4, rec.value("TimeIn").toString());
				it->setText(5, rec.value("DateOut").toString());
				it->setText(6, rec.value("TimeOut").toString());
				it->setText(7, rec.value("HoursWorked").toString());
				it->setText(8, rec.value("OvertimeHours").toString());
				it->setText(9, rec.value("DoubleOvertimeHours").toString());
				it->setText(10, rec.value("AbsentHours").toString());
				it->setText(11, rec.value("Comment").toString());

				if (rec.value("Type").toString() == "Manual") {
					for (int r = 0; r < 12; r++) {
						it->setBackgroundColor(r, QColor(170, 255, 127));
					}
				}

				it->setCheckState(0, Qt::Unchecked);
			}
		}

		if (rawAttendance) {
			ui->trvRawAttendanceData->invisibleRootItem()->takeChildren();
			ui->trvErrorsOnThisDate->invisibleRootItem()->takeChildren();
			QSqlQuery rawQu = db.exec("SELECT * FROM biometric_attendance WHERE Deleted = 'No' AND Status = 'Pending' AND `Date` BETWEEN '" + startDate + "' AND '" + endDate + "' ORDER BY `Date`, `Time`");
			while (rawQu.next()) {
				QSqlRecord rec = rawQu.record();
				QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvRawAttendanceData);
				it->setText(0, rec.value("EntryID").toString());


				QString empNo = rec.value("StaffNo").toString();
				if (empNo.length() < 2)
					empNo.prepend("00");

				if (empNo.length() < 3)
					empNo.prepend("0");



				it->setText(1, empNo);

				it->setText(2, DataPublics::getDbValue("SELECT Name FROM vw_employeenames_all WHERE `#` = '" +
								       empNo + "'"
								       , db, "Name").toString());
				it->setText(3, rec.value("Date").toString());
				it->setText(4, rec.value("Time").toString());
				it->setText(5, rec.value("InOut").toString());
				it->setText(6, rec.value("Posted").toString());
				it->setText(7, rec.value("Reason").toString());


				if (rec.value("Date").toString() == ui->dtpProcessed->date().toString("yyyy-MM-dd")
				    && rec.value("Posted").toString() == "No"
				    ) {
					QTreeWidgetItem *it2 = new QTreeWidgetItem(ui->trvErrorsOnThisDate);
					it2->setText(1, empNo);

					it2->setText(2, DataPublics::getDbValue("SELECT Name FROM vw_employeenames_all WHERE `#` = '" +
										empNo + "'"
										, db, "Name").toString());
					it2->setText(3, rec.value("Date").toString());
					it2->setText(4, rec.value("Time").toString());
					it2->setText(5, rec.value("InOut").toString());
					it2->setText(6, rec.value("Posted").toString());
					it2->setText(7, rec.value("Reason").toString());
				}

				it->setCheckState(1, Qt::Unchecked);

				if (rec.value("Posted").toString() == "No") {
					for (int c = 0; c < 8; c++) {
						it->setBackgroundColor(c, QColor(255, 101, 137));
					}
				}
			}
			ui->trvRawAttendanceData->setColumnHidden(0, true);
		}

		if (processedAttendance) {

			QSqlQuery empQu = db.exec("SELECT EmployeeNo, CONCAT(`FirstName`, ' ', `OtherNames`) as 'Name' FROM employees_hr WHERE IsActive = 'Yes' ORDER BY EmployeeNo");
			QStringList empLst;
			QStringList empNames;
			while (empQu.next()) {
				empLst << empQu.record().value("EmployeeNo").toString();
				empNames << empQu.record().value("Name").toString();
			}

			ui->trvProcessedBiometricData->invisibleRootItem()->takeChildren();
			ui->trvNotClockedOnThisDate->invisibleRootItem()->takeChildren();
			QSqlQuery processedQu = db.exec("SELECT * FROM attendance_3 WHERE DateIn = '" + ui->dtpProcessed->date().toString("yyyy-MM-dd") + "' AND DELETED = 'No' AND `DateIn` BETWEEN '" + startDate + "' AND '" + endDate + "'  ORDER BY `DateIn`, `TimeIn`");
			while (processedQu.next()) {
				QSqlRecord rec = processedQu.record();
				QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvProcessedBiometricData);
				QString entryID = rec.value("EntryID").toString();
				QString empID = rec.value("EmployeeID").toString();
				QString empNO = DataPublics::getDbValue("SELECT `#` FROM vw_employeenames_all WHERE `employeeID` = '" +
									empID + "'", db, "#").toString();
				QString empName = DataPublics::getDbValue("SELECT `Name` FROM vw_employeenames_all WHERE `employeeID` = '" +
									  empID + "'", db, "Name").toString();
				it->setText(0, entryID);
				it->setText(1, empNO);

				int eID = empLst.indexOf(empNO);
				if (eID > -1) {
					empLst.removeAt(eID);
					empNames.removeAt(eID);
				}

				int cnt = DataPublics::getDbValue("SELECT Count(EmployeeID) as 'cnt' FROM attendance_2 WHERE EmployeeID = '"
								  + empID + "' AND DateIn = '" + rec.value("DateIn").toDate().toString("dd-MMM-yyyy")
								  + "'", db, "cnt").toInt();
				if (cnt > 0) {
					int eID = empLst.indexOf(empNO);
					if (eID > -1) {
						empLst.removeAt(eID);
						empNames.removeAt(eID);
					}
				}

				it->setText(2, empName);
				it->setText(3, rec.value("DateIn").toDate().toString("dd-MMM-yyyy"));
				it->setText(4, rec.value("TimeIn").toString());
				it->setText(5, rec.value("DateOut").toDate().toString("dd-MMM-yyyy"));
				it->setText(6, rec.value("TimeOut").toString());
				it->setCheckState(1, Qt::Unchecked);

				if (rec.value("Assigned") == "Yes") {
					it->setIcon(1, QIcon(":images/go-previous-24.png"));
				} else {
					it->setIcon(1, QIcon(":images/Icon_136.ico"));
				}

			}
			ui->trvProcessedBiometricData->setColumnHidden(0, true);
			for (int e = 0; e < empLst.count(); e++) {

				QTreeWidgetItem *newIt = new QTreeWidgetItem(ui->trvNotClockedOnThisDate);
				newIt->setText(0, empLst.at(e));
				newIt->setText(1, empNames.at(e));
			}
			ui->trvNotClockedOnThisDate->setColumnHidden(0, true);
		}


	}
}

#include "attendance2_newentry.h"
void Attendance2::on_actionNew_Attendance_Entry_triggered()
{
	Attendance2_NewEntry *att = new Attendance2_NewEntry(this, db);
	if (att->exec() == QDialog::Accepted) {
		reloadAttendance();
	}
}

#include "attendance2_editor.h"
void Attendance2::on_treeView_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString id = ui->treeView->getCurrentID();
	if (id.length() > 0) {
		attendance2_editor *ed = new attendance2_editor(this, db);
		ed->setAttendance(id);
		if (ed->exec() == QDialog::Accepted) {
			reloadAttendance();
		}
	}
}

void Attendance2::on_cmdDelete_clicked()
{
	if (!isClosed) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete the selected item(s)?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			for (int i = 0; i < ui->lstAttendance->invisibleRootItem()->childCount(); i++) {
				QTreeWidgetItem *it = ui->lstAttendance->invisibleRootItem()->child(i);
				if (it->checkState(0) == Qt::Checked) {
					QString id = it->text(99);
					db.exec("DELETE FROM attendance_2 WHERE EntryID = '" + id + "'");
					reloadAttendance(true, false, false);
				}
			}
		}
	}
	else {
		DataPublics::showWarning("This month has already been closed.");
	}
}


#include "allocateabsentism.h"
void Attendance2::on_actionLeaves_Absent_triggered()
{
	AllocateAbsentism *all = new AllocateAbsentism(this, db);
	all->exec();
}

void Attendance2::on_lstAttendance_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	//QString id = ui->treeView->getCurrentID();
	QString id = ui->lstAttendance->currentItem()->text(99);
	//qDebug() << id;
	if (id.length() > 0) {
		if (!isClosed) {
			attendance2_editor *ed = new attendance2_editor(this, db);
			ed->setAttendance(id);
			if (ed->exec() == QDialog::Accepted) {
				reloadAttendance();
			}
		}
		else {
			DataPublics::showWarning("This month has already been closed.");
		}
	}
}

void Attendance2::on_cmdChangeShift_clicked()
{
	if (!isClosed) {
		QInputDialog *dg = new QInputDialog(this);
		QString newShift = dg->getItem(this, "New Shift", "Select the new shift",
					       DataPublics::getDbListItems("SELECT * FROM shifts", "ShiftName", db));
		QString newShiftID = DataPublics::getDbValue("SELECT * FROM shifts WHERE ShiftName = '" + newShift + "'", db, "ShiftID").toString();
		if (newShiftID.length() > 0) {
			if (newShiftID == "0") {
				return;
			} else {
				for (int i = 0; i < ui->lstAttendance->invisibleRootItem()->childCount(); i++) {
					QTreeWidgetItem *it = ui->lstAttendance->invisibleRootItem()->child(i);
					if (it->checkState(0) == Qt::Checked) {
						db.exec("UPDATE attendance_2 SET ShiftID = '" + newShiftID + "' WHERE EntryID = '" + it->text(99) + "'");
					}
				}
			}
		}
		reloadAttendance();
	} else {
		DataPublics::showWarning("This month has already been closed.");
	}
}

#include "attendance_newdaterange.h"
void Attendance2::on_cmdChangeDate_clicked()
{
	if (!isClosed) {
		Attendance_NewDateRange *newD = new Attendance_NewDateRange(this);
		if (newD->exec() == QDialog::Accepted) {
			for (int i = 0; i < ui->lstAttendance->invisibleRootItem()->childCount(); i++) {
				QTreeWidgetItem *it = ui->lstAttendance->invisibleRootItem()->child(i);
				if (it->checkState(0) == Qt::Checked) {
					db.exec("UPDATE attendance_2 SET DateIn = '" + newD->dateIn.toString("yyyy-MM-dd")
						+ "', DateOut = '" + newD->dateOut.toString("yyyy-MM-dd")
						+ "' WHERE EntryID = '" + it->text(99) + "'");
				}
			}
			reloadAttendance();
		}
	} else {
		DataPublics::showWarning("This month has already been closed.");
	}

}

void Attendance2::on_actionRefresh_triggered()
{
	reloadAttendance();
}

#include "calculateattendancedialog.h"
void Attendance2::on_actionRecalculate_triggered()
{
	if (!isClosed) {
		// db.exec("CALL CalculateAllAtendance()");
		QStringList lst = QStringList();
		for (int i = 0; i < ui->lstAttendance->invisibleRootItem()->childCount(); i++) {
			QTreeWidgetItem *it = ui->lstAttendance->invisibleRootItem()->child(i);
			if (it->checkState(0) == Qt::Checked) {
				// db.exec("CALL calculate_attendance('" + it->text(99) + "')");
				lst << it->text(99);
			}
		}
		CalculateAttendanceDialog *cal = new CalculateAttendanceDialog(this, lst, db);
		connect (cal, SIGNAL(allDone()), SLOT(reloadProcessedandMain()));
		cal->on_cmdRecalculate_clicked();
		if (cal->exec()) {
			// reloadAttendance(true, false, false);
		}
	} else {
		DataPublics::showWarning("This month has already been closed.");
	}
}

void Attendance2::on_cboMonths_currentIndexChanged(const QString &arg1)
{
	Q_UNUSED(arg1);
	reloadAttendance();
}

void Attendance2::generateEmployeeMonthlyAttendanceReport()
{
	QString html = "<html><head><!-- CSS goes in the document HEAD or added to your external stylesheet --> "
			" <style type=\"text/css\"> "
			" table.gridtable { "
			"font-family: verdana,arial,sans-serif; "
			"font-size:11px; "
			"color:#333333; "
			"border-width: 1px; "
			"border-color: #666666; "
			" border-collapse: collapse; "
			" } "
			"table.gridtable th { "
			"border-width: 1px; "
			" padding: 8px; "
			" border-style: solid; "
			" border-color: #666666; "
			" background-color: #dedede; "
			"} "
			" table.gridtable td { "
			" border-width: 1px; "
			"padding: 8px; "
			" border-style: solid; "
			" border-color: #666666; "
			" background-color: #ffffff; "
			" } "
			" </style></head><body>";
	html += "<h2> Attendance Report For " + ui->cboEmpName->currentText() + "</h2>";
	html += "<h3>" + ui->cboEmpMonth->currentText() + "</h3>";

	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboEmpMonth->currentText() + "'", db, "MonthID").toString();
	QString s_monthStartDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "StartDate").toString();
	QString s_monthEndDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "EndDate").toString();

	QDate monthStartDate = QDate::fromString(s_monthStartDate, "yyyy-MM-dd");
	QDate monthEndDate = QDate::fromString(s_monthEndDate, "yyyy-MM-dd");

	QString employeeID = DataPublics::getDbValue("SELECT * FROM vw_employeenames_ex WHERE Name = '" + ui->cboEmpName->currentText() + "'", db, "employeeID").toString();

	html += "<h3>" + monthStartDate.toString("dd MMMM yyyy")+ "-" + monthEndDate.toString("dd MMMM yyyy")+ "</h3>";


	int dayCount = monthStartDate.daysTo(monthEndDate) + 1;

	int weeks = dayCount / 7;
	if ((weeks * 7) < dayCount){
		weeks = weeks+1;
	}

	QStringList  weeksList;
	QString table = "<table class=\"gridtable\">";
	int days = 0;
	for (int i = 0; i < weeks; i++) {
		int weekNum = i  + 1;
		QString weekName = "Week " + QString::number(weekNum);
		weeksList.append(weekName);
		table += "<tr><td><b>" + weekName + "</b></td>";
		for (int d = 0; d < 7; d++) {
			if (days < dayCount) {
				QDate currentDay = monthStartDate.addDays(days);
				QString dateLabel = "<b>" +
						currentDay.toString("ddd") + " " +
						QString::number(currentDay.day()) + "-" +
						currentDay.toString("MMM") + "-" +
						currentDay.toString("yy")
						+ "</b>";
				QString presence = "---";
				QString bgColor = "\"white\"";
				QSqlQuery attQu = db.exec("SELECT * FROM attendance_2 WHERE EmployeeID = '" + employeeID + "' AND DateIn = '" + currentDay.toString("yyyy-MM-dd") + "'");
				if (attQu.size() < 1) {
					presence = "---";
				} else {
					attQu.first();
					QString note = attQu.record().value("Note").toString();
					QString absent = attQu.record().value("AbsentHours").toString();
					QString worked = attQu.record().value("HoursWorked").toString();
					QString ot = attQu.record().value("OvertimeHours").toString();
					QString ot2 = attQu.record().value("DoubleOvertimeHours").toString();
					if (note.trimmed().length() > 0) {
						qDebug() << "Note is " << note.trimmed().toLower() ;
						if (note.trimmed().toLower() == "absent") {
							presence = "Absent: " + absent;
							bgColor = "red";
						}else if (note.trimmed().toLower()== "leave") {
							presence = "Leave";
							bgColor = "pink";
						}else if (note.trimmed().toLower() == "sick") {
							presence = "Sick";
							bgColor = "yellow";
						}else if (note.trimmed().toLower() == "off") {
							presence = "Off";
							bgColor = "lightgreen";
							presence = "<b>Off: Absent hours ignored</b><br/>Worked :" + worked  + "<br/>OT: " + ot + "<br/>OT2: " + ot2 + "<br/>Absent: " + absent;
						}else if (note.trimmed().toLower() == "half") {
							bgColor = "yellow";
							presence = "<b>Half day deducted</b><br/><br/>Absent: " + absent;
						} else {
							presence = "Unknown (" + note + ")<br/>" +
									"Worked :" + worked  + "<br/>OT: " + ot + "<br/>OT2: " + ot2 + "<br/>Absent: " + absent;
							;
							bgColor = "grey";
						}
					} else {


						presence = "Worked :" + worked  + "<br/>OT: " + ot + "<br/>OT2: " + ot2 + "<br/>Absent: " + absent;

						if (absent.toDouble() > 0.1) {
							bgColor = "lightgreen";
						} else {
							bgColor = "green";
						}
					}
				}
				days++;
				table += "<td bgcolor=" + bgColor + ">" + dateLabel;
				table += "<br/>" + presence;
				table += "</td>";
			}
		}
		table += "</tr>";
	}
	table += "</table>";
	html += table;

	QString totHours = DataPublics::getDbValue("SELECT Sum(HoursWorked) as 'tot' FROM attendance_2 WHERE EmployeeID = '" + employeeID + "' AND DateIn BETWEEN '" + monthStartDate.toString("yyyy-MM-dd") + "' AND '" + monthEndDate.toString("yyyy-MM-dd") + "'", db, "tot").toString();
	QString totOtHours = DataPublics::getDbValue("SELECT Sum(OvertimeHours) as 'tot' FROM attendance_2 WHERE EmployeeID = '" + employeeID + "' AND DateIn BETWEEN '" + monthStartDate.toString("yyyy-MM-dd") + "' AND '" + monthEndDate.toString("yyyy-MM-dd") + "'", db, "tot").toString();
	QString totOt2 = DataPublics::getDbValue("SELECT Sum(DoubleOvertimeHours) as 'tot' FROM attendance_2 WHERE EmployeeID = '" + employeeID + "' AND DateIn BETWEEN '" + monthStartDate.toString("yyyy-MM-dd") + "' AND '" + monthEndDate.toString("yyyy-MM-dd") + "'", db, "tot").toString();
	QString totAbsentHours = DataPublics::getDbValue("SELECT Sum(AbsentHours) as 'tot' FROM attendance_2 WHERE EmployeeID = '" + employeeID + "' AND DateIn BETWEEN '" + monthStartDate.toString("yyyy-MM-dd") + "' AND '" + monthEndDate.toString("yyyy-MM-dd") + "'", db, "tot").toString();

	QString hours_summary = "";
	hours_summary += "<b>Total Hours Worked: </b>" + totHours + "<br/>";
	hours_summary += "<b>Total Overtime Hours: </b>" + totOtHours + "<br/>";
	hours_summary += "<b>Total Double Overtime Hours: </b>" + totOt2 + "<br/>";
	hours_summary += "<b>Total Absent Hours: </b>" + totAbsentHours + "<br/>";
	html += hours_summary;

	//    QString midMonthAdv = DataPublics::getDbValue("SELECT Sum(Amount) as 'tot' FROM employee_advances WHERE EmployeeID = '" + employeeID + "' AND AdvanceDate BETWEEN '" + monthStartDate.toString("yyyy-MM-dd") + "' AND '" + monthEndDate.toString("yyyy-MM-dd") + "'", db, "tot").toString();
	//    QString cashAdv = DataPublics::getDbValue("SELECT Sum(Amount) as 'tot' FROM employee_cash_advances WHERE EmployeeID = '" + employeeID + "' AND AdvanceDate BETWEEN '" + monthStartDate.toString("yyyy-MM-dd") + "' AND '" + monthEndDate.toString("yyyy-MM-dd") + "'", db, "tot").toString();

	//    QString payroll_summary = "";
	//    payroll_summary += "<h1>Payroll Summary</h1>";
	//    payroll_summary += "<table>";
	//    payroll_summary += tr("<tr><td><b>Mid Month Advance</b></td><td>%1</td></tr>").arg(midMonthAdv );
	//    payroll_summary += tr("<tr><td><b>Cash Month Advance</b></td><td>%1</td></tr>").arg(cashAdv );
	//    payroll_summary += "</table>";

	//    html += payroll_summary;
	html += "</body></html>";
	ui->txtBrowser1->setHtml(html);
}

void Attendance2::on_cmdReloadRPT1_clicked()
{
	generateEmployeeMonthlyAttendanceReport();
}

#include "importbiometricdata.h"
void Attendance2::on_actionImport_Biometric_Data_triggered()
{
	ImportBiometricData *wiz =  new ImportBiometricData(this);
	wiz->exec();
}

void Attendance2::on_actionAssign_Shifts_triggered()
{

}

#include <QThread>
void Attendance2::on_cmdProcessUnprocessed_clicked()
{
	ui->cmdProcessUnprocessed->setEnabled(false);
	ui->frameBiometricProcessing->setVisible(true);
	QThread *thread = new QThread;
	BiometricProcessor *worker = new
			BiometricProcessor(0);
	worker->setVars(db);
	worker->setEntries(QStringList());

	connect (worker, SIGNAL(progress(int)),
		 this, SLOT(biometricProgress(int)));
	connect (worker, SIGNAL(progress_data(QString)),
		 this, SLOT(biometricProgressData(QString)));

	connect (worker, SIGNAL(total(int)), this, SLOT(biometricTotal(int)));
	connect (worker, SIGNAL(finished()), this, SLOT(processorFinished()));
	connect (worker, SIGNAL(error(QString)), this, SLOT(biometricError(QString)));

	connect(thread, SIGNAL(started()), worker, SLOT(processAllUnprocessed()));
	connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
	connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	worker->moveToThread(thread);
	thread->start();
}

void Attendance2::processorFinished()
{
	ui->cmdProcessUnprocessed->setEnabled(true);
	ui->frameBiometricProcessing->setVisible(false);
	reloadAttendance(false, true, true);
}

void Attendance2::biometricProgress(int val)
{
	ui->prgBiometricData->setValue(val);
}

void Attendance2::biometricTotal(int val)
{
	ui->prgBiometricData->setMinimum(0);
	ui->prgBiometricData->setMaximum(val);
}

void Attendance2::biometricProgressData(QString data)
{
	ui->lblBiometricData->setText(data);
}

void Attendance2::biometricError(QString error)
{
	DataPublics::showWarning(error);
}


BiometricProcessor::BiometricProcessor(QObject *parent = 0)
	: QObject(parent)
{

}

void BiometricProcessor::setVars(QSqlDatabase database)
{
	QSqlDatabase newDb = QSqlDatabase::addDatabase("QMYSQL", "biometricDb" + database.databaseName());
	newDb.setHostName(database.hostName());
	newDb.setUserName(database.userName());
	newDb.setPassword(database.password());
	newDb.setDatabaseName(database.databaseName());
	newDb.open();
	db = newDb;
}

void BiometricProcessor::setEntries(QStringList entries)
{
	lst_entries = entries;
}

void BiometricProcessor::processAllUnprocessed()
{
	int totalEntries = 0;
	int count = 0;
	totalEntries = DataPublics::getDbValue(
				"SELECT COUNT(EntryID) AS cnt FROM biometric_attendance WHERE Reason = 'Not Processed' And `InOut` = 'I'"
				, db, "cnt"
				).toInt();
	emit total(totalEntries);
	QSqlQuery qu = db.exec("SELECT * FROM biometric_attendance WHERE Status = 'Pending' And `InOut` = 'I'");
	if (qu.lastError().isValid()) {
		emit error(qu.lastError().text());
		emit finished();
		return;
	} else {
		while (qu.next()) {
			QString empNo = qu.record().value("StaffNo").toString();
			QString entryID = qu.record().value("EntryID").toString();
			if (empNo.length() < 2)
				empNo.prepend("00");

			if (empNo.length() < 3)
				empNo.prepend("0");

			emit progress_data(empNo);

			QString empID = DataPublics::getDbValue(
						"SELECT * FROM employees_hr WHERE EmployeeNo = '" + empNo + "'"
						, db, "EmployeeID"
						).toString();

			QDate dateIn = qu.record().value("Date").toDate();
			QTime timeIn = qu.record().value("Time").toTime();

			int out_count = 0;

			if (timeIn > QTime(15, 0, 0) ) {
				//This is an evening clock in
				out_count =  DataPublics::getDbValue(
							"SELECT COUNT(EntryID) AS cnt FROM biometric_attendance WHERE  "
							"`InOut` = 'O' AND  "
							"`StaffNo` = '" + qu.record().value("StaffNo").toString() + "' AND "
							"`Date` = DATE_ADD('" + qu.record().value("Date").toString() +"', INTERVAL 1 DAY)"
							, db, "cnt").toInt();
			} else {
				//This is a morning clock in
				out_count =  DataPublics::getDbValue(
							"SELECT COUNT(EntryID) AS cnt FROM biometric_attendance WHERE  "
							"`InOut` = 'O' AND  "
							"`StaffNo` = '" + qu.record().value("StaffNo").toString() + "' AND "
							"DATE = '" + qu.record().value("Date").toString()  +"'"
							, db, "cnt").toInt();
			}


			if (out_count > 0) {
				QSqlQuery outQu;
				if (timeIn > QTime(15, 0, 0) ) {
					//Evening clock in
					outQu = db.exec("SELECT * FROM biometric_attendance WHERE  "
							"`InOut` = 'O' AND  "
							"`StaffNo` = '" + qu.record().value("StaffNo").toString() + "' AND "
							"`Date` = DATE_ADD('" + qu.record().value("Date").toString() +"', INTERVAL 1 DAY)");

				} else {
					//Morning clock in
					outQu = db.exec("SELECT * FROM biometric_attendance WHERE  "
							"`InOut` = 'O' AND  "
							"`StaffNo` = '" + qu.record().value("StaffNo").toString() + "' AND "
							"`Date` = '" + qu.record().value("Date").toString()  +"'");

				}
				if (outQu.lastError().isValid()) {
					emit error(outQu.lastError().text());
				} else {
					outQu.first();
					QDate dateOut = outQu.record().value("Date").toDate();
					QTime timeOut = outQu.record().value("Time").toTime();

					////qDebug() << out_count << empID << empNo << dateIn << timeIn << dateOut << timeOut;

					db.exec("DELETE FROM attendance_3 WHERE EmployeeID = '" + empID + "' AND Date = '" + dateIn.toString("yyyy-MM-dd") + "'");
					QSqlQuery insQu =  db.exec("INSERT INTO attendance_3 (EmployeeID,"
								   "DateIn, TimeIn, DateOut, TimeOut) VALUES ('" +
								   empID + "', '"+
								   dateIn.toString("yyyy-MM-dd") + "', '"+
								   timeIn.toString("HH:mm") + "', '"+
								   dateOut.toString("yyyy-MM-dd") + "', '"+
								   timeOut.toString("HH:mm") + "')");

					if (insQu.lastError().isValid()) {
						emit error(insQu.lastError().text());
					} else {
						db.exec("UPDATE biometric_attendance SET Status='Linked', Posted = 'Yes', Reason = 'Processed Successfully' WHERE EntryID = '" + entryID + "'");
						db.exec("UPDATE biometric_attendance SET Status='Linked', Posted = 'Yes', Reason = 'Processed Successfully' WHERE EntryID = '" + outQu.record().value("EntryID").toString() + "'");
					}
				}
			} else {

			}

			count++;
			emit progress(count);
		}
	}
	db.exec("UPDATE biometric_attendance SET `Reason` = 'Clock-In Missing' WHERE DELETED = 'No' AND `Status` = 'Pending' AND `InOut` = 'O'");
	db.exec("UPDATE biometric_attendance SET `Reason` = 'Clock-Out Missing' WHERE DELETED = 'No' AND `Status` = 'Pending' AND `InOut` = 'I'");

	emit finished();
	return;
}

void BiometricProcessor::processEntries()
{

}

#include "postbiometricattendancewizard.h"
void Attendance2::on_actionImport_Biometric_Attendance_triggered()
{
	PostBiometricAttendanceWizard *postB = new PostBiometricAttendanceWizard(this, db);
	if (postB->exec() == QDialog::Accepted) {
		reloadAttendance();
	}
}

void Attendance2::on_actionRecalculate_All_Entries_triggered()
{
	if (isClosed) {
		DataPublics::showWarning("This month has already been closed.");
	} else {
		// db.exec("CALL CalculateAllAtendance()");
		if (QMessageBox::question(this, "Warning!!!", "This operation may take a long time to complete. \n\nProceed?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
			return;
		}
		QStringList lst = QStringList();
		for (int i = 0; i < ui->lstAttendance->invisibleRootItem()->childCount(); i++) {
			QTreeWidgetItem *it = ui->lstAttendance->invisibleRootItem()->child(i);
			lst << it->text(99);
		}
		CalculateAttendanceDialog *cal = new CalculateAttendanceDialog(this, lst, db);
		if (cal->exec()) {
			reloadAttendance(true, false, false);
		}
	}
}

void Attendance2::on_tabWidget_currentChanged(int index)
{
	if (index == 1) {
		reloadAttendance(false, true, false);
	}
}

void Attendance2::on_cmdChangeRawEntry_clicked()
{
	for (int i = 0; i < ui->trvRawAttendanceData->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->trvRawAttendanceData->invisibleRootItem()->child(i);
		if (it->checkState(1) == Qt::Checked) {
			QString entryID = it->text(0);
			QString inOut = it->text(5);

			if (inOut == "I") {
				inOut = "O";
			} else {
				inOut = "I";
			}

			db.exec("UPDATE biometric_attendance SET `InOut` = '" + inOut + "' WHERE EntryID = '" + entryID + "'");
		}
	}

	reloadAttendance(false, true, false);
}

void Attendance2::on_cmdDeleteRawData_clicked()
{
	if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete all selected entries?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
		return;
	}
	for (int i = 0; i < ui->trvRawAttendanceData->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->trvRawAttendanceData->invisibleRootItem()->child(i);
		if (it->checkState(1) == Qt::Checked) {
			QString entryID = it->text(0);

			db.exec("UPDATE biometric_attendance SET `Deleted` = 'Yes' WHERE EntryID = '" + entryID + "'");
		}
	}

	reloadAttendance(false, true, false);
}

void Attendance2::on_cmdDeleteProcessedData_clicked()
{
	if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete all selected entries?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) {
		return;
	}
	for (int i = 0; i < ui->trvProcessedBiometricData->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->trvProcessedBiometricData->invisibleRootItem()->child(i);
		if (it->checkState(1) == Qt::Checked) {
			QString entryID = it->text(0);
			//qDebug() << "Deleting attendance_3 " << entryID;
			db.exec("UPDATE attendance_3 SET `Deleted` = 'Yes' WHERE EntryID = '" + entryID + "'");
		}
	}

	reloadAttendance(false, false, true);
}

void Attendance2::on_dbTimer()
{
	if (!db.isOpen()) {
		//qDebug() << "Db not open";
		if (db.open()) {
			//qDebug() << "Db open";
			reloadAttendance(true, true, true);
		} else {
			//qDebug() << "Db failed to open " << db.lastError().text();
		}
	}
}

void Attendance2::on_cmdAssignBiometricShift_clicked()
{
	if (!isClosed) {
		QInputDialog *dg = new QInputDialog(this);
		QString newShift = dg->getItem(this, "New Shift", "Select the new shift",
					       DataPublics::getDbListItems("SELECT * FROM shifts", "ShiftName", db));
		QString newShiftID = DataPublics::getDbValue("SELECT * FROM shifts WHERE ShiftName = '" + newShift + "'", db, "ShiftID").toString();
		if (newShiftID.length() > 0) {
			if (newShiftID == "0") {
				return;
			} else {
				QStringList ents;
				for (int i = 0; i < ui->trvProcessedBiometricData->invisibleRootItem()->childCount(); i++) {
					QTreeWidgetItem *it = ui->trvProcessedBiometricData->invisibleRootItem()->child(i);
					if (it->checkState(0) == Qt::Checked) {
						QString att_3_id = it->text(0);

						QSqlQuery sqlQu = db.exec("SELECT * FROM attendance_3 WHERE EntryID = '" + att_3_id  + "'");
						if (!sqlQu.lastError().isValid()) {
							sqlQu.first();
							QString empID = sqlQu.record().value("EmployeeID").toString();
							QString dateIn = sqlQu.record().value("DateIn").toString();
							QString timeIn = sqlQu.record().value("TimeIn").toString();
							QString dateOut = sqlQu.record().value("DateOut").toString();
							QString timeOut = sqlQu.record().value("TimeOut").toString();

							QSqlQuery ins  =
									db.exec(tr("INSERT INTO attendance_2 (EmployeeID, DateIn, TimeIn, DateOut, TimeOut, ShiftID, Type) VALUES "
										   "('%1', '%2', '%3', '%4', '%5', '%6', 'Auto')"
										   ).arg(empID, dateIn, timeIn, dateOut, timeOut, newShiftID)
										);
							QString id = ins.lastInsertId().toString();
							ents << id;

							db.exec("UPDATE attendance_3 SET Assigned = 'Yes' WHERE EntryID = '" + it->text(0) + "'");
						}
					}
				}
				CalculateAttendanceDialog *calc = new CalculateAttendanceDialog(this, ents, db);
				connect (calc, SIGNAL(allDone()), SLOT(reloadProcessedandMain()));
				calc->on_cmdRecalculate_clicked();
			}
		}
		//reloadAttendance(true, true, true);
	} else {
		DataPublics::showWarning("This month has already been closed.");
	}
}

void Attendance2::on_dtpProcessed_dateChanged(const QDate &date)
{
	Q_UNUSED(date);
	reloadAttendance(false, true, true);
}

void Attendance2::on_cboAttendanceEmployee_currentIndexChanged(const QString &arg1)
{
	Q_UNUSED(arg1);
	reloadAttendance(true, false, false);
}

void Attendance2::on_chkAttendanceAllEmployees_toggled(bool checked)
{
	Q_UNUSED(checked);
	reloadAttendance(true, false, false);
}
