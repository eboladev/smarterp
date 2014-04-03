#ifndef PRODUCTIONMAINWINDOW_H
#define PRODUCTIONMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class ProductionMainWindow;
}

class ProductionMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit ProductionMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ProductionMainWindow();

private:
	Ui::ProductionMainWindow *ui;
	QSqlDatabase db;
};

#endif // PRODUCTIONMAINWINDOW_H
