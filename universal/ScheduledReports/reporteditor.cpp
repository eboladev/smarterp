#include "reporteditor.h"
#include "ui_reporteditor.h"
#include "datapublics.h"
ReportEditor::ReportEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::ReportEditor)
{
    ui->setupUi(this);
    db = database;
    ui->lblSQLError->setVisible(false);
    QSqlQuery qu = db.exec("SELECT UserID, FullName, Email from users");
    while (qu.next()) {
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvRecepients);
        it->setText(0, qu.record().value("FullName").toString());
        it->setText(1, qu.record().value("Email").toString());
        it->setText(99, qu.record().value("UserID").toString());
        it->setCheckState(0, Qt::Unchecked);
    }

    isAdding  = true;

    for (int i = 0; i < ui->lstMonths->count(); ++i) {
        ui->lstMonths->item(i)->setCheckState(Qt::Checked);
        ui->lstMonths->item(i)->setCheckState(Qt::Unchecked);
    }


    for (int i = 0; i < ui->lstDays->count(); ++i) {
        ui->lstDays->item(i)->setCheckState(Qt::Checked);
        ui->lstDays->item(i)->setCheckState(Qt::Unchecked);
    }

    for (int i = 0; i < ui->lstHours->count(); ++i) {
        ui->lstHours->item(i)->setCheckState(Qt::Checked);
        ui->lstHours->item(i)->setCheckState(Qt::Unchecked);
    }

    for (int i = 0; i < ui->lstMinutes->count(); ++i) {
        ui->lstMinutes->item(i)->setCheckState(Qt::Checked);
        ui->lstMinutes->item(i)->setCheckState(Qt::Unchecked);
    }
}

ReportEditor::~ReportEditor()
{
    delete ui;
}

void ReportEditor::addNew()
{
    isAdding = true;
}

void ReportEditor::edit(QString id)
{
    isAdding = false;
    currentID = id;

    QSqlQuery qu = db.exec("SELECT * FROM scheduled_reports WHERE ReportID = '" + currentID + "'");

    if (qu.lastError().isValid()) {
        QMessageBox::warning(this, "Database Error", qu.lastError().text());
    }
    else {
        qu.first();
        QSqlRecord rec = qu.record();
        ui->txtReportName->setText(rec.value("ReportName").toString());
        ui->txtDescription->setText(rec.value("ReportDescription").toString());
        ui->txtTitle->setText(rec.value("ReportTitle").toString());
        ui->txtSQL->setPlainText(rec.value("ReportSQL").toString());
    }

    qu = db.exec("SELECT * FROM scheduled_reports_recepients WHERE ReportID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        QMessageBox::warning(this, "Database Error", qu.lastError().text());
    }
    else {
        while (qu.next()) {
            QSqlRecord rec = qu.record();
            for (int i = 0; i < ui->trvRecepients->invisibleRootItem()->childCount(); ++i) {
                QTreeWidgetItem *it = ui->trvRecepients->invisibleRootItem()->child(i);
                if (it->text(99) == rec.value("UserID").toString())
                    it->setCheckState(0, Qt::Checked);
            }
        }
    }

    qu = db.exec("SELECT * FROM scheduled_reports_schedule WHERE ReportID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        QMessageBox::warning(this, "Database Error", qu.lastError().text());
    }
    else {
        qu.first();
        QSqlRecord rec = qu.record();
        QStringList months = rec.value("Months").toString().split(",");
        QStringList days = rec.value("Days").toString().split(",");
        QStringList hours = rec.value("Hours").toString().split(",");
        QStringList minutes = rec.value("Minutes").toString().split(",");

        for (int i = 0; i < ui->lstMonths->count(); ++i) {
            if (months.contains(ui->lstMonths->item(i)->text())) {
                ui->lstMonths->item(i)->setCheckState(Qt::Checked);
            }
        }

        for (int i = 0; i < ui->lstHours->count(); ++i) {
            if (hours.contains(ui->lstHours->item(i)->text())) {
                ui->lstHours->item(i)->setCheckState(Qt::Checked);
            }
        }

        for (int i = 0; i < ui->lstDays->count(); ++i) {
            if (days.contains(ui->lstDays->item(i)->text())) {
                ui->lstDays->item(i)->setCheckState(Qt::Checked);
            }
        }

        for (int i = 0; i < ui->lstMinutes->count(); ++i) {
            if (minutes.contains(ui->lstMinutes->item(i)->text())) {
                ui->lstMinutes->item(i)->setCheckState(Qt::Checked);
            }
        }

       loadColumns(ui->txtSQL->toPlainText());
    }
}

void ReportEditor::on_cmdSave_clicked()
{
    QString query = "SELECT Now()";
    if (isAdding) {
        QSqlQuery insQU = db.exec("INSERT INTO scheduled_reports (ReportName) VALUES ('" +  ui->txtReportName->text() + "')");
        if (insQU.lastError().isValid()) {
            QMessageBox::warning(this, "Database Error", insQU.lastError().text());
            return;
        } else {
            currentID = insQU.lastInsertId().toString();
        }
    }

    QString hidden = "";
    QString sum = "";

    for (int h = 0; h < ui->lstHiddenColumns->count(); ++h) {
        if (ui->lstHiddenColumns->item(h)->checkState() == Qt::Checked)
            hidden += ui->lstHiddenColumns->item(h)->text() + ",";
    }

    for (int s = 0; s < ui->lstHiddenColumns->count(); ++s) {
        if (ui->lstSumColumns->item(s)->checkState() == Qt::Checked)
            sum += ui->lstSumColumns->item(s)->text() + ",";
    }

    query = "UPDATE scheduled_reports SET ReportName = '" + ui->txtReportName->text() + "', "
            " ReportTitle = '" + ui->txtTitle->text() + "', "
            " ReportDescription = '" + ui->txtDescription->text() + "', "
            " HiddenColumns = '" + hidden + "', "
            " SumColumns = '" + sum + "', "
            " ReportSQL = '" + ui->txtSQL->toPlainText() + "' WHERE ReportID = '" + currentID + "'";

    QSqlQuery qu = db.exec(query);
    if (qu.lastError().isValid()) {
        QMessageBox::warning(this, "Database Error", qu.lastError().text());
    } else {
        QString errors = "";
        //Save Recepients
        db.exec("DELETE FROM scheduled_reports_recepients WHERE ReportID = '" + currentID + "'");
        for (int i = 0; i < ui->trvRecepients->invisibleRootItem()->childCount(); ++i) {
            if (ui->trvRecepients->invisibleRootItem()->child(i)->checkState(0) == Qt::Checked) {
                QString userID = ui->trvRecepients->invisibleRootItem()->child(i)->text(99);
                db.exec(tr("INSERT INTO scheduled_reports_recepients (ReportID, UserID) VALUES ('%1', '%2')").arg(currentID, userID));
                if (db.lastError().isValid()) {
                    errors += "Recepients: " + db.lastError().text() + "\n\n";
                }
            }
        }
        //Save Schedule
        db.exec("DELETE FROM scheduled_reports_schedule WHERE ReportID = '" + currentID + "'");
        QString months = "";
        QString days = "";
        QString hours = "";
        QString minutes = "";

        for (int i = 0; i < ui->lstMonths->count(); ++i) {
            if (ui->lstMonths->item(i)->checkState() == Qt::Checked)
                months += ui->lstMonths->item(i)->text() + ",";
        }

        for (int i = 0; i < ui->lstDays->count(); ++i) {
            if (ui->lstDays->item(i)->checkState() == Qt::Checked)
                days += ui->lstDays->item(i)->text() + ",";
        }

        for (int i = 0; i < ui->lstHours->count(); ++i) {
            if (ui->lstHours->item(i)->checkState() == Qt::Checked)
                hours += ui->lstHours->item(i)->text() + ",";
        }

        for (int i = 0; i < ui->lstMinutes->count(); ++i) {
            if (ui->lstMinutes->item(i)->checkState() == Qt::Checked)
                minutes += ui->lstMinutes->item(i)->text() + ",";
        }

        db.exec(tr("INSERT INTO scheduled_reports_schedule (ReportID, Months, Days, Hours, Minutes) VALUES ("
                   "'%1', '%2', '%3', '%4', '%5')")
                .arg(currentID, months, days, hours, minutes));
        if (db.lastError().isValid()) {
            errors += "Schedule : " + db.lastError().text() + "\n\n";
        }

        if (errors.length() > 0) {
            QMessageBox::warning(this, "Database Error", errors);
            return;
        }

        this->accept();
    }
}

void ReportEditor::on_txtSQL_textChanged()
{
    QString query = ui->txtSQL->toPlainText();
    if (!query.contains(" LIMIT ")) {
        query.append("LIMIT 0, 1");
    }

    loadColumns(query);
}

void ReportEditor::loadColumns(QString sql)
{
    QSqlQuery qu1 = db.exec("SELECT SumColumns, HiddenColumns FROM scheduled_reports WHERE ReportID = '" + currentID + "'");
    if (qu1.lastError().isValid()) {
        DataPublics::showWarning(qu1.lastError().text());
        return;
    }
    qu1.first();
    QSqlRecord rec = qu1.record();

    QStringList sumCols = rec.value("SumColumns").toString().split(",");
    sumCols.removeLast();
    sumCols.removeDuplicates();

    QStringList hiddenCols = rec.value("HiddenColumns").toString().split(",");
    hiddenCols.removeLast();
    hiddenCols.removeDuplicates();

    QSqlQuery qu = db.exec(sql);
    if (qu.lastError().isValid()) {
        ui->lblSQLError->setVisible(true);
        //DataPublics::showWarning(qu.lastError().text());
        return;
    }
    ui->lblSQLError->setVisible(false);
    ui->lstHiddenColumns->clear();
    ui->lstSumColumns->clear();
    for (int i = 0; i < qu.record().count(); i++) {
        QString colName =  qu.record().fieldName(i);
        ui->lstSumColumns->addItem(colName);
        ui->lstHiddenColumns->addItem(colName);

        ui->lstSumColumns->item(i)->setCheckState(Qt::Unchecked);
        ui->lstHiddenColumns->item(i)->setCheckState(Qt::Unchecked);

        if (sumCols.contains(colName))
            ui->lstSumColumns->item(i)->setCheckState(Qt::Checked);

        if (hiddenCols.contains(colName))
            ui->lstHiddenColumns->item(i)->setCheckState(Qt::Checked);
    }
}
