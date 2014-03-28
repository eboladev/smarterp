#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include <QtSql>
#include <QtNetwork>
#include <QMainWindow>
namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public QMainWindow
{
	Q_OBJECT

public:
	explicit WelcomeScreen(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
			       QString userID = QString());
	~WelcomeScreen();
	void findPlugins();
	bool checkUserInPlugin(QString pluginName, QString userID);
	QString projectName;
private:
	Ui::WelcomeScreen *ui;
	void emitPlugin(QObject *plugin);
	QSqlDatabase db;
	QTcpSocket *sock;
	QString socketData;
	QString m_userID;
signals:
	void newPlugin(QMainWindow *w);
	void logOff();
	void dbState(QString);
	void userLoggedIn(QString);
private slots:
	void on_cmdExit_clicked();
	void on_cmdLogOff_clicked();
	void on_cmdCheckForUpdates_clicked();

	void pluginUpdateAction(int pID, QString action);

	void checkForUpdates();
	void readyRead();
	void socketStateChanged(QAbstractSocket::SocketState newState);
};

#endif // WELCOMESCREEN_H
