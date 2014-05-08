#ifndef SAMAINWINDOW_H
#define SAMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class SaMainWindow;
}

class SaMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SaMainWindow(QWidget *parent = 0);
	~SaMainWindow();

private:
	Ui::SaMainWindow *ui;
	QSqlDatabase db;
};

#endif // SAMAINWINDOW_H
