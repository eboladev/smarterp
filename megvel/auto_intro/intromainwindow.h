#ifndef INTROMAINWINDOW_H
#define INTROMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class IntroMainWindow;
}

class IntroMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit IntroMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~IntroMainWindow();

private:
	Ui::IntroMainWindow *ui;
	QSqlDatabase db;
};

#endif // INTROMAINWINDOW_H
