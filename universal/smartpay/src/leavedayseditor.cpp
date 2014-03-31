#include "leavedayseditor.h"
#include "ui_leavedayseditor.h"

LeaveDaysEditor::LeaveDaysEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaveDaysEditor)
{
    ui->setupUi(this);
}

LeaveDaysEditor::~LeaveDaysEditor()
{
    delete ui;
}
