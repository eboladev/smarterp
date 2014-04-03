#ifndef CUSTOMDEDUCTIONS_H
#define CUSTOMDEDUCTIONS_H

#include <QMainWindow>

namespace Ui {
class CustomDeductions;
}

class CustomDeductions : public QMainWindow
{
	Q_OBJECT

public:
	explicit CustomDeductions(QWidget *parent = 0);
	~CustomDeductions();

private:
	Ui::CustomDeductions *ui;
};

#endif // CUSTOMDEDUCTIONS_H
