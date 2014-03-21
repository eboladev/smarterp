#include "reportdateselectwidget.h"
#include "ui_reportdateselectwidget.h"

ReportDateSelectWidget::ReportDateSelectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportDateSelectWidget)
{
    ui->setupUi(this);
}

ReportDateSelectWidget::~ReportDateSelectWidget()
{
    delete ui;
}

void ReportDateSelectWidget::on_pushButton_clicked()
{

}
