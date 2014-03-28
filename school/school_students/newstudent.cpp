#include "newstudent.h"
#include "ui_newstudent.h"

#include "newstudentwizard.h"

NewStudent::NewStudent(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::NewStudent)
{
    ui->setupUi(this);
    db = database;
}

NewStudent::~NewStudent()
{
    delete ui;
}

void NewStudent::on_cmdFreshStudent_clicked()
{
    NewStudentWizard *wiz = new NewStudentWizard(this);
    wiz->exec();
}
