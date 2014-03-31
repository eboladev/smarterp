#include "newstudentwizard.h"
#include "ui_newstudentwizard.h"

NewStudentWizard::NewStudentWizard(QWidget *parent, QSqlDatabase database) :
    QWizard(parent),
    ui(new Ui::NewStudentWizard)
{
    ui->setupUi(this);
    db = database;
}

NewStudentWizard::~NewStudentWizard()
{
    delete ui;
}
