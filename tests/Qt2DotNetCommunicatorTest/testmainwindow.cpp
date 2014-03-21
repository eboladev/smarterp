#include "testmainwindow.h"
#include "ui_testmainwindow.h"

TestMainWindow::TestMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestMainWindow)
{
    ui->setupUi(this);
    lgm = new LGMClientClass(this);
    connect(lgm, SIGNAL(status(QString)), ui->lblStatus, SLOT(setText(QString)));
    connect(lgm, SIGNAL(serverResponse(QString)), ui->txtResponse, SLOT(setText(QString)));
    lgm->startLgmClient();
}

TestMainWindow::~TestMainWindow()
{
    delete ui;
}

void TestMainWindow::on_cmdSend_clicked()
{
    lgm->sendMessageToServer(ui->txtCommand->text());
}
