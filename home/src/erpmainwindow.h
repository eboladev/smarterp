#ifndef ERPMAINWINDOW_H
#define ERPMAINWINDOW_H

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include <QtSql>
#include <QTcpSocket>
#include <QTimer>
#include <QMainWindow>
#include <QLabel>

namespace Ui {
class ERPMainWindow;
}


class WelcomeScreen;

class ERPMainWindow : public QMainWindow
{
	Q_OBJECT
protected:
	void closeEvent(QCloseEvent *evt);
public:
	QString projectName;
	QString databaseName;
	explicit ERPMainWindow(QWidget *parent = 0, QString pName = "megvel", QString dbName = "cartons",
			       QString user_id = QString()
			, QSqlDatabase database = QSqlDatabase()
			);
	~ERPMainWindow();
	void init();

signals:
	void emit_logOff();
public slots:
	void userChanged(QString newUser);
private:
	Ui::ERPMainWindow *ui;

	WelcomeScreen *m_fancyWelcomeScreen;
	int tabs;
	QSqlDatabase db;
	QMap<int, QMainWindow *> tabWindows;
	QList<QMainWindow *> sectionWindows;

	QLabel *w_dbStatusLabel;
	QLabel *w_timeLabel;
	QLabel *w_currentUserLabel;
	QLabel *w_notificationsLabel;

	QTcpSocket *updateSocket;

	QTimer *dbTimer;
	QSqlQuery secondQU;

	QString userID;
private slots:
	void addFancyWidgets();
	void addNewTab(QMainWindow *tab);
	void logOff();

	void tabChanged(int i);
	void socketReadyRead();
	void socketConnected();
	void secondTimeOut();


};

#endif // ERPMAINWINDOW_H
