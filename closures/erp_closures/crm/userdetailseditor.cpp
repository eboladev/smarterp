#include "userdetailseditor.h"
#include "ui_userdetailseditor.h"
#include <QtSql>
#include <QMessageBox>
UserDetailsEditor::UserDetailsEditor(QWidget *parent, bool IsAdding) :
    QDialog(parent),
    ui(new Ui::UserDetailsEditor)
{
    ui->setupUi(this);
    setIsAdding(IsAdding);
    fromNew = m_isAdding;
}

UserDetailsEditor::~UserDetailsEditor()
{
    delete ui;
}
bool UserDetailsEditor::isAdding() const
{
    return m_isAdding;
}

void UserDetailsEditor::setIsAdding(bool isAdding)
{
    m_isAdding = isAdding;
    ui->groupBox->setVisible(!m_isAdding);
}
QString UserDetailsEditor::currentID() const
{
    return m_currentID;
}

void UserDetailsEditor::setCurrentID(const QString &currentID)
{
//    m_currentID = currentID;
//    if (!fromNew) {
//        QSqlQuery qu = QSqlDatabase::database().exec("SELECT * FROM users WHERE user_id = '" + currentID() + "'");
//        if (qu.first()) {
//            ui->txtFullName->setText(qu.record().value("full_name").toString());
//        }
//    }
}



void UserDetailsEditor::on_cmdSave_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("closures");
    QString query = "";
    QString admin = "0";
    if (ui->chkAdminAccess->isChecked())
        admin = "1";

    if (isAdding()) {
        QString addQuery = "INSERT INTO users (login_name) VALUES ('" + ui->txtLoginName->text()  +"')";
        QSqlQuery qu = db.exec(addQuery);
        if (qu.lastError().isValid()) {
            QMessageBox::critical(this, "Error", "An error has occurred.\n\n" + qu.lastError().text());
            return;
        } else {
           setIsAdding(false);
           setCurrentID(qu.lastInsertId().toString());
        }
    }

    query = "";/*"UPDATE users SET "
            + "login_name = '" + ui->txtLoginName->text()
            + "' full_name = '" + ui->txtFullName->text()
            + "' password = '" + ui->txtPassword->text()
            + "' admin_access = '" + admin + "' WHERE user_id = '" + currentID() + "'";*/


    QSqlQuery qu = db.exec(query);
    if (qu.lastError().isValid()) {
        QMessageBox::critical(this, "Error", "An error has occurred.\n\n" + qu.lastError().text());
        return;
    } else {
        this->accept();
    }
}
