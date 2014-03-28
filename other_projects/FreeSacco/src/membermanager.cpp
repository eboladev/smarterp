#include "membermanager.h"
#include "ui_membermanager.h"

#include "membereditordialog.h"
#include "startnewmemberdialog.h"
MemberManager::MemberManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MemberManager)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("free_sacco");
    reloadMemberList();
}

MemberManager::~MemberManager()
{
    delete ui;
}

void MemberManager::on_cmdNewMember_clicked()
{
    StartNewMemberDialog *ed = new StartNewMemberDialog(this);
    if (ed->exec() == QDialog::Accepted) {
        reloadMemberList();
    }
}

void MemberManager::reloadMemberList()
{
    members_model = new QSqlQueryModel(this);
    members_model->setQuery("SELECT member_id, member_no as 'No.', full_name as 'Name' FROM fs_members", db);
    ui->tblMembers->setModel(members_model);
    ui->tblMembers->setColumnHidden(0, true);
    ui->tblMembers->resizeColumnsToContents();
    ui->tblMembers->horizontalHeader()->setStretchLastSection(true);
    ui->tblMembers->resizeRowsToContents();
}
