#include "bdmainwindow.h"
#include "ui_bdmainwindow.h"

#include <QMessageBox>
#include "preferencesdialog.h"

BDMainWindow::BDMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::BDMainWindow)
{
	ui->setupUi(this);
	isDownloading = false;
}

BDMainWindow::~BDMainWindow()
{
	delete ui;
}

void BDMainWindow::on_actionAbout_Bd_triggered()
{
	QMessageBox::about(this, "About BD", "(c)2014 Free Software (k) Ltd");
}

void BDMainWindow::on_actionExit_triggered()
{
	//stop download
	if (isDownloading) {
		on_cmdDownload_clicked();
	}
	//
	qApp->quit();
}

void BDMainWindow::on_actionAbout_Qt_triggered()
{
	QMessageBox::aboutQt(this, "About Qt");
}

void BDMainWindow::on_actionPreferences_triggered()
{
	PreferencesDialog *pref = new PreferencesDialog(this);
	pref->exec();
}

void BDMainWindow::on_cmdDownload_clicked()
{
	if (isDownloading) {
		//Stop download

		ui->cmdDownload->setText("Start Download");
		isDownloading = false;
	} else {
		//Stop download

		ui->cmdDownload->setText("Stop Download");
		isDownloading = true;
	}
}
