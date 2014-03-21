#include "scheduledreportsmainwindow.h"
#include "ui_scheduledreportsmainwindow.h"

#include "datapublics.h"
#include "htmlreportpreview.h"
#include <QMessageBox>
ScheduledReportsMainWindow::ScheduledReportsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScheduledReportsMainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL", "ScheduledReportsConnection");
    db.setHostName(DataPublics::getIniSetting("hostName"));
    db.setUserName(DataPublics::getIniSetting("userName"));
    db.setDatabaseName("cartons");
    db.setPassword(DataPublics::getIniSetting("password"));

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", "Could not connect to the reports database.\n\n" + db.lastError().text());
        this->close();
        qApp->quit();
    }

    reloadReportList();
}

ScheduledReportsMainWindow::~ScheduledReportsMainWindow()
{
    delete ui;
}

void ScheduledReportsMainWindow::reloadReportList()
{
    ui->trvReports->setQuery("SELECT ReportID, ReportName as 'Name', ReportDescription as 'Description', ReportTitle as 'Title' FROM scheduled_reports", db, "Scheduled Reports", true);
    ui->trvReports->setColumnHidden(0, true);
}

#include "reporteditor.h"
void ScheduledReportsMainWindow::on_action_New_triggered()
{
    ReportEditor *ed = new ReportEditor(this, db);
    ed->addNew();
    if (ed->exec() == QDialog::Accepted) {
        reloadReportList();
    }
}

void ScheduledReportsMainWindow::on_trvReports_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString id = ui->trvReports->getCurrentID();
    if (id.length() > 0) {
        ReportEditor *ed = new ReportEditor(this, db);
        ed->edit(id);
        if (ed->exec() == QDialog::Accepted) {
            reloadReportList();
        }
    }
}

#include "htmlgenerator.h"
#include "html_printer.h"
void ScheduledReportsMainWindow::on_action_Print_Preview_triggered()
{
    QString id = ui->trvReports->getCurrentID();
    if (id.length() > 0) {
        QString html = HtmlGenerator::showReportHtml(id, db);
       // HTMLReportPreview *pre = new HTMLReportPreview(this, html);
      //  pre->show();
        HTML_PRINTER *p = new HTML_PRINTER(this, "Report Preview", html);
    }
}
