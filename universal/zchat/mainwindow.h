#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>
#include <QDebug>
#include <QMainWindow>
#include <QTimer>
#include <QTreeWidget>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0
			, QSqlDatabase database = QSqlDatabase());
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QSqlDatabase db;
	QTimer *buddyTimer;
	QString userID;
private slots:
	void updateBuddies();
	void on_lstBuddies_itemDoubleClicked(QTreeWidgetItem *item, int column);
};

#endif // MAINWINDOW_H
