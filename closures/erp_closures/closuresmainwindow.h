#ifndef CLOSURESMAINWINDOW_H
#define CLOSURESMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

#include "crm/crmmainwindow.h"
#include "production/productionmw.h"

namespace Ui {
class ClosuresMainWindow;
}

class ClosuresMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit ClosuresMainWindow(QWidget *parent = 0, QSqlDatabase database =
			QSqlDatabase());
	~ClosuresMainWindow();

private:
	Ui::ClosuresMainWindow *ui;
	QSqlDatabase db;

	CRMMainWindow *crm_mw;
	ProductionMW *prod_mw;
};

#endif // CLOSURESMAINWINDOW_H
