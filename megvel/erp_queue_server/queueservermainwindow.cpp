#include "queueservermainwindow.h"
#include "ui_queueservermainwindow.h"

QueueServerMW::QueueServerMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QueueServerMainWindow)
{
    ui->setupUi(this);
    lbl_statusConnectivity = new QLabel(ui->statusBar);
    ui->statusBar->addWidget(lbl_statusConnectivity);
    updateConnectivity();
}

QueueServerMW::~QueueServerMW()
{
    delete ui;
}

void QueueServerMW::updateConnectivity()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        lbl_statusConnectivity->setText("Connected to mysql://" + db.hostName() + ":" + QString::number(db.port()));
    } else {
        lbl_statusConnectivity->setText("Database not connected. Reconnecting...");
        db.open();
    }
}
