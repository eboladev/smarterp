#ifndef CHEQUESMW_H
#define CHEQUESMW_H

#include <QMainWindow>

namespace Ui {
class ChequesMW;
}

class ChequesMW : public QMainWindow
{
	Q_OBJECT

public:
	explicit ChequesMW(QWidget *parent = 0);
	~ChequesMW();

private:
	Ui::ChequesMW *ui;
};

#endif // CHEQUESMW_H
