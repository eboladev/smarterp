#include "loadreportfromsql.h"
#include "ui_loadreportfromsql.h"

LoadReportFromSQL::LoadReportFromSQL(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::LoadReportFromSQL)
{
    ui->setupUi(this);
    db = database;
    save = false;
}

LoadReportFromSQL::~LoadReportFromSQL()
{
    delete ui;
}

void LoadReportFromSQL::on_cmdPrintOnly_clicked()
{

    query = ui->txtSQL->toPlainText();
    title = ui->txtTitle->text();
    landscape = ui->optLandscape->isChecked();
    lines = ui->chkShowLines->isChecked();
    pageNumbers = ui->chkShowPageNumbers->isChecked();
    this->accept();
}

void LoadReportFromSQL::on_cmdPrintAndSave_clicked()
{
    save = true;
    on_cmdPrintOnly_clicked();
}
