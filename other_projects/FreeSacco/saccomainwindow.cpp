#include "saccomainwindow.h"
#include "ui_saccomainwindow.h"
#include "datapublics.h"
#include "src/membermanager.h"
#include "src/companymanager.h"
SaccoMainWindow::SaccoMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SaccoMainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL", "free_sacco");
    db.setHostName("197.254.15.122");
    db.setPassword("pledge");
    db.setUserName("root");
    db.setDatabaseName("freesacco");

    if (!db.open()) {
        DataPublics::showWarning("Database Error\n\n" + db.lastError().text());

        ui->menuBar->setEnabled(false);

        ui->membersToolBar->setEnabled(false);
        ui->loansToolBar->setEnabled(false);
        ui->adminToolBar->setEnabled(false);
    } else {

    }
}

SaccoMainWindow::~SaccoMainWindow()
{
    delete ui;
}

void SaccoMainWindow::on_actionMember_Manager_triggered()
{
    MemberManager *man = new MemberManager(this);
    addSubWindow(man);
    man->setWindowState(Qt::WindowMaximized);
}

void SaccoMainWindow::addSubWindow(QMainWindow *sub)
{
    ui->mdiArea->addSubWindow(sub);
    sub->setVisible(true);
}

void SaccoMainWindow::on_actionMember_Companies_triggered()
{
    CompanyManager *man = new CompanyManager(this);
    addSubWindow(man);
}
