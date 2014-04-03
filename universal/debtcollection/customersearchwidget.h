#ifndef CUSTOMERSEARCHWIDGET_H
#define CUSTOMERSEARCHWIDGET_H

#include <QWidget>

namespace Ui {
class customerSearchWidget;
}

class customerSearchWidget : public QWidget
{
	Q_OBJECT

public:
	explicit customerSearchWidget(QWidget *parent = 0);
	~customerSearchWidget();

private:
	Ui::customerSearchWidget *ui;
};

#endif // CUSTOMERSEARCHWIDGET_H
