#include "createschedule.h"
#include "ui_createschedule.h"
#include "producteditoc.h"
#include "viewschedule.h"
CreateSchedule::CreateSchedule(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::CreateSchedule)
{
    ui->setupUi(this);
    db = database;
    ui->dtpScheduleDt->setDate(QDate::currentDate());
    connect (ui->calOCDate, SIGNAL(activated(QDate)), SLOT(reloadOrderList(QDate)));
    connect (ui->calOCDate, SIGNAL(clicked(QDate)), SLOT(reloadOrderList(QDate)));

    reloadOrderList(QDate::currentDate());
    reloadSchedule();
}

CreateSchedule::~CreateSchedule()
{
    delete ui;
}

void CreateSchedule::reloadOrderList(QDate newDate)
{
    ui->trvOders->setQuery("SELECT TicketNo, Client, Product, PaperSpecs, A, W FROM newreport WHERE ProductionTicked = 'No' AND Produced='No' AND Date = '" + DataPublics::mysqlDate(newDate) + "'", db, "Unprocessed Orders for (" + newDate.toString("dd MMM yyyy") + ")", false);
}

void CreateSchedule::reloadSchedule()
{
    ui->trvSchedule->setQuery("SELECT TicketNo as 'OC#', Client, Product, PaperSpecs, Round(A, 0) as 'A', L, W, T, S, F1, F2, F3, ProductionComment as 'Comment' FROM newreport WHERE (ProductionTicked = 'Yes') AND ((Qty * 1) > (CorugatorQty * 1)) ORDER By W DESC"
                              , db, "Production Schedule (" + QDate::currentDate().toString("dd MMM yyyy") + ")", false);
}

void CreateSchedule::on_cmdPrintSchedule_clicked()
{
    ViewSchedule *vs = new ViewSchedule(this, db);
    if (vs->exec()) {

    }
}

void CreateSchedule::on_cmdAddToSchedule_clicked()
{
    QString ocToAdd = ui->trvOders->getCurrentID();
    if (ocToAdd.length() > 0) {
        QString sqlQuery = "UPDATE newreport SET ProductionTicked = 'Yes', ProductionTicked = 'Yes' WHERE `TicketNo` = '" + ocToAdd + "'";
        db.exec(sqlQuery);
        reloadOrderList(ui->calOCDate->selectedDate());
        reloadSchedule();
    }
}

void CreateSchedule::on_cmdRemoveFromSchedule_clicked()
{
    QString ocToRemove = ui->trvSchedule->getCurrentID();
    if (ocToRemove.length() > 0) {
        QString sqlQuery = "UPDATE newreport SET ScheduleDate = '', ProductionTicked = 'No' WHERE `TicketNo` = '" + ocToRemove + "'";
        db.exec(sqlQuery);
        reloadOrderList(ui->calOCDate->selectedDate());
        reloadSchedule();
    }
}

void CreateSchedule::on_trvSchedule_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    ProductEditOC *ed = new ProductEditOC(this, db, ui->trvSchedule->getCurrentID());
    if (ed->exec()) {
        reloadSchedule();
    }
}



void CreateSchedule::on_cmdSaveSchedule_clicked()
{
    QString errors = "";
    QSqlQuery qu = db.exec("SELECT TicketNo FROM newreport WHERE (ProductionTicked = 'Yes') AND ((Qty * 1) > (CorugatorQty * 1)) ORDER By W DESC");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }
    while (qu.next()) {
        QString currentOcNo = qu.record().value("TicketNo").toString();
        QString query = "UPDATE newreport SET ScheduleDate = '" + ui->dtpScheduleDt->date().toString("yyyy-MM-dd") + "' WHERE TicketNo = '" + currentOcNo + "'";
        db.exec(query);
        qDebug() << query;
        if (db.lastError().isValid()) {
            errors.append(currentOcNo + " could not be added. Error: " + db.lastError().text() + "\n");
        }
    }
    if (errors.length() > 0) {
        DataPublics::showWarning(errors);
    } else {
        DataPublics::showInformation("Schedule saved successfully");
    }
}
