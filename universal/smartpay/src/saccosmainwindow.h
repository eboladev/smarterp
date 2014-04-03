#ifndef SACCOSMAINWINDOW_H
#define SACCOSMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "publics.h"
namespace Ui {
class SaccosMainWindow;
}

class SaccosMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SaccosMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~SaccosMainWindow();

private slots:
	void on_cmdDelete_clicked();

	void on_actionNew_Entry_triggered();

	void on_cboMonths_currentIndexChanged(const QString &arg1);

	void on_actionRefresh_triggered();

private:
	Ui::SaccosMainWindow *ui;
	QSqlDatabase db;
};

#endif // SACCOSMAINWINDOW_H
