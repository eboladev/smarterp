#include "attendance2_newentry.h"
#include "ui_attendance2_newentry.h"
#include "datapublics.h"
#include "calculateattendancedialog.h"
Attendance2_NewEntry::Attendance2_NewEntry(QWidget *parent, QSqlDatabase d) :
	QWizard(parent),
	ui(new Ui::Attendance2_NewEntry)
{
	ui->setupUi(this);

	//    this->setButtonText(QWizard::CustomButton1, tr("&Previous"));
	//    this->setButtonText(QWizard::CustomButton1, tr("&Next"));
	//    this->setButtonText(QWizard::CustomButton2, tr("&Cancel"));
	//    this->setOption(QWizard::HaveCustomButton1, true);
	//    this->setOption(QWizard::HaveCustomButton2, true);
	//    connect(this, SIGNAL(customButtonClicked(int)),
	//            this, SLOT(customButtonClicked(int)));

	//    QList<QWizard::WizardButton> layout;
	//    layout << QWizard::CustomButton1 << QWizard::CustomButton2;
	//    setButtonLayout(layout);
	saved = false;
	connect (this, SIGNAL(currentIdChanged(int)), SLOT(pageChanged(int)));

	db = d;
	ui->dtpDateIn->setDate(QDate::currentDate());
	ui->dtpDateOut->setDate(QDate::currentDate());

	DataPublics::loadQueryToComboBox("SELECT * FROM shifts", "ShiftName", db, ui->cboShift);
	reloadEmployees();
}

Attendance2_NewEntry::~Attendance2_NewEntry()
{
	delete ui;
}



void Attendance2_NewEntry::reloadEmployees()
{
	ui->trvEmployees->invisibleRootItem()->takeChildren();
	QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames_all ORDER BY `#` ASC");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
	} else {
		while (qu.next()) {
			QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvEmployees);
			it->setText(0, qu.record().value("#").toString());
			it->setText(1, qu.record().value("Name").toString());
			it->setText(99, qu.record().value("employeeID").toString());
			it->setCheckState(0, Qt::Unchecked);
		}
	}
}

void Attendance2_NewEntry::on_cmdReloadEmployees_clicked()
{
	if (QMessageBox::question(this, "Confirm", "Are you sure you want to reload this list? All selections will be lost.", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
		reloadEmployees();
	}
}

void Attendance2_NewEntry::pageChanged(int pageNum)
{
	if (pageNum == 2) {
		for (int i = 0; i < ui->tblTimes->rowCount(); i++)
			ui->tblTimes->removeRow(i);

		for (int i = 0; i < ui->trvEmployees->invisibleRootItem()->childCount(); i++) {
			QTreeWidgetItem *it = ui->trvEmployees->invisibleRootItem()->child(i);
			if (it->checkState(0) == Qt::Checked) {
				QString empID = it->text(99);
				QString empName = it->text(1);
				QString rollNo = it->text(0);

				int r = ui->tblTimes->rowCount();
				ui->tblTimes->insertRow(r);

				QTableWidgetItem *rollCol = new QTableWidgetItem(rollNo, 1);
				QTableWidgetItem *empCol = new QTableWidgetItem(empName, 1);
				QTableWidgetItem *idCol = new QTableWidgetItem(empID, 1);
				QTableWidgetItem *timeIn = new QTableWidgetItem(" ", 1);
				QTableWidgetItem *timeOut = new QTableWidgetItem(" ", 1);
				QTableWidgetItem *commentCol = new QTableWidgetItem(" ", 1);


				rollCol->setText(rollNo);
				empCol->setText(empName);
				idCol->setText(empID);
				timeIn->setText(ui->dtpIntroTimeIn->time().toString("hh:mm"));
				timeOut->setText(ui->dtpIntroTimeOut->time().toString("hh:mm"));

				ui->tblTimes->setItem(r, 0, rollCol);
				ui->tblTimes->setItem(r, 1, empCol);
				ui->tblTimes->setItem(r, 2, timeIn);
				ui->tblTimes->setItem(r, 3, timeOut);
				ui->tblTimes->setItem(r, 4, idCol);
				ui->tblTimes->setItem(r, 5, commentCol);

				ui->tblTimes->setColumnHidden(4, true);

				ui->tblTimes->resizeColumnsToContents();
				ui->tblTimes->resizeRowsToContents();
			}
		}
	} if (pageNum == 3) {
		//Show Confirmation details
		QString html = "<h2>Attendance Data Entry</h2>";
		html += "<br/>";
		html += "<b>Shift:</b> " + ui->cboShift->currentText();
		html += "<br/>";
		html += "<b>Date In:</b> " + ui->dtpDateIn->date().toString("dd MMM yyyy");
		html += "<br/>";
		html += "<b>Date Out:</b> " + ui->dtpDateOut->date().toString("dd MMM yyyy");
		html += "<br/>";

		html += "<br/>";
		html += "<table width=100% border=0>";
		html += "<tr bgcolor=\"lightgray\">";
		html += "<td><b>Roll No.</b></td>";
		html += "<td><b>Name</b></td>";
		html += "<td><b>Time In</b></td>";
		html += "<td><b>Time Out</b></td>";
		html += "<td><b>Comment</b></td>";
		html += "</tr>";

		for (int  r = 0; r < ui->tblTimes->rowCount(); r++) {
			QString rollNo = ui->tblTimes->item(r, 0)->text();
			QString empName = ui->tblTimes->item(r, 1)->text();
			QString timeIn = ui->tblTimes->item(r, 2)->text();
			QString timeOut = ui->tblTimes->item(r, 3)->text();
			QString comment = ui->tblTimes->item(r, 5)->text();

			html += "<tr>";
			html += "<td>" + rollNo + "</td>";
			html += "<td>" + empName + "</td>";
			html += "<td>" + timeIn + "</td>";
			html += "<td>" + timeOut + "</td>";
			html += "<td>" + comment + "</td>";
			html += "</tr>";
		}
		html += "</table>";
		ui->txtReview->setHtml(html);
	} if (pageNum == 4) {
		if (!saved) {
			saved = true;
			on_cmdSave_clicked();
		}
	}
}



void Attendance2_NewEntry::on_cmdExit_clicked()
{
	this->accept();
}

void Attendance2_NewEntry::on_cmdStartOver_clicked()
{
	ui->trvEmployees->invisibleRootItem()->takeChildren();
	ui->dtpDateIn->setDate(QDate::currentDate());
	ui->dtpDateOut->setDate(QDate::currentDate());

	DataPublics::loadQueryToComboBox("SELECT * FROM shifts", "ShiftName", db, ui->cboShift);
	reloadEmployees();
	for (int i = 0; i < ui->tblTimes->rowCount(); i++)
		ui->tblTimes->removeRow(i);
	this->restart();
}

void Attendance2_NewEntry::on_cmdSave_clicked()
{
	QString shiftID = DataPublics::getDbValue("SELECT ShiftID FROM shifts WHERE ShiftName = '" + ui->cboShift->currentText() + "'", db, "ShiftID").toString();

	QString dateIn = ui->dtpDateIn->date().toString("yyyy-MM-dd");
	QString dateOut = ui->dtpDateOut->date().toString("yyyy-MM-dd");
	QString quError = "";
	QStringList calcs;
	for (int  r = 0; r < ui->tblTimes->rowCount(); r++) {
		QString timeIn = ui->tblTimes->item(r, 2)->text();
		QString timeOut = ui->tblTimes->item(r, 3)->text();
		QString empID = ui->tblTimes->item(r, 4)->text();
		QString comment = ui->tblTimes->item(r, 5)->text();

		db.exec("DELETE FROM attendance_2 WHERE EmployeeID = '" + empID + "'"
			" AND DateIn = '" + dateIn + "'");

		QSqlQuery qu = db.exec("INSERT INTO attendance_2 "
				       " (EmployeeID, ShiftID, Note, DateIn, DateOut, TimeIn, TimeOut) "
				       " VALUES ('"
				       + empID + "', '"
				       + shiftID + "', '"
				       + comment + "', '"
				       + dateIn + "', '"
				       + dateOut + "', '"
				       + timeIn + "', '"
				       + timeOut + "')");
		if (qu.lastError().isValid()) {
			quError.append(qu.lastError().text());
		} else {
			//db.exec("CALL calculate_attendance('" + qu.lastInsertId().toString() + "')");
			calcs << qu.lastInsertId().toString();
		}
	}

	if (calcs.count() > 0) {
		QThread *thread = new QThread;
		AttendanceCalculator *worker =
				new AttendanceCalculator(0);
		worker->setVars(db, calcs);

		connect (thread, SIGNAL(started()), worker, SLOT(startProcessing()));
		connect (worker, SIGNAL(finished()), thread, SLOT(quit()));
		connect (worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
		connect (thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

		worker->moveToThread(thread);
		thread->start();
	}


	if (quError.length() > 0) {
		DataPublics::showWarning("An error has occured.\nData not saved");
		//qDebug() << quError;
	}else {
		if (!saved) {
			saved = true;
			this->next();
		}
	}
}
