#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QTimer>
#include "datapublics.h"

ChatWindow::ChatWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::ChatWindow)
{
	ui->setupUi(this);
	db = database;

	messageTimer = new QTimer(this);
	connect (messageTimer, SIGNAL(timeout()), SLOT(updateMessages()));
	messageTimer->start(2000);


#ifdef Q_OS_LINUX
	// sleep(0.5);
#endif
	updateMessages();
}

ChatWindow::~ChatWindow()
{
	delete ui;
}

void ChatWindow::on_cmdSendMessage_clicked()
{
	db.exec(QString("INSERT INTO chatmessages (SenderID, Recepient, DateSent, Message) VALUES("
			"'%1', '%2', NOW(), '%3')")
		.arg(sender, recepient, ui->txtMessage->text()));
	if (db.lastError().isValid()) {
		QMessageBox::critical(this, "Database Error", db.lastError().text());
	} else {
		ui->txtMessage->clear();
		updateMessages();
	}
}

void ChatWindow::updateMessages()
{
	QSqlQuery qu = db.exec(QString("SELECT * FROM chatmessages WHERE (SenderID = '%1'"
				       " AND Recepient = '%2') "
				       " OR (Recepient = '%1' "
				       " AND SenderID = '%2') LIMIT 0, 200"
				       ).arg(sender, recepient)
			       );
	if (qu.lastError().isValid()) {
		QMessageBox::critical(this, "Database Error", qu.lastError().text());
	} else {
		ui->txtHistory->clear();
		while (qu.next()) {
			QSqlRecord rec = qu.record();
			QString userName = DataPublics::getDbValue("SELECT * FROM users WHERE userID = '" + rec.value("senderID").toString()
								   + "'", db, "FullName").toString();

			QString msg_time = rec.value("DateSent").toDateTime().toString("dd-MMM-yy hh:mm");
			QString nameColor = "\"blue\"";
			if (rec.value("senderID").toString() == sender)
				nameColor = "\"red\"";
			QString append = "<b>[" + msg_time + "] <font color=" + nameColor + ">" + userName + "</font>:</b> " + rec.value("Message").toString();
			ui->txtHistory->append(append);
		}
	}
}

void ChatWindow::on_txtMessage_returnPressed()
{
	on_cmdSendMessage_clicked();
}
