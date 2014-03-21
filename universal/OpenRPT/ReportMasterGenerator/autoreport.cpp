#include "autoreport.h"
#include "ui_autoreport.h"

AutoReport::AutoReport(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::AutoReport)
{
    ui->setupUi(this);
    db  = database;
    dataModel = new QSqlQueryModel(this);
}

AutoReport::~AutoReport()
{
    delete ui;
}

void AutoReport::on_cmdPreview_clicked()
{
    dataModel = new QSqlQueryModel(this);
    dataModel->setQuery(ui->txtQuery->toPlainText(), db);
    ui->trvPreview->setModel(dataModel);
}

void AutoReport::on_cmdGenerateReport_clicked()
{
    ui->txtReport->setPlainText(DataPublics::getReportXML(ui->txtQuery->toPlainText(), "MCL", db, true, true, true, false));
}
