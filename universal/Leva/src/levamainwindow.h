#ifndef LEVAMAINWINDOW_H
#define LEVAMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

#include "levaconnectionwindow.h"
#include "tableeditor.h"

namespace Ui {
class LevaMainWindow;
}

class LevaMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit LevaMainWindow(QWidget *parent = 0,
				QSqlDatabase database=QSqlDatabase());
	~LevaMainWindow();
private:
	Ui::LevaMainWindow *ui;
	QSqlDatabase db;



private slots:
	void addConnection(QString serverName, QString userName, QString password, QString dbName="mysql", int port=3306);
	void on_actionNew_Connection_triggered();
};

#endif // LEVAMAINWINDOW_H
