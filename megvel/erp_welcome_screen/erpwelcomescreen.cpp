#include "erpwelcomescreen.h"
#include "ui_erpwelcomescreen.h"

ERPWelcomeScreen::ERPWelcomeScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ERPWelcomeScreen)
{
    ui->setupUi(this);
}

ERPWelcomeScreen::~ERPWelcomeScreen()
{
    delete ui;
}
