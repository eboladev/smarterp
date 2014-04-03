#ifndef QCMAINWINDOW_H
#define QCMAINWINDOW_H

#include <QMainWindow>

#include "datapublics.h"
namespace Ui {
class QcMainWindow;
}

class QcMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit QcMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~QcMainWindow();

private slots:
	void on_treeView_doubleClicked(const QModelIndex &index);

	void on_cmdShowOcs_clicked();
	void alive();
	void on_trvQcData_doubleClicked(const QModelIndex &index);

private:
	QTimer *aliveTimer;
	Ui::QcMainWindow *ui;
	QSqlDatabase db;
	void reload();
};

#endif // QCMAINWINDOW_H
