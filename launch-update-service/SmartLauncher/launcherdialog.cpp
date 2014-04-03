#include "launcherdialog.h"
#include "../SmartLauncher/ui_launcherdialog.h"
#include <QDateTime>
#include <QProcess>
#include <QDir>
#include <QDesktopServices>
#include <QDebug>
#include <QApplication>

LauncherDialog::LauncherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LauncherDialog)
{
    ui->setupUi(this);
    newLogEntry("Starting launcher...");

    UpdateService *serv = new UpdateService();
    connect (serv, SIGNAL(serviceStatus(QString)), SLOT(newLogEntry(QString)));
    connect (serv, SIGNAL(finished()), SLOT(startERP()));
    serv->connectToDb();
}

LauncherDialog::~LauncherDialog()
{
    delete ui;
}

void LauncherDialog::newLogEntry(QString s)
{
    ui->textBrowser->append(QDateTime::currentDateTime().toString("hh:mm:ss dd-MMM-yyyy") + " - " + s);
}

void LauncherDialog::startERP()
{

    QString erpname = "smarterp";
#ifdef Q_OS_WIN
    erpname = "SmartERP.exe";
#endif

#ifdef Q_OS_LINUX
    erpname = "smarterp";
#endif


    QProcess *myprocess = new QProcess(this);

    connect (myprocess, SIGNAL(finished(int)), SLOT(closeAll()));

    myprocess->start("SmartERP.exe");

}

void LauncherDialog::closeAll()
{
   this->close();
}
