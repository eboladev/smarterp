#ifndef CLEARHISTORY_H
#define CLEARHISTORY_H

#include <QDialog>

namespace Ui {
class ClearHistory;
}

class ClearHistory : public QDialog
{
	Q_OBJECT

public:
	explicit ClearHistory(QWidget *parent = 0);
	~ClearHistory();

private:
	Ui::ClearHistory *ui;
};

#endif // CLEARHISTORY_H
