#include "finishing_report.h"
#include "ui_finishing_report.h"

#include "htmlgenerator.h"

finishing_report::finishing_report(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::finishing_report)
{
    ui->setupUi(this);
    db = database;
    ui->dtpEndDate->setDate(QDate::currentDate());
    ui->dtpStartDate->setDate(QDate::currentDate().addDays(-30));
    refresh();
}

finishing_report::~finishing_report()
{
    delete ui;
}

void finishing_report::on_cmdRefresh_clicked()
{
    refresh();
}

void finishing_report::refresh()
{
    HtmlGenerator *gen = new HtmlGenerator(this);
    gen->AddHiddenColumn("EntryID");
    gen->AddSumColumn("Produced");

    QString query = "SELECT NOW()";
    query = "SELECT * FROM vw_finishing";
    QString startDate = ui->dtpStartDate->date().toString("yyyy-MM-dd");
    QString endDate = ui->dtpEndDate->date().toString("yyyy-MM-dd");
    QString section = ui->cboSection->currentText();
//    if (section== "All")
//        section = "";

    if (section == "Gluing - H")
        section = "Gluing";

    QString sectionWhere = " AND Section = '" + section + "' ";

    if (section == "All") {
        sectionWhere = " AND Section LIKE '%%' ";
    }

    QString shift = ui->cboShift->currentText();
    if (shift == "All")
        shift = "";

    query.append(" WHERE `Date` BETWEEN '" + startDate + "' AND '" + endDate + "' ");
    query.append(" AND Shift LIKE '%" + shift + "%' ");
    query.append(sectionWhere);

    qDebug() << query;

    QString html = gen->getReportHTMLFromQuery(query, db, "Finishing Data");
    ui->txtData->setHtml(html);
}
