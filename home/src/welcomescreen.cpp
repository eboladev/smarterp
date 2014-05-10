#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include <QDir>
#include <QPluginLoader>
#include "interfaces.h"
#include "datapublics.h"
#include "userlogin.h"
//#include "threadedpluginupdater.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
WelcomeScreen::WelcomeScreen(QWidget *parent, QSqlDatabase database, QString userID) :
	QMainWindow(parent),
	ui(new Ui::WelcomeScreen)
{
	ui->setupUi(this);

	db = database;
	m_userID = userID;
	ui->cmdLogOff->setVisible(false);
	//    QTimer *tmr = new QTimer(this);
	//    connect (tmr, SIGNAL(timeout()), SLOT(checkForUpdates()));
	//    tmr->start(60000);
	//    checkForUpdates();
}

WelcomeScreen::~WelcomeScreen()
{
	delete ui;
}

void WelcomeScreen::findPlugins()
{
	QStringList loadedOnes;
	QString pluginPath = qApp->applicationDirPath() + QDir::separator() + "plugins";
	const QDir dir(pluginPath);

	QString userID = m_userID;
	//    UserLogin *uLogin = new UserLogin(this, db);
	//    if (uLogin->exec() == QDialog::Accepted) {
	//        userID = uLogin->userID;
	//        emit userLoggedIn(uLogin->userName);
	//    }
	//Load dynamic plugins
	foreach (QString fName, dir.entryList(QDir::Files)) {
		QPluginLoader loader(dir.absoluteFilePath(fName));
		loader.load();
		QObject *plugin = loader.instance();


		if (loader.isLoaded()) {
			//it->setText(0, tr("%1 (Dynamic Plugin)").arg(plugin->metaObject()->className()));
			MainWindowInterface *mW = qobject_cast<MainWindowInterface *>(plugin);
			if (mW->pluginName().length() > 0) {

				QTreeWidgetItem *it = new QTreeWidgetItem(ui->treeWidget);
				if (mW) {
					if (mW->pluginName() == "Automatic Introduction") {
						//emitPlugin(plugin);
					} else {
						if (!loadedOnes.contains(mW->pluginName())) {
							if (mW->projectName() == projectName || mW->projectName() == "universal") {

								//qDebug() << "PLUGIN " << mW->pluginName();
								it->setText(0, mW->pluginName());
								it->setText(1, mW->pluginVersion());
								it->setText(2, mW->releaseDate());
								it->setText(3, mW->pluginDescription());
								it->setText(4, mW->pluginAuthor());
								loadedOnes.append(mW->pluginName());
								QStringList sw = mW->subWindows();
								for (int s = 0; s < sw.count(); s++) {
									QString subWin = sw.at(s);
									QStringList s_details = subWin.split("\t");
									QTreeWidgetItem *sItem = new QTreeWidgetItem(it);
									for (int j = 0; j < s_details.count(); j++)
									{
										if (j == 0)
											sItem->setText(0, s_details.at(j));

										if (j == 1)
											sItem->setText(3, s_details.at(j));

										if (j == 2)
											sItem->setText(4, s_details.at(j));
									}
								}
							} else {
								it->setText(665, "Error");
							}
							if (checkUserInPlugin(mW->pluginName(), userID)) {
								//mW->setDatabase(db);
								emitPlugin(plugin);
								it->setText(5, "Latest version loaded");
								it->setText(666, "IDLE");
								//qDebug() << "Plugin allowed " << mW->pluginName();
							} else {
								/*Debug() << "Plugin not allowed " << mW->pluginName()
									    << " user ID: " << userID*/
									    ;
								it->setText(5, "Access Denied. Plugin Not Loaded");
							}
						} else {
							loader.unload();
							it->setText(665, "Error");
						}
					}

					if (it->text(665) == "Error") {
						ui->treeWidget->invisibleRootItem()->removeChild(it);
					}
				}
			}
		}
	}


	bool loadstatic = false;
	if (loadstatic) {
		foreach (QObject *plugin, QPluginLoader::staticInstances()) {
			//Found a static plugin
			QTreeWidgetItem *it = new QTreeWidgetItem(ui->treeWidget);
			it->setText(0, tr("%1 (Static Plugin)").arg(plugin->metaObject()->className()));

			emitPlugin(plugin);
		}
	}
	ui->treeWidget->resizeColumnToContents(0);
	ui->treeWidget->resizeColumnToContents(1);
	ui->treeWidget->resizeColumnToContents(2);
	ui->treeWidget->resizeColumnToContents(4);
	ui->treeWidget->resizeColumnToContents(5);
}
bool WelcomeScreen::checkUserInPlugin(QString pluginName, QString userID)
{
	QString sql = "SELECT * FROM `plugins` WHERE `PluginName` = '" + pluginName + "'";

	QSqlQuery qqq = db.exec("SELECT * FROM plugins");

	if (qqq.lastError().isValid()) {
		qDebug() << qqq.lastError().text();
	}

	while (qqq.next()) {
		qDebug() << qqq.record().value(0).toString();
	}

	QString pluginID = DataPublics::getDbValue(sql, db, "PluginID").toString();
	QSqlQuery qu = db.exec(tr("SELECT * FROM pluginusers WHERE UserID = '%1' AND PluginID = '%2'")
			       .arg(userID, pluginID));
	int cnt = 0;
	while (qu.next()) {
		cnt ++;
	}
	//qDebug() << userID << pluginID << cnt;
	return cnt > 0;
}

void WelcomeScreen::emitPlugin(QObject *plugin)
{
	MainWindowInterface *mW = qobject_cast<MainWindowInterface *>(plugin);
	if (mW) {
		emit newPlugin(mW->pluginMainWindow(0, db));
	}
}

void WelcomeScreen::on_cmdExit_clicked()
{
	qApp->exit(0);
}

void WelcomeScreen::on_cmdLogOff_clicked()
{
	emit logOff();
}

void WelcomeScreen::on_cmdCheckForUpdates_clicked()
{
	//    for (int i = 0; i < ui->treeWidget->invisibleRootItem()->childCount(); i++) {
	//        QTreeWidgetItem *it = ui->treeWidget->invisibleRootItem()->child(i);
	//        if (it->text(666) == "IDLE") {
	//            it->setText(5, "Ckecking for updates...");
	//            it->setText(666, "UPDATING");
	//            ThreadedPluginUpdater *thUpdater = new ThreadedPluginUpdater(this);
	//            thUpdater->setVars(it->text(0), i, it->text(1), it->text(2));
	//            connect (thUpdater, SIGNAL(currentAction(int,QString)), SLOT(pluginUpdateAction(int,QString)));
	//            thUpdater->start();
	//        }
	//    }
	//   checkForUpdates();
}

void WelcomeScreen::pluginUpdateAction(int pID, QString action)
{
	//qDebug() << "Action:" << pID << action;
	ui->treeWidget->invisibleRootItem()->child(pID)->setText(5, action);
}

void WelcomeScreen::checkForUpdates()
{
	//    qDebug() << "Starting update check";
	//    int idleCount = 0;
	//    for (int i = 0; i < ui->treeWidget->invisibleRootItem()->childCount(); i++) {
	//        QTreeWidgetItem *it = ui->treeWidget->invisibleRootItem()->child(i);
	//        if (it->text(666) == "IDLE") {
	//            idleCount  = idleCount + 1;
	//            it->setText(5, "Ckecking for updates...");
	//            it->setText(666, "UPDATING");
	//        }
	//    }
	//    socketData = "";
	//    if (idleCount > 0) {
	//        for (int i = 0; i < ui->treeWidget->invisibleRootItem()->childCount(); i++) {
	//            QTreeWidgetItem *it = ui->treeWidget->invisibleRootItem()->child(i);
	//            if (it->text(666) == "IDLE") {
	//                QString pluginName, version, buildDate;
	//                pluginName = it->text(0);
	//                version = it->text(1);
	//                buildDate = it->text(2);
	//                socketData = socketData + pluginName + "\t"
	//                        + version + "\t" + buildDate + "\n";
	//            }
	//        }
	//        sock = new QTcpSocket(this);
	//        connect (sock, SIGNAL(readyRead()), SLOT(readyRead()));
	//        connect (sock, SIGNAL(stateChanged(QAbstractSocket::SocketState)), SLOT(socketStateChanged(QAbstractSocket::SocketState)));
	//        sock->connectToHost("127.0.0.1", 8000);
	//    }
}

void WelcomeScreen::readyRead()
{
	//qDebug() << "Socket communication..." << sock->readAll();
}

void WelcomeScreen::socketStateChanged(QAbstractSocket::SocketState newState)
{
	if (newState == QAbstractSocket::ConnectedState) {
		sock->write(socketData.toUtf8());
		//qDebug() << "Plugin information sent...";
	} else if (newState == QAbstractSocket::HostLookupState) {

	}
}
