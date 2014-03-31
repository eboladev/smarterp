#include "usmainwindow.h"
#include "ui_usmainwindow.h"

USMainWindow::USMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::USMainWindow)
{
    ui->setupUi(this);
}

USMainWindow::~USMainWindow()
{
    delete ui;
}
