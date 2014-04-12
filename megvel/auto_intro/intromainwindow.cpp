#include "intromainwindow.h"
#include "ui_intromainwindow.h"

IntroMainWindow::IntroMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent), db(database),
	ui(new Ui::IntroMainWindow)
{
	ui->setupUi(this);
}

IntroMainWindow::~IntroMainWindow()
{
	delete ui;
}
