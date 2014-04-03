#include "calculateattendancedialog.h"
#include "ui_calculateattendancedialog.h"
#include <QThread>
CalculateAttendanceDialog::CalculateAttendanceDialog(QWidget *parent,
						     QStringList entriesToCalculate
						     , QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::CalculateAttendanceDialog)
{
	ui->setupUi(this);
	m_db = database;
	setEntries(entriesToCalculate);


}

CalculateAttendanceDialog::~CalculateAttendanceDialog()
{
	delete ui;
}
QStringList CalculateAttendanceDialog::entries() const
{
	return m_entries;
}

void CalculateAttendanceDialog::setEntries(const QStringList &entries)
{
	m_entries = entries;
	ui->prgProgress->setMinimum(1);
	ui->prgProgress->setMaximum(m_entries.count());
	ui->prgProgress->setValue(1);
}
QSqlDatabase CalculateAttendanceDialog::db() const
{
	return m_db;
}

void CalculateAttendanceDialog::setDb(const QSqlDatabase &db)
{
	m_db = db;
}



AttendanceCalculator::AttendanceCalculator(QObject *parent)
	: QObject(parent)
{
	stop = false;
}

void AttendanceCalculator::setVars(QSqlDatabase database, QStringList lst)
{
	QSqlDatabase newDb = QSqlDatabase::addDatabase("QMYSQL", "att_calculator_thread_db" + database.databaseName());
	newDb.setHostName(database.hostName());
	newDb.setUserName(database.userName());
	newDb.setPassword(database.password());
	newDb.setDatabaseName(database.databaseName());
	newDb.open();
	db = newDb;
	entries = lst;
}

void AttendanceCalculator::startProcessing()
{
	for (int i = 0; i < entries.count(); i++) {
		emit progress(i);
		if (stop) {
			emit finished();
			return;
		} else {
			//db.exec("CALL calculate_attendance('" + entries.at(i) + "')");
			QString attID = entries.at(i);
			QString shiftID, employeeID;
			QDate dateIn, dateOut;
			QTime timeIn, timeOut, shiftIn, shiftOut;
			QDateTime fullTimeIn, fullTimeOut;
			QString note, comments;

			QString shiftName, hasOt, empName;
			double hoursWorked, minutesWorked, secondsWorked;
			double s_otStart, s_otRate, s_lunchMinutes, e_workedHours, e_otHours, e_doubleOtHours, e_absentHours;

			double earlyMinutes = 0;
			double lateMinutes = 0;


			QSqlQuery attQu1 = db.exec("SELECT EmployeeID, ShiftID, DateIn, TimeIn, DateOut, TimeOut, Note FROM attendance_2 WHERE EntryID = '"  + attID + "' LIMIT 0, 1");
			attQu1.first();
			employeeID = attQu1.record().value("EmployeeID").toString();
			shiftID = attQu1.record().value("ShiftID").toString();
			dateIn = attQu1.record().value("DateIn").toDate();
			timeIn = attQu1.record().value("TimeIn").toTime();
			dateOut = attQu1.record().value("DateOut").toDate();
			timeOut = attQu1.record().value("TimeOut").toTime();
			note = attQu1.record().value("Note").toString();



			QSqlQuery otQu = db.exec("SELECT HasOvertime, FirstName, OtherNames FROM employees_hr WHERE EmployeeID = '" + employeeID + "'");
			otQu.first();
			hasOt = otQu.record().value("HasOvertime").toString();
			empName = otQu.record().value("OtherNames").toString() + ", " + otQu.record().value("FirstName").toString();



			QSqlQuery shiftQu = db.exec("SELECT ShiftName, StartTime, EndTime, OvertimeStart, OvertimeRate, LunchMinutes FROM shifts WHERE ShiftID = '"  +  shiftID +"'");
			shiftQu.first();
			shiftName = shiftQu.record().value("ShiftName").toString();
			shiftIn = shiftQu.record().value("StartTime").toTime();
			shiftOut = shiftQu.record().value("EndTime").toTime();
			s_otStart = shiftQu.record().value("OvertimeStart").toDouble();
			s_otRate = shiftQu.record().value("OvertimeRate").toDouble();
			s_lunchMinutes = shiftQu.record().value("LunchMinutes").toDouble();

			if (timeOut == QTime(0,0,0) && timeIn == QTime(0,0,0)) {
				timeOut = shiftIn;
				timeIn = shiftIn;
			}

			emit progressData(empName + " " + dateIn.toString() + " " + shiftName);

			if (shiftIn >= timeIn) {
				//I am Early, or I am on time
				earlyMinutes = timeIn.secsTo(shiftIn) / 60;
				lateMinutes = 0;
				timeIn = shiftIn;
			} else {
				//I am Late
				lateMinutes = shiftIn.secsTo(timeIn) / 60;
				if (shiftIn.secsTo(timeIn) < (60 * 11)) {
					//I am late by ten minutes or less
					//Reprieve
					earlyMinutes = 0;
					timeIn = shiftIn;
				}  else {
					//I am late by more than ten minutes
					//No reprieve
					earlyMinutes = 0;
					timeIn = timeIn.addSecs(-600);
				}
			}

			comments = "--";
			fullTimeIn = QDateTime(dateIn, timeIn);
			fullTimeOut = QDateTime(dateOut, timeOut);

			QDateTime shiftStart = QDateTime(dateIn, shiftIn);
			QDateTime shiftEnd = QDateTime(dateOut, shiftOut);
			double shiftHours = shiftStart.secsTo(shiftEnd) / 60 / 60;

			secondsWorked = fullTimeIn.secsTo(fullTimeOut);
			minutesWorked = secondsWorked / 60;
			hoursWorked = minutesWorked / 60;

			e_workedHours = 0;
			e_otHours = 0;
			e_doubleOtHours = 0;
			e_absentHours = 0;

			e_workedHours = (minutesWorked - s_lunchMinutes) / 60;

			if (e_workedHours < 0)
				e_workedHours = 0;

			if (s_otRate == 1.5)
				e_otHours = e_workedHours - s_otStart;

			if (s_otRate == 2)
				e_doubleOtHours = e_workedHours - s_otStart;

			if (e_otHours < 0)
				e_otHours = 0;

			if (e_doubleOtHours < 0)
				e_doubleOtHours = 0;


			//for saturday shifts, if one leaves before 1 PM, no lunch minutes deducted.
			if (s_otStart == 5) {
				if (e_workedHours < s_otStart) {
					e_workedHours = (minutesWorked / 60);
					comments = "Sat";
				}
			}

			if (minutesWorked < 330) {
				e_workedHours = (minutesWorked / 60);
				comments = "No Lunch";
			}

			if (e_workedHours < s_otStart) {
				if (note.toLower() == "leave" ||
				    note.toLower() == "sick" ||
				    note.toLower() == "off") {
					e_absentHours = 0;
				} else {
					e_absentHours = s_otStart - e_workedHours;
				}
			}

			if (s_otRate == 1.5) {
				e_otHours = e_workedHours - s_otStart;
			}

			if (s_otRate == 2) {
				e_doubleOtHours = e_workedHours - s_otStart;
			}

			if (e_workedHours < 0)
				e_workedHours = 0;

			if (e_otHours < 0)
				e_otHours = 0;

			if (e_doubleOtHours < 0)
				e_doubleOtHours = 0;

			if (s_otStart == 0)
				e_absentHours = 0;

			if (hasOt == "No") {
				e_otHours = 0;
				e_doubleOtHours = 0;
				e_workedHours = shiftHours;
				e_absentHours = 0;
				comments = "No OT";
			}

			if (note.trimmed().toLower() == "absent") {
				if (e_workedHours == 0) {
					e_absentHours = shiftHours;
					comments = "Absent";
				}
			}

			if (note.trimmed().toLower() == "half") {

				qDebug() << note << e_workedHours << e_absentHours;
				if (e_absentHours > 0) {
					comments = "Half";
					e_absentHours = e_absentHours / 2;
				} else {

				}
			}

			if (note.trimmed().toLower() == "off") {
				e_absentHours = 0;
				e_workedHours = shiftHours;
				qDebug() << "Off found";
				comments = "Off";
			}


			db.exec(tr("UPDATE attendance_2 SET "
				   "HoursWorked = '%1', "
				   "OvertimeHours = '%2', "
				   "DoubleOvertimeHours = '%3', "
				   "AbsentHours = '%4', "
				   "`Comment` = '%5'"
				   "WHERE EntryID = '%6'")
				.arg(QString::number(e_workedHours),
				     QString::number(e_otHours),
				     QString::number(e_doubleOtHours),
				     QString::number(e_absentHours),
				     comments,
				     attID)
				);
			db.exec(tr("UPDATE attendance_2 SET "
				   "EarlyMinutes = '%1', "
				   "LateMinutes = '%2' "
				   "WHERE EntryID = '%3'")
				.arg(QString::number(earlyMinutes),
				     QString::number(lateMinutes),
				     attID)
				);
		}
	}
	emit finished();
	return;
}

void AttendanceCalculator::cancelAll()
{
	stop = true;
}

void CalculateAttendanceDialog::on_cmdRecalculate_clicked()
{
	if (entries().count() < 1) {
		this->accept();
	}
	QThread *thread = new QThread;
	AttendanceCalculator *worker =
			new AttendanceCalculator(0);
	worker->setVars(m_db, entries());

	connect (worker, SIGNAL(progress(int)),
		 ui->prgProgress, SLOT(setValue(int)));
	connect (worker, SIGNAL(progressData(QString)),
		 ui->lblStatus, SLOT(setText(QString)));

	connect (worker, SIGNAL(finished()), SLOT(accept()));
	connect (thread, SIGNAL(started()), worker, SLOT(startProcessing()));
	connect (worker, SIGNAL(finished()), thread, SLOT(quit()));
	connect (worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
	connect (thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	connect (worker, SIGNAL(finished()), SIGNAL(allDone()));

	connect (ui->cmdCancel, SIGNAL(clicked()), thread, SLOT(terminate()));

	worker->moveToThread(thread);
	thread->start();
}
