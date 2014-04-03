#ifndef REPORTVIEWWIDGET_H
#define REPORTVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class ReportViewWidget;
}

class ReportViewWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ReportViewWidget(QWidget *parent = 0);
	~ReportViewWidget();

private:
	Ui::ReportViewWidget *ui;
};

#endif // REPORTVIEWWIDGET_H
