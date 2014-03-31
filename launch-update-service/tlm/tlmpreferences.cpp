#include "tlmpreferences.h"
#include "ui_tlmpreferences.h"

TLMPreferences::TLMPreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TLMPreferences)
{
    ui->setupUi(this);
}

TLMPreferences::~TLMPreferences()
{
    delete ui;
}

void TLMPreferences::on_cmdSave_clicked()
{
    this->accept();
}
