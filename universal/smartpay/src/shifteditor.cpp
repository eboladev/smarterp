#include "shifteditor.h"
#include "ui_shifteditor.h"
#include "datapublics.h"
ShiftEditor::ShiftEditor(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::ShiftEditor)
{
	ui->setupUi(this);
	db = database;
}

ShiftEditor::~ShiftEditor()
{
	delete ui;
}

void ShiftEditor::AddNew()
{
	isAdding = true;
}

void ShiftEditor::Edit(QString id)
{
	isAdding = false;
	currentID = id;
	QSqlQuery qu = db.exec("SELECT * FROM shifts WHERE ShiftID = '" + currentID + "'");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		this->reject();
	} else {
		qu.first();
		ui->txtShiftName->setText(qu.record().value("ShiftName").toString());
		ui->txtDescription->setText(qu.record().value("Description").toString());
		//ui->dtpStartTime->setTime(QTime::fromString(qu.record().value("StartTime").toString(), "hh:mm"));
		// ui->dtpEndTime->setTime(QTime::fromString(qu.record().value("EndTime").toString(), "hh:mm"));
		ui->dtpStartTime->setTime(qu.record().value("StartTime").toTime());
		ui->dtpEndTime->setTime(qu.record().value("EndTime").toTime());

		ui->spinOvertimeRate->setValue(qu.record().value("OvertimeRate").toDouble());
		ui->spinOvertimeStart->setValue(qu.record().value("OvertimeStart").toDouble());
		ui->spinLunchMinutes->setValue(qu.record().value("LunchMinutes").toDouble());
	}
}

void ShiftEditor::on_cmdSave_clicked()
{
	QString query = "";
	if (isAdding) {
		query = "INSERT INTO shifts"
				" (ShiftName, Description, StartTime, EndTime, LunchMinutes, OvertimeStart, OvertimeRate) "
				" VALUES ('"
				+ ui->txtShiftName->text() + "', '"
				+ ui->txtDescription->text() + "', '"
				+ ui->dtpStartTime->time().toString("hh:mm") + "', '"
				+ ui->dtpEndTime->time().toString("hh:mm") + "', '"
				+ QString::number(ui->spinLunchMinutes->value()) + "', '"
				+ QString::number(ui->spinOvertimeStart->value()) + "', '"
				+ QString::number(ui->spinOvertimeRate->value()) + "')";
	} else {
		query = "UPDATE shifts SET "
				"ShiftName = '" + ui->txtShiftName->text() + "', "
				"Description = '" + ui->txtDescription->text() + "', "
				"StartTime = '" + ui->dtpStartTime->time().toString("hh:mm") + "', "
				"EndTime = '" + ui->dtpEndTime->time().toString("hh:mm") + "', "
				"LunchMinutes = '" + QString::number(ui->spinLunchMinutes->value()) + "', "
				"OvertimeStart = '" + QString::number(ui->spinOvertimeStart->value()) + "', "
				"OvertimeRate = '" + QString::number(ui->spinOvertimeRate->value()) + "' WHERE ShiftID = '" + currentID + "'";
	}

	QSqlQuery qu = db.exec(query);
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
	} else {
		this->accept();
	}
}
