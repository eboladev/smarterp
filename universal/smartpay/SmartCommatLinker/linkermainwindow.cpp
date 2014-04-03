#include "linkermainwindow.h"
#include "ui_linkermainwindow.h"
#include "settingsdialog.h"
#include "odbctomysqlimport.h"
#include <QThread>
#include <QTimer>

LinkerMainWindow::LinkerMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::LinkerMainWindow)
{
	ui->setupUi(this);


	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(":images/Info-icon.png"));

	connect (trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		 this, SLOT(toggleVisibility(QSystemTrayIcon::ActivationReason)));

	trayIcon->show();


	QTimer *tmr = new QTimer(this);
	connect (tmr, SIGNAL(timeout()), SLOT(onTimer()));

	tmr->start(120000);

	on_cmdFetchData_clicked();
}

LinkerMainWindow::~LinkerMainWindow()
{
	delete ui;
}

void LinkerMainWindow::closeEvent(QCloseEvent *event)
{
	if (trayIcon->isVisible()) {
		hide();
		event->ignore();
	}
}

void LinkerMainWindow::on_actionSettings_triggered()
{
	SettingsDialog *d_sett = new SettingsDialog(this);
	d_sett->exec();
}


void LinkerMainWindow::linkerMessage(QString msg)
{
	QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvLog);
	it->setIcon(0, QIcon(":images/Info-icon.png"));
	it->setText(0, "Message");
	it->setText(1, msg);
	it->setText(2, QDate::currentDate().toString());
	it->setText(3, QTime::currentTime().toString());
}

void LinkerMainWindow::linkerError(QString err)
{
	QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvLog);
	it->setText(0, "Error");
	it->setIcon(0, QIcon(":images/Actions-window-close-icon.png"));
	it->setText(1, err);
	it->setText(2, QDate::currentDate().toString());
	it->setText(3, QTime::currentTime().toString());
}

void LinkerMainWindow::on_actionE_xit_triggered()
{
	qApp->quit();
}


#include "aboutdialog.h"
void LinkerMainWindow::on_actionAbout_Smart_Commat_Linker_triggered()
{
	AboutDialog d(this);
	d.exec();
}

void LinkerMainWindow::toggleVisibility(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::DoubleClick) {
		this->setVisible(!this->isVisible());
	}
}

void LinkerMainWindow::on_cmdFetchData_clicked()
{
	QThread *thread = new QThread;
	linker = new ODBCToMysqlImport();
	connect (linker, SIGNAL(message(QString)), SLOT(linkerMessage(QString)));
	connect (linker, SIGNAL(error(QString)), SLOT(linkerError(QString)));
	connect(thread, SIGNAL(started()), linker, SLOT(process()));
	connect(linker, SIGNAL(finished()), thread, SLOT(quit()));
	connect(linker, SIGNAL(finished()), linker, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	linker->moveToThread(thread);
	thread->start();
}

void LinkerMainWindow::onTimer()
{
	//    int minute = QTime::currentTime().minute();
	//    int second = QTime::currentTime().second();

	//    if (minute == 0 && second == 0)
	//        on_cmdFetchData_clicked();

	//    if (minute == 15 && second == 0)
	//        on_cmdFetchData_clicked();

	//    if (minute == 30 && second == 0)
	//        on_cmdFetchData_clicked();

	//    if (minute == 45 && second == 0)
	on_cmdFetchData_clicked();
}
