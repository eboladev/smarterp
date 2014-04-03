#include "updatermainwindow.h"
#include "ui_updatermainwindow.h"

UpdaterMainWindow::UpdaterMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::UpdaterMainWindow)
{
	ui->setupUi(this);
}

UpdaterMainWindow::~UpdaterMainWindow()
{
	delete ui;
}
