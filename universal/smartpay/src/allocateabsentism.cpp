#include "allocateabsentism.h"
#include "ui_allocateabsentism.h"

AllocateAbsentism::AllocateAbsentism(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::AllocateAbsentism)
{
    ui->setupUi(this);
    db = database;
    ui->dtpDate->setDate(QDate::currentDate());
}

AllocateAbsentism::~AllocateAbsentism()
{
    delete ui;
}

void AllocateAbsentism::on_dtpDate_dateChanged(const QDate &date)
{
    ui->trvAll->invisibleRootItem()->takeChildren();
    QString where =  "WHERE DateIn = '" + date.toString("yyyy-MM-dd") + "' ";
    QSqlQuery qu = db.exec("SELECT * FROM vw_attendance_2 " + where + " AND TRIM(Comment) = ''");
    while (qu.next()) {
        QString entryID = qu.record().value("EntryID").toString();
        //QSqlQuery qu2 = db.exec("SELECT * FROM absentism WHERE AttendanceID = '" + entryID + "'");
        //if (qu2.size() < 1) {
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvAll);
        it->setText(0, qu.record().value("Name").toString());
        it->setText(1, qu.record().value("ShiftName").toString());
        it->setText(2, qu.record().value("DateIn").toString());
        it->setText(3, qu.record().value("TimeIn").toString());
        it->setText(4, qu.record().value("DateOut").toString());
        it->setText(5, qu.record().value("TimeOut").toString());
        it->setText(99, entryID);
        it->setCheckState(0, Qt::Unchecked);
        //ui->trvAll->invisibleRootItem()->addChild(it);
        //}
    }

    ui->trvAbsent->setQuery("SELECT * FROM vw_attendance_2 " + where + " AND Comment = 'Absent'", db, "Absent", true);
    ui->trvAbsent->setColumnHidden(0, true);

    ui->trvLeave->setQuery("SELECT * FROM vw_attendance_2 " + where + " AND (Comment = 'Leave' OR Comment = 'Sick')", db, "Leave", true);
    ui->trvLeave->setColumnHidden(0, true);
}

void AllocateAbsentism::on_cmdAddToLeave_clicked()
{
    for (int i = 0; i < ui->trvAll->invisibleRootItem()->childCount(); i++) {
        if (ui->trvAll->invisibleRootItem()->child(i)->checkState(0) == Qt::Checked) {
            QTreeWidgetItem *it = ui->trvAll->invisibleRootItem()->child(i);
            QString id = it->text(99);
            db.exec("UPDATE attendance_2 SET Note = 'Leave' WHERE EntryID = '" + id + "'");
        }
    }
    on_dtpDate_dateChanged(ui->dtpDate->date());
}

void AllocateAbsentism::on_cmdAddToAbsent_clicked()
{
    for (int i = 0; i < ui->trvAll->invisibleRootItem()->childCount(); i++) {
        if (ui->trvAll->invisibleRootItem()->child(i)->checkState(0) == Qt::Checked) {
            QTreeWidgetItem *it = ui->trvAll->invisibleRootItem()->child(i);
            QString id = it->text(99);
            db.exec("UPDATE attendance_2 SET Note = 'Absent' WHERE EntryID = '" + id + "'");
        }
    }
    on_dtpDate_dateChanged(ui->dtpDate->date());
}

void AllocateAbsentism::on_cmdRemoveFromLeave_clicked()
{
    QString id = ui->trvLeave->getCurrentID();
    if (id.length() > 0) {
        db.exec("UPDATE attendance_2 SET Note = '' WHERE EntryID = '" + id + "'");
    }
    on_dtpDate_dateChanged(ui->dtpDate->date());
}

void AllocateAbsentism::on_cmdRemoveFromAbsent_clicked()
{
    QString id = ui->trvAbsent->getCurrentID();
    if (id.length() > 0) {
        db.exec("UPDATE attendance_2 SET Note = '' WHERE EntryID = '" + id + "'");
    }
    on_dtpDate_dateChanged(ui->dtpDate->date());
}

void AllocateAbsentism::on_toolButton_clicked()
{
    on_dtpDate_dateChanged(ui->dtpDate->date());
}
