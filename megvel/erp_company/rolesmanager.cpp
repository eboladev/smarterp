#include "rolesmanager.h"
#include "ui_rolesmanager.h"
#include "datapublics.h"
RolesManager::RolesManager(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::RolesManager)
{
    ui->setupUi(this);
    db = database;
    reloadGroups();
}

RolesManager::~RolesManager()
{
    delete ui;
}

void RolesManager::reloadGroups()
{
    groupModel = new QSqlQueryModel(this);
    groupModel->setQuery("SELECT * FROM rolegroups", db);
    ui->lstGroups->setModel(groupModel);
    ui->lstGroups->setColumnHidden(0, true);
    ui->lstGroups->setAlternatingRowColors(true);
    ui->lstGroups->setHeaderHidden(true);
}

void RolesManager::reloadRoles()
{
    roleModel = new QSqlQueryModel(this);
    roleModel->setQuery("SELECT * FROM roles WHERE RoleGroupID = '" + groupID + "'", db);
    ui->lstRoles->setModel(roleModel);
    ui->lstRoles->setColumnHidden(0, true);
    ui->lstRoles->setColumnHidden(1, true);
    ui->lstRoles->setHeaderHidden(true);
}

void RolesManager::on_lstGroups_clicked(const QModelIndex &index)
{
    groupID = groupModel->record(index.row()).value(0).toString();
    reloadRoles();
}

void RolesManager::on_cmdNewRole_clicked()
{
    if (groupID == "") {
        DataPublics::showWarning("Select a group");
        return;
    }
    QString newRole = "";
    newRole = QInputDialog::getText(this, "New Role", "Enter the name for the new role");
    if (newRole != "") {
        DataPublics::ExecuteQuery(tr("INSERT INTO roles (RoleGroupID, RoleName) VALUES ('%1', '%2')")
                                  .arg(groupID, newRole), db);
    }
    reloadRoles();
}
