#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

//
// Prototypes
//
class QMdiArea;
class QAction;
class ReportHandler;
class QMenu;
class QString;
class QWorkspace;
class QTreeWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~MainWindow();

private:
	Ui::MainWindow *ui;
	int dbTimerId;

	QAction * fileExitAction;

	ReportHandler * handler;

	QMenu *windowMenu;
	QDockWidget *_fieldDock;
	QMdiArea * ws;
	QString _dbName;
	QString _serverName;
	QString _userName;
	QString _password;
	QString _reportName;

	QSqlDatabase db;
	QSqlDatabase fieldDb;

	QWidget *currentSubWindow();

	QTimer *secondTimer;
	QString rName;
public slots:
	virtual void setCaption();
	virtual void openReportFile(const QString &);
	void dbConnected();
	void reportChanged(QString newReportName);

	void timeOut();

protected:
	virtual void closeEvent(QCloseEvent*);
	virtual void timerEvent(QTimerEvent*);

private slots:
	void appExit();
	void sPrepareWindowMenu();
	void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
	void on_actionAuto_Report_triggered();
	void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
