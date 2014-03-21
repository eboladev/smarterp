#include "dcmainwindow.h"
#include "ui_dcmainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

#include "publics.h"
#include "customersearchwidget.h"
#include "quickcalendarview.h"

#include "mymodels.h"

DCMainWindow::DCMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DCMainWindow)
{
    ui->setupUi(this);
    runCount = 0;
    db = Publics::getDatabase();

    m_customerSearchWidget = new customerSearchWidget(this);
    ui->toolBar->addWidget(m_customerSearchWidget);

    ui->lblCurrentFile->setHidden(true);
    ui->actionNew_File->setVisible(false);

    ui->actionAlerts->setChecked(false);
    ui->actionTo_Do_List->setChecked(false);
    ui->dockWidget_2->setVisible(false);
    ui->dockTransactions->setVisible(false);

    reloadFiles();

    hasFile = false;
    currentFileNo = "";

    ui->dockCalendar->setVisible(false);
    calStartDate = QDate::currentDate().addDays(-3);


    ui->dtpChequeDate->setDate(QDate::currentDate());

    reloadCalendarSpecs();
    reloadCalendar();
    reloadTransactions();
    reloadAgeing();

    reloadCheques();
    ui->dockChequeRegister->setVisible(false);
}

DCMainWindow::~DCMainWindow()
{
    delete ui;
}

void DCMainWindow::on_actionNew_Action_triggered()
{

}

void DCMainWindow::reloadCalendarSpecs()
{
    myColors.clear();
    myCalendars.clear();
    myIcons.clear();

    const QStringList colorNames = QColor::colorNames();


    foreach (const QString &colorName, colorNames) {
        const QColor color(colorName);
        myColors << QColor(color.red(), color.green(), color.blue());
    }



    QListIterator <QColor> i(myColors);
    while(i.hasNext())
    {
        QColor color = i.next();
        // qDebug() << color.name();
        QPixmap pixmap(24, 24);
        pixmap.fill(color);
        QIcon icon;
        icon.addPixmap(pixmap);
        myIcons.append(icon);
    }

    QSqlQuery actions_query = db.exec("SELECT * FROM appointment_types");
    if (actions_query.lastError().isValid()) {
        Publics::showError(actions_query.lastError().text());
    } else {
        while (actions_query.next()) {
            Calendar *cal = new Calendar(myCalendars.count());
            cal->setName(actions_query.record().value(1).toString());
            QString colName = actions_query.record().value("Color").toString();

            for (int iC = 0; iC < myColors.count(); iC++) {
                qDebug() << myColors.at(iC).rgb() << QColor(colName).rgb();
                if (myColors.at(iC).rgb() == QColor(colName).rgb())
                    cal->setColor(myColors.at(iC));
            }
            cal->setSelected(true);

            //Show appointments
            QString calID = actions_query.record().value(0).toString();
            cal->setKey(calID.toInt());

            QSqlDatabase db = Publics::getDatabase();
            if (db.isOpen()) {
                QSqlQuery qu = db.exec("SELECT * FROM appointments WHERE AppointmentType = '"  + calID + "' AND Deleted = 'No'");
                while (qu.next()) {
                    QString calendarName = Publics::getDbValue(db, "SELECT * FROM appointment_types WHERE EntryID = '" + qu.record().value("AppointmentType").toString() + "'", "AppointmentTypeName");
                    if (calendarName == cal->name()) {
                        Appointment *app = new Appointment();
                        QString complete = qu.record().value("IsComplete").toString();
                        bool cmp = false;
                        if (complete == "true")
                            cmp = true;
                        //app->setKey(qu.record().value(0).toInt());
                        app->setCalendar(cal);
                        app->setCalendarKey(calID.toInt());
                        app->setKey(qu.record().value(0).toInt());
                        app->setSubject(qu.record().value("Subject").toString());
                        app->setPlace(qu.record().value("Location").toString());
                        app->setCustomerID(qu.record().value("CustomerID").toString());
                        app->setIsComplete(cmp);
                        QString sD = qu.record().value("StartDate").toString();
                        QString eD = qu.record().value("EndDate").toString();
                        QString sT = qu.record().value("StartTime").toString();
                        QString eT = qu.record().value("EndTime").toString();

                        QDate startDate = QDate::fromString(sD, "yyyy-MM-dd");
                        QDate endDate = QDate::fromString(eD, "yyyy-MM-dd");

                        QTime startTime = QTime::fromString(sT, "hh:mm:ss");
                        QTime endTime = QTime::fromString(eT, "hh:mm:ss");

                        QDateTime sdt = QDateTime(startDate, startTime);
                        QDateTime edt = QDateTime(endDate, endTime);

                        qDebug() << sdt <<edt;

                        app->setDateTimes(sdt, edt);

                        cal->insertAppointment(app);
                    }
                }
            }

            myCalendars.append(cal);
        }
    }

}

void DCMainWindow::reloadCalendar()
{
    //Initialize quick calendar

    ptrCalendarModel = new CalendarTableModel();
    ptrCalendarModel->setCalendars(&myCalendars);




    if (runCount > 0) {
        delete ptrCalendarView;
    }

    runCount ++;

    ptrCalendarView = new QuickCalendarView();
    ptrCalendarView->setCalendars(&myCalendars);

    ptrCalendarView->setMonth(QDate::currentDate().year(), QDate::currentDate().month());
    ui->calendarLayout->addWidget(ptrCalendarView);
    QDate dStart = calStartDate;
    QDate dEnd = dStart.addDays(7);

    ui->lblDateRange->setText(dStart.toString("dd-MMM-yyyy") + " to " + dEnd.toString("dd-MMM-yyyy"));
    qDebug() << "3";
    ptrCalendarView->setRange(dStart, dEnd);
    qDebug() << "4";
    if (ui->cboCalendarMode->currentText() == "Month") {
        ptrCalendarView->setDisplayMode(QuickCalendarView::DisplayFullWeeks);
    } else {
        ptrCalendarView->setDisplayMode(QuickCalendarView::DisplayOnlyRange);
    }
}

#include "newfiledialog.h"
void DCMainWindow::on_actionNew_File_triggered()
{
    NewFileDialog *nF = new NewFileDialog(this, db);
    if (nF->exec() == QDialog::Accepted) {
        reloadFiles();
    }
}

void DCMainWindow::reloadFiles()
{
    ui->trvActiveCustomers->invisibleRootItem()->takeChildren();

}


void DCMainWindow::loadFile(QString fileNo)
{

}

void DCMainWindow::on_cmdDateLeft_clicked()
{
    calStartDate = calStartDate.addDays(-1);
    reloadCalendar();
}

void DCMainWindow::on_cmdDateRight_clicked()
{
    calStartDate = calStartDate.addDays(1);
    reloadCalendar();
}

#include "actiontypes.h"
void DCMainWindow::on_actionAction_Types_triggered()
{
    ActionTypes *act  = new ActionTypes(this, db);
    act->exec();
}

#include "appointmentdetailsform.h"
void DCMainWindow::on_actionNew_Appointment_triggered()
{
    Appointment *app = new Appointment();
    QDateTime sdt = QDateTime(calStartDate, QTime::currentTime());
    QDateTime edt = QDateTime(calStartDate, QTime::currentTime().addSecs(600));

    app->setDateTimes(sdt, edt);

    AppointmentDetailsForm *det = new AppointmentDetailsForm(app, &myCalendars);

    connect (det, SIGNAL(onClose(Appointment*)), this, SLOT(SaveNewAppointment(Appointment*)));



    det->show();
}

void DCMainWindow::SaveNewAppointment(Appointment *app)
{
    Q_UNUSED(app);
    reloadCalendarSpecs();
    reloadCalendar();
}

void DCMainWindow::reloadTransactions()
{
    ui->transWidget->reloadData();
}


void DCMainWindow::reloadAgeing()
{
    ageingModel = new AgeingModel(this);
    ageingModel->setQuery("SELECT CompanyName as 'Customer', CurrentBalance as 'Current', `30`, `60`, `90`, `120`, Over120 as '> 120', Total FROM customer_balances", db);
    ui->trvAgeing->setModel(ageingModel);

    ui->trvAgeing->setAlternatingRowColors(true);
}

#include "extendednewaction.h"
void DCMainWindow::on_actionNew_Call_triggered()
{
    ExtendedNewAction *newP = new ExtendedNewAction(this, &myCalendars);
    if (newP->exec() == QDialog::Accepted) {
        reloadCalendarSpecs();
        reloadCalendar();
    }
}

void DCMainWindow::on_trvAgeing_doubleClicked(const QModelIndex &index)
{
    QModelIndex companyNameIndex = ageingModel->index(index.row(), 0);
    QString companyName = ageingModel->data(companyNameIndex, Qt::DisplayRole).toString() ;
    qDebug() << "Company Name is " << companyName;

    if (index.column() == 0) {
        ExtendedNewAction *newP = new ExtendedNewAction(this, &myCalendars);
        newP->setCustomer(companyName);
        if (newP->exec() == QDialog::Accepted) {
            reloadCalendarSpecs();
            reloadCalendar();
        }
    }

    if (index.column() > 0) {
        QDialog* dg = new QDialog(this, Qt::Tool|Qt::WindowStaysOnTopHint|Qt::Popup);
        dg->setWindowTitle(companyName);
        TransactionView *vw = new TransactionView(dg);
        QBoxLayout *bg = new QBoxLayout(QBoxLayout::TopToBottom, dg);
        bg->addWidget(vw);
        dg->setLayout(bg);

        QDate startDate;
        QDate endDate;

        if (index.column() == 1) {
            //Current
            startDate = QDate::currentDate().addDays(-1);
            endDate = QDate::currentDate();
        } else if (index.column() == 2) {
            //0-30
            startDate = QDate::currentDate().addDays(-30);
            endDate = QDate::currentDate().addDays(-1);
        } else if (index.column() == 3) {
            //30-60
            startDate = QDate::currentDate().addDays(-60);
            endDate = QDate::currentDate().addDays(-30);
        } else if (index.column() == 4) {
            //60-90
            startDate = QDate::currentDate().addDays(-90);
            endDate = QDate::currentDate().addDays(-60);
        } else if (index.column() == 5) {
            //90-120
            startDate = QDate::currentDate().addDays(-120);
            endDate = QDate::currentDate().addDays(-90);
        } else if (index.column() == 6) {
            //>120
            startDate = QDate::currentDate().addDays(-3000);
            endDate = QDate::currentDate().addDays(-120);
        } else if (index.column() == 7) {
            //Total
            startDate = QDate::currentDate().addDays(-3000);
            endDate = QDate::currentDate().addDays(0);
        }

        vw->setCustomer(companyName);
        vw->setStartDate(startDate);
        vw->setEndDate(endDate);
        vw->reloadData();

        dg->showNormal();
    }
}

void DCMainWindow::on_cboCalendarMode_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    //reloadCalendarSpecs();
    reloadCalendar();
}

void DCMainWindow::on_actionView_Register_triggered()
{
    ui->dockChequeRegister->setVisible(!ui->dockChequeRegister->isVisible());
}

void DCMainWindow::reloadCheques()
{


    //    ui->lstCheques->setQuery("SELECT * FROM vw_cheques", db, "Cheque Register", true);
    //    ui->lstCheques->setColumnHidden(0, true);

    ui->lstCheques->setVisible(false);

    QSqlQuery qu = db.exec("SELECT * FROM vw_cheques WHERE `Cheque Date` = '" + ui->dtpChequeDate->date().toString("yyyy-MM-dd") + "'");
    if (qu.lastError().isValid()) {
        Publics::showError(qu.lastError().text());
    } else {
        ui->trvChequeList->invisibleRootItem()->takeChildren();
        while (qu.next()) {
            QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvChequeList);
            it->setText(99, qu.record().value("ChequeID").toString());
            it->setText(0, qu.record().value(1).toString());
            it->setText(1, qu.record().value(2).toString());
            it->setText(2, qu.record().value(3).toString());
            it->setText(3, qu.record().value(4).toString());
            it->setText(4, qu.record().value(5).toString());
            it->setText(5, qu.record().value(6).toString());

            it->setCheckState(0, Qt::Unchecked);
        }
    }
}

#include "chequeeditor.h"
void DCMainWindow::on_cmdNewCheque_clicked()
{
    ChequeEditor *ed = new ChequeEditor(this, db);
    ed->AddNew();
    if (ed->exec() == QDialog::Accepted) {
        //Ok
        reloadCheques();
    }
}

void DCMainWindow::on_lstCheques_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    if (ui->lstCheques->getCurrentID().length() > 0) {
        QString id = ui->lstCheques->getCurrentID();
        ChequeEditor *ed = new ChequeEditor(this, db);
        ed->Edit(id);
        if (ed->exec() == QDialog::Accepted) {
            //Ok
            reloadCheques();
        }
    }
}

#include "chequedeposit.h"
void DCMainWindow::on_cmdDeposit_clicked()
{
    QString id = "";
    ChequeDeposit *dep = new ChequeDeposit(this, db, id);
    for (int i = 0; i < ui->trvChequeList->invisibleRootItem()->childCount(); i++) {
        if (ui->trvChequeList->invisibleRootItem()->child(i)->checkState(0) == Qt::Checked) {
            dep->addCheque(ui->trvChequeList->invisibleRootItem()->child(i)->text(99));
        }
    }
    if (dep->exec() == QDialog::Accepted) {
        reloadCheques();
    }
}

void DCMainWindow::on_cmdRefreshAgeing_clicked()
{
    reloadAgeing();
}

void DCMainWindow::on_trvChequeList_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    QString id = item->text(99);
    ChequeEditor *ed = new ChequeEditor(this, db);
    ed->Edit(id);
    if (ed->exec() == QDialog::Accepted) {
        //Ok
        reloadCheques();
    }
}

void DCMainWindow::on_dtpChequeDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    reloadCheques();
}
