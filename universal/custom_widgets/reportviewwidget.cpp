#include "reportviewwidget.h"
#include "ui_reportviewwidget.h"

ReportViewWidget::ReportViewWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ReportViewWidget)
{
	ui->setupUi(this);
}

ReportViewWidget::~ReportViewWidget()
{
	delete ui;
}
