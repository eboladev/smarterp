#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include <QtSql>
#include <QMainWindow>
namespace Ui {
class MainWindow;

}
class Employees;
class Lists;
class Leaves;

class Attendance;
class Timetable;
class Admin;
class MyAccount;
class Attendance2;

class HR_Leaves;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), bool demo = false);
	~MainWindow();
	void setDatabase(QSqlDatabase database);
	QSqlDatabase companyDb;
	bool payrollAccess;
	void setCompanyName(QString c);
private:
	Ui::MainWindow *ui;
	Employees  *m_employees;
	Lists   *m_lists;
	//Leaves  *m_leaves;
	Attendance *m_attendance;
	Timetable *m_timeTable;
	Admin *m_admin;
	MyAccount *m_acc;
	Attendance2 *att;

	HR_Leaves *m_leaves;

	QSqlDatabase db;
	int count;
	bool isDemo;
public slots:
	void logOff();
	void logIn();
private slots:
	void keepAlive();

	void pageChanged(QString newPage);
};

#endif // MAINWINDOW_H
