#ifndef SMARTREPORTWIDGET_H
#define SMARTREPORTWIDGET_H

#include <QPrinter>
#include <QPrintPreviewWidget>
#include <QWidget>

namespace Ui {
class SmartReportWidget;
}

class SmartReportWidget : public QPrintPreviewWidget
{
	Q_OBJECT

public:
	explicit SmartReportWidget(QWidget *parent = 0);
	~SmartReportWidget();

private:
	Ui::SmartReportWidget *ui;
};

#endif // SMARTREPORTWIDGET_H
