#include "crmmainwindow.h"
#include "ui_crmmainwindow.h"

CRMMainWindow::CRMMainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::CRMMainWindow)
{
    ui->setupUi(this);
    db = database;
}

CRMMainWindow::~CRMMainWindow()
{
    delete ui;
}

