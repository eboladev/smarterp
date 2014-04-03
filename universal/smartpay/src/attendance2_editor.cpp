#include "attendance2_editor.h"
#include "ui_attendance2_editor.h"

#include "datapublics.h"
attendance2_editor::attendance2_editor(QWidget *parent, QSqlDatabase d) :
	QDialog(parent),
	ui(new Ui::attendance2_editor)
{
	ui->setupUi(this);
	db = d;

	DataPublics::loadQueryToComboBox("SELECT ShiftName FROM shifts", "ShiftName", db, ui->cboShift);
}

attendance2_editor::~attendance2_editor()
{
	delete ui;
}

void attendance2_editor::setAttendance(QString id)
{
	currentID = id;
	QString query = "SELECT "
			" `attendance_2`.EntryID"
			", `employees_hr`.OtherNames"
			", `employees_hr`.EmployeeNo"
			", `attendance_2`.ShiftID"
			", `attendance_2`.DateIn"
			", `attendance_2`.TimeIn"
			", `attendance_2`.DateOut"
			", `attendance_2`.Note"
			", `attendance_2`.TimeOut"
			" FROM "
			"`attendance_2` "
			" INNER JOIN `employees_hr` "
			"ON (`attendance_2`.EmployeeID = `employees_hr`.`employeeID`) WHERE EntryID = '" + currentID + "'";

	//qDebug() << query;

	QSqlQuery qu = db.exec(query);
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
	} else {
		qu.first();

		ui->txtEmployeeName->setText(qu.record().value("OtherNames").toString());
		ui->txtRollNo->setText(qu.record().value("EmployeeNo").toString());
		ui->cboComment->setEditText(qu.record().value("Note").toString());
		ui->dtpDateIn->setDate(qu.record().value("DateIn").toDate());
		ui->dtpDateOut->setDate(qu.record().value("DateOut").toDate());
		ui->dtpTimeIn->setTime(QTime::fromString(qu.record().value("TimeIn").toString(), "hh:mm"));
		ui->dtpTimeOut->setTime(QTime::fromString(qu.record().value("TimeOut").toString(), "hh:mm"));


		QSqlQuery shiftsQu = db.exec("SELECT * FROM shifts WHERE ShiftID = '" + qu.record().value("ShiftID").toString() + "'") ;
		shiftsQu.first();
		for (int s = 0; s < ui->cboShift->count(); s++) {
			////qDebug() << s;
			if (ui->cboShift->itemText(s) == shiftsQu.record().value("ShiftName").toString()) {
				// //qDebug() << "OK";
				ui->cboShift->setCurrentIndex(s);
			}
		}
	}
}

void attendance2_editor::on_cmdSave_clicked()
{
	QString query = "";
	QString shiftID = DataPublics::getDbValue("SELECT * FROM shifts WHERE ShiftName = '" + ui->cboShift->currentText() + "'", db, "ShiftID").toString();
	query += "UPDATE attendance_2 SET ShiftID = '" + shiftID + "' "
			", DateIn = '" + ui->dtpDateIn->date().toString("yyyy-MM-dd") + "' "
			", TimeIn = '" + ui->dtpTimeIn->time().toString("hh:mm")  + "' "
			", DateOut = '" + ui->dtpDateOut->date().toString("yyyy-MM-dd") + "' "
			", TimeOut = '" + ui->dtpTimeOut->time().toString("hh:mm") + "' "
			", Note = '" + ui->cboComment->currentText() + "' "
			" WHERE EntryID = '" + currentID + "'";
	QSqlQuery qu = db.exec(query);
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
	} else {
		db.exec("CALL RecalculateEmpAttendance('" + currentID + "')");
		this->accept();
	}
}
