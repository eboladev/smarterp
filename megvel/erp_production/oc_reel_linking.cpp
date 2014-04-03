#include "oc_reel_linking.h"
#include "ui_oc_reel_linking.h"

OC_Reel_Linking::OC_Reel_Linking(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::OC_Reel_Linking)
{
    ui->setupUi(this);
    db = database;
}

OC_Reel_Linking::~OC_Reel_Linking()
{
    delete ui;
}
