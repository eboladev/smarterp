#ifndef FINISHINGMAINWINDOW_H
#define FINISHINGMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class FinishingMainWindow;
}

class FinishingMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit FinishingMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~FinishingMainWindow();

private:
	Ui::FinishingMainWindow *ui;
	QSqlDatabase db;
};

#endif // FINISHINGMAINWINDOW_H
