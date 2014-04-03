#ifndef DISPATCHMAINWINDOW_H
#define DISPATCHMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class DispatchMainWindow;
}

class DispatchMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit DispatchMainWindow(QWidget *parent = 0
			, QSqlDatabase database =
			QSqlDatabase()
			);
	~DispatchMainWindow();
public slots:
	void reloadDispatch();
private slots:
	void on_trvDispatch_doubleClicked(const QModelIndex &index);

	void on_pushButton_2_clicked();

	void on_cmdNewDispatch_clicked();

	void on_cmdSearchPastEntries_clicked();

private:
	Ui::DispatchMainWindow *ui;
	QSqlDatabase db;
};

#endif // DISPATCHMAINWINDOW_H
