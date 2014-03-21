#include "smartreportwidget.h"
#include "ui_smartreportwidget.h"

SmartReportWidget::SmartReportWidget(QWidget *parent) :
    QPrintPreviewWidget(parent),
    ui(new Ui::SmartReportWidget)
{
    ui->setupUi(this);
}

SmartReportWidget::~SmartReportWidget()
{
    delete ui;
}
