#ifndef COL_TRANSACTIONS_H
#define COL_TRANSACTIONS_H

#include <QMainWindow>

namespace Ui {
class col_transactions;
}

class col_transactions : public QMainWindow
{
	Q_OBJECT

public:
	explicit col_transactions(QWidget *parent = 0);
	~col_transactions();

private:
	Ui::col_transactions *ui;
};

#endif // COL_TRANSACTIONS_H
