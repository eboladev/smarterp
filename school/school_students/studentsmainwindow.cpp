#include "studentsmainwindow.h"
#include "ui_studentsmainwindow.h"
#include "utils/stylehelper.h"
#include "newstudent.h"

StudentsMainWindow::StudentsMainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::StudentsMainWindow)
{
    ui->setupUi(this);
    Utils::StyleHelper::setBaseColor(QColor(128,128,128));
    db = database;

    t_newStudent = new NewStudent(this);

    ui->widget->insertTab(t_newStudent);
}

StudentsMainWindow::~StudentsMainWindow()
{
    delete ui;
}
