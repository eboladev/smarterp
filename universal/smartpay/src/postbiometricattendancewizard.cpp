#include "postbiometricattendancewizard.h"
#include "ui_postbiometricattendancewizard.h"
#include "datapublics.h"
#include "calculateattendancedialog.h"
PostBiometricAttendanceWizard::PostBiometricAttendanceWizard(QWidget *parent, QSqlDatabase d) :
    QWizard(parent),
    ui(new Ui::PostBiometricAttendanceWizard)
{
    ui->setupUi(this);
    db = d;
    connect (this, SIGNAL(currentIdChanged(int)), SLOT(pageChanged(int)));

    saved = false;
    ui->dtpDate->setDate(QDate::currentDate());
    DataPublics::loadQueryToComboBox("SELECT * FROM shifts", "ShiftName", db, ui->cboShift);
    reloadEmployees();
}

PostBiometricAttendanceWizard::~PostBiometricAttendanceWizard()
{
    delete ui;
}

void PostBiometricAttendanceWizard::reloadEmployees()
{
    ui->trvAttendance->invisibleRootItem()->takeChildren();
    QSqlQuery processedQu = db.exec("SELECT * FROM attendance_3 WHERE Deleted = 'No' AND `DateIn` = '" + ui->dtpDate->date().toString("yyyy-MM-dd") + "' ORDER BY EmployeeID");
    while (processedQu.next()) {
        QSqlRecord rec = processedQu.record();
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvAttendance);


        QString entryID = rec.value("EntryID").toString();
        QString empID = rec.value("EmployeeID").toString();
        QString empNO = DataPublics::getDbValue("SELECT `#` FROM vw_employeenames_all WHERE `employeeID` = '" +
                                                empID + "'", db, "#").toString();
        QString empName = DataPublics::getDbValue("SELECT `Name` FROM vw_employeenames_all WHERE `employeeID` = '" +
                                                  empID + "'", db, "Name").toString();
        it->setText(0, entryID);
        it->setText(1, empID);
        it->setText(2, empNO);
        it->setText(3, empName);
        it->setText(4, rec.value("DateIn").toDate().toString("dd MMM yyyy"));
        it->setText(5, rec.value("TimeIn").toString());
        it->setText(6, rec.value("DateOut").toDate().toString("dd MMM yyyy"));
        it->setText(7, rec.value("TimeOut").toString());
        it->setCheckState(2, Qt::Unchecked);
    }
    ui->trvAttendance->setColumnHidden(0, true);
    ui->trvAttendance->setColumnHidden(1, true);
}

void PostBiometricAttendanceWizard::on_dtpDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    reloadEmployees();

}

void PostBiometricAttendanceWizard::pageChanged(int pageNum)
{
    if (pageNum == 1) {
        QString html = "<h2>Attendance Data Entry</h2>";
        html += "<br/>";
        html += "<b>Shift:</b> " + ui->cboShift->currentText();
        html += "<br/>";
        html += "<b>Date:</b> " + ui->dtpDate->date().toString("dd MMM yyyy");
        html += "<br/>";
        html += "<br/>";

        html += "<br/>";
        html += "<table width=100% border=0>";
        html += "<tr bgcolor=\"lightgray\">";
        html += "<td><b>Roll No.</b></td>";
        html += "<td><b>Name</b></td>";
        html += "<td><b>Time In</b></td>";
        html += "<td><b>Time Out</b></td>";
        html += "</tr>";

        for (int r = 0; r < ui->trvAttendance->invisibleRootItem()->childCount(); r++) {
            QTreeWidgetItem *it = ui->trvAttendance->invisibleRootItem()->child(r);
            if (it->checkState(2) == Qt::Checked) {
                QString rollNo = it->text(2);
                QString empName = it->text(3);
                QString timeIn = it->text(5);
                QString timeOut = it->text(7);

                html += "<tr>";
                html += "<td>" + rollNo + "</td>";
                html += "<td>" + empName + "</td>";
                html += "<td>" + timeIn + "</td>";
                html += "<td>" + timeOut + "</td>";
                html += "</tr>";
            }
        }
        html += "</table>";
        ui->txtReview->setHtml(html);

    }
    if (pageNum == 2) {
        if (!saved) {
            saved = true;
            on_cmdSave_clicked();
        }
    }
}

void PostBiometricAttendanceWizard::on_cmdSave_clicked()
{
    QString shiftID = DataPublics::getDbValue("SELECT ShiftID FROM shifts WHERE ShiftName = '" + ui->cboShift->currentText() + "'", db, "ShiftID").toString();
    QString quError = "";
    QStringList calcs;
    for (int r = 0; r < ui->trvAttendance->invisibleRootItem()->childCount(); r++) {
        QTreeWidgetItem *it = ui->trvAttendance->invisibleRootItem()->child(r);
        if (it->checkState(2) == Qt::Checked) {
            QString dateIn = QDate::fromString(it->text(4), "dd MMM yyyy").toString("yyyy-MM-dd");
            QString dateOut = QDate::fromString(it->text(6), "dd MMM yyyy").toString("yyyy-MM-dd");
            QString timeIn = it->text(5);
            QString timeOut = it->text(7);
            QString empID = it->text(1);
            QString entID = it->text(0);
            QString comment = "";
            db.exec("DELETE FROM attendance_2 WHERE EmployeeID = '" + empID + "'"
                    " AND DateIn = '" + dateIn + "'");
            QSqlQuery qu = db.exec("INSERT INTO attendance_2 "
                                   " (EmployeeID, ShiftID, Note, DateIn, DateOut, TimeIn, Type, TimeOut) "
                                   " VALUES ('"
                                   + empID + "', '"
                                   + shiftID + "', '"
                                   + comment + "', '"
                                   + dateIn + "', '"
                                   + dateOut + "', '"
                                   + timeIn + "', '"
                                   + "Auto', '"
                                   + timeOut + "')");

            db.exec("UPDATE attendance_3 SET Assigned = 'Yes' WHERE EntryID = '" + entID + "'");

            if (qu.lastError().isValid()) {
                quError.append(qu.lastError().text());
            } else {
                db.exec("CALL calculate_attendance('" + qu.lastInsertId().toString() + "')");
                calcs << qu.lastInsertId().toString();
            }
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
