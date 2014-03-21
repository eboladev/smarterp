#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"

#include "employees.h"
#include "lists.h"
#include "leaves.h"
#include "payroll.h"
#include "attendance.h"
#include "timetable.h"
#include "admin.h"
#include "payslips.h"

#include "userlogin.h"
#include "myaccount.h"
#include "datapublics.h"
MainWindow::MainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Utils::StyleHelper::setBaseColor(QColor(128,128,128));
    db = database;

    logIn();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDatabase(QSqlDatabase database)
{
    db = database;
}

void MainWindow::logOff()
{
 /*Not Implemented */
}

void MainWindow::logIn()
{
    m_employees = new Employees(this, db);
    m_lists = new Lists(this, db);
    m_leaves = new Leaves(this, db);
    m_attendance = new Attendance(this, db);
    m_timeTable = new Timetable(this, db);
    m_payroll = new Payroll(this, db);
    m_acc = new MyAccount(this, db);
    m_payslips = new Payslips(this, db);

    count = 0;
        ui->widget->insertTab(m_employees);
        count++;
        ui->widget->insertTab(m_lists);
        count++;
            //m_employees->hideHR();
            //m_employees->hideFinance();
            ui->widget->insertTab(m_leaves);
            count++;
            ui->widget->insertTab(m_timeTable);
            count++;
            ui->widget->insertTab(m_attendance);
            count++;
            ui->widget->insertTab(m_payroll);
            count++;
            ui->widget->insertTab(m_payslips);
        count++;
}
