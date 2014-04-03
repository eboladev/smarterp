#include "mainwindow.h"
#include "../zchat/ui_mainwindow.h"

#include "chatwindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>
MainWindow::MainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setCentralWidget(ui->mdiArea);
	db = database;
	if (db.isOpen()) {
		QSqlQuery qu = db.exec("SELECT * FROM users");
		while (qu.next()) {
			QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstBuddies);
			it->setText(0, qu.record().value("FullName").toString());
			it->setText(99, qu.record().value("UserID").toString());
			it->setText(100, qu.record().value("UserName").toString());
		}
	}
	updateBuddies();
	buddyTimer = new QTimer(this);
	connect (buddyTimer, SIGNAL(timeout()), SLOT(updateBuddies()));
	buddyTimer->start(5000);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updateBuddies()
{
	QString tmpFileName = qApp->applicationDirPath() + QDir::separator() + "~tmpcurrentuser.dat";
	QFile fil(tmpFileName);
	if (!fil.exists()) {
		//Cannot determine userid
		return;
	} else {
		if (fil.open(QIODevice::ReadOnly)) {
			userID = fil.readAll();
			db.exec(tr("UPDATE users SET LastChatTime = '%1' WHERE UserID = '%2'")
				.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), userID));
		} else {
			//cannot determine userid
			return;
		}
	}

	for (int i = 0; i < ui->lstBuddies->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->lstBuddies->invisibleRootItem()->child(i);
		QString this_userID = it->text(99);
		QSqlQuery qu = db.exec("SELECT * FROM users WHERE UserID = '" + this_userID + "'");
		qu.first();
		QString lastChat = qu.record().value("LastChatTime").toString();
		if (lastChat == "")
			lastChat = "1999-12-31 23:59:59";

		QDateTime d_lastChat = QDateTime::fromString(lastChat, "yyyy-MM-dd hh:mm:ss");
		if (QDateTime::currentDateTime().addSecs(-15) > d_lastChat) {
			//User Offline
			it->setIcon(0, QIcon(":/images/images/red-flag.png"));
		} else {
			//User Online
			it->setIcon(0, QIcon(":/images/images/green-flag.png"));
		}
	}
}

void MainWindow::on_lstBuddies_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column);

	for (int i = 0; i < ui->mdiArea->subWindowList().count(); i++) {
		if (ui->mdiArea->subWindowList().at(i)->windowTitle() == ("Chat With " + item->text(0))) {
			//Chat window already exists
			return;
		}
	}

	QString this_userID = item->text(99);
	ChatWindow *dg = new ChatWindow(this, db);
	dg->setWindowTitle("Chat With " + item->text(0));
	dg->recepient = this_userID;
	dg->sender = userID;

	ui->mdiArea->addSubWindow(dg);
	dg->show();
}
