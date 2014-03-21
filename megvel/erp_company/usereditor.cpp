#include "usereditor.h"
#include "ui_usereditor.h"
#include <QMessageBox>
#include "datapublics.h"
UserEditor::UserEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::UserEditor)
{
    ui->setupUi(this);
    db = database;

    ui->calStartDate->setDate(QDate::currentDate().addDays(-7));
    ui->calEndDate->setDate(QDate::currentDate());
}

UserEditor::~UserEditor()
{
    delete ui;
}

void UserEditor::edit()
{
    isEditing = true;
    QSqlQuery qu = db.exec("SELECT * FROM users WHERE UserID = '" + currentID + "'");
    if (!qu.lastError().isValid()) {
        qu.next();
        ui->txtFullName->setText(qu.record().value("FullName").toString());
        ui->txtUserName->setText(qu.record().value("UserName").toString());
        loadRoles();
        loadAuditTrail();
        loadPlugins();
    } else {
        QMessageBox::warning(this, "Error", qu.lastError().text());
    }
}

void UserEditor::addNew()
{
    ui->tabWidget->setVisible(false);
    ui->txtPassword->setEnabled(false);
    ui->txtConfirmPassword->setEnabled(false);
    ui->cmdSetPassword->setEnabled(false);
    ui->lstPlugins->setVisible(false);
    ui->lblPlugins->setVisible(false);
    this->resize(60,20);
    isEditing = false;
}

void UserEditor::saveRights()
{
}

void UserEditor::loadAuditTrail()
{
    QSqlQueryModel *trailModel = new QSqlQueryModel(this);
    trailModel->setQuery(tr("SELECT Date,Time,ComputerName,Section,Action FROM audittrail WHERE `UserID` = '%1' AND `Date` BETWEEN '%2' AND '%3'")
                         .arg(currentID, DataPublics::mysqlDate(ui->calStartDate->date()), DataPublics::mysqlDate(ui->calEndDate->date())), db);
    ui->trvAuditTrail->setModel(trailModel);
}

void UserEditor::loadRoles()
{
    QSqlQuery qu = db.exec("SELECT * FROM rolegroups");
    while (qu.next()) {
        QTreeWidgetItem *groupItem = new QTreeWidgetItem(ui->lstRights);
        groupItem->setText(0, qu.record().value("RoleGroupName").toString());
        groupItem->setText(99, qu.record().value("RoleGroupID").toString());
        loadRoleChildren(groupItem);
    }
    ui->lstRights->resizeColumnToContents(0);
}

void UserEditor::loadRoleChildren(QTreeWidgetItem *groupItem)
{
    groupItem->takeChildren();
    QSqlQuery roleQu = db.exec("SELECT * FROM roles WHERE RoleGroupID = '" + groupItem->text(99) + "'");
    while (roleQu.next()) {
        QTreeWidgetItem *roleItem = new QTreeWidgetItem(groupItem);
        roleItem->setText(0, roleQu.record().value("RoleName").toString());
        roleItem->setText(97, roleQu.record().value("RoleID").toString());
        if (DataPublics::checkUserAccess(currentID, roleQu.record().value("RoleName").toString(), db)) {
            //roleItem->setText(1, "Allowed");
            roleItem->setBackgroundColor(1, Qt::green);
            roleItem->setText(2, "Double click to revoke access");
        } else {
            roleItem->setBackgroundColor(1, Qt::red);
            roleItem->setText(2, "Double click to give access");
        }
        roleItem->setText(98, "role");
    }
    groupItem->setExpanded(true);
    ui->lstRights->resizeColumnToContents(0);
}

void UserEditor::on_cmdLoadAuditTrail_clicked()
{
    loadAuditTrail();
}

void UserEditor::on_cmdSetPassword_clicked()
{
    if (ui->txtPassword->text().length() < 5) {
        DataPublics::showWarning("The password has to be at least 4 characters long.");
        return;
    }
    if (ui->txtPassword->text() != ui->txtConfirmPassword->text()) {
        DataPublics::showWarning("Please enter matching passwords.");
        return;
    }
    //ALL OK
    QString err;
    if (!DataPublics::ExecuteQuery(tr("UPDATE users SET `Password` = '%1' WHERE `UserID` = '%2'")
                                   .arg(ui->txtPassword->text(), currentID)
                                   , db, err)) {
        DataPublics::showWarning("<h3>Database Error</h3>" + db.lastError().text());
    } else {
        DataPublics::showInformation("Password Changed");
    }
}

void UserEditor::on_lstRights_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
}

void UserEditor::on_lstRights_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if (item->text(98) == "role") {
        QString userID = currentID;
        QString roleID = item->text(97);
        if (item->backgroundColor(1) == Qt::red) {
            //Enable Access
            db.exec(tr("INSERT INTO userroles (UserID, RoleID, DateAssigned) VALUES ('%1', '%2', Now())")
                    .arg(userID, roleID));
            loadRoleChildren(item->parent());
        } else {
            //Disable Access
            db.exec(tr("DELETE FROM userroles WHERE UserID = '%1' AND RoleID = '%2'")
                    .arg(userID, roleID));
            loadRoleChildren(item->parent());
        }
    }

}

void UserEditor::on_cmdSave_clicked()
{
    QString query = "SELECT NOW()";
    if (isEditing) {
        //Edit
        query = tr("UPDATE users SET UserName = '%1', FullName = '%2' WHERE UserID = '%3'")
                .arg(ui->txtUserName->text(), ui->txtFullName->text(), currentID);
    } else {
        //Add New
        query  = tr("INSERT INTO users (UserName, FullName, Password) VALUES ('%1','%2','123456')")
                .arg(ui->txtUserName->text(), ui->txtFullName->text());
    }
    db.exec(query);
    if (db.lastError().isValid()) {
        //Error
        DataPublics::showWarning("<h3>Database Error</h3>There was an error while saving the user details:<br/>" + db.lastError().text() + "<br/>Please try again");

    } else {
        //No Error
        DataPublics::showInformation("User details successfully saved");
        if (isEditing)
            savePlugins();
        this->accept();
    }
}

void UserEditor::on_cmdDelete_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this user?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        QString query = tr("DELETE FROM users WHERE UserID = '%1'")
                .arg(currentID);
        db.exec(query);
        if (db.lastError().isValid()) {
            //Error
            DataPublics::showWarning("<h3>Database Error</h3>There was an error while deleting the user details:<br/>" + db.lastError().text() + "<br/>Please try again");
        } else {
            //No Error
            DataPublics::showInformation("User details successfully deleted");
            this->accept();
        }
    }
}

void UserEditor::on_cmdClose_clicked()
{
    this->reject();
}

void UserEditor::loadPlugins()
{
    QSqlQuery pluginQuery = db.exec("SELECT * FROM plugins");
    while (pluginQuery.next()) {
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstPlugins);
        it->setText(0, pluginQuery.record().value("PluginName").toString());
        it->setText(5, pluginQuery.record().value("PluginID").toString());
        it->setCheckState(0, Qt::Unchecked);
        QSqlQuery checker = db.exec(tr("SELECT * FROM pluginusers WHERE PluginID = '%1' and UserID = '%2'")
                                    .arg(pluginQuery.record().value("PluginID").toString(), currentID));
        if (checker.size() > 0)
            it->setCheckState(0, Qt::Checked);
    }
}

void UserEditor::savePlugins()
{
    db.exec(tr("DELETE FROM pluginusers WHERE UserID = '%1'").arg(currentID));
    for (int i = 0; i < ui->lstPlugins->invisibleRootItem()->childCount(); i++) {
        QTreeWidgetItem *it = ui->lstPlugins->invisibleRootItem()->child(i);
        if (it->checkState(0) == Qt::Checked) {
            db.exec(tr("INSERT INTO pluginusers (PluginID, UserID) VALUES ('%1', '%2')")
                    .arg(it->text(5), currentID));
        }
    }
}
