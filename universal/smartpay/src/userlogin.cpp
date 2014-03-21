#include "userlogin.h"
#include "ui_userlogin.h"

#include <QMessageBox>
#include "datapublics.h"

UserLogin::UserLogin(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::UserLogin)
{
    ui->setupUi(this);
    db = database;
    connect (ui->Cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect (ui->Login, SIGNAL(clicked()), SLOT(tryLogin()));
    DataPublics::loadQueryToComboBox("SELECT * FROM `smartpay-master`.companies", "CompanyName",
                                     db, ui->cboCompanies);

    ui->label_5->setVisible(false);
    ui->cboCompanies->setVisible(false);
}

UserLogin::~UserLogin()
{
    delete ui;
}

void UserLogin::tryLogin() {
    bool ok = false;
    payrollAccess = false;
    bool dbOk;
    dbOk = true;
   // QSqlQuery qu = db.exec("SELECT UserName, CompanyName, PayrollAccess, Password, DatabaseName FROM `smartpay-master`.vw_company_users WHERE UserName = '" + ui->UserName->text() + "' AND CompanyName = '" + ui->cboCompanies->currentText() + "' AND `Password` = PASSWORD('" + ui->Password->text() + "')");
     QSqlQuery qu = db.exec("SELECT UserName, CompanyName, PayrollAccess, Password, DatabaseName FROM `smartpay-master`.vw_company_users WHERE UserName = '" + ui->UserName->text() + "' AND `Password` = PASSWORD('" + ui->Password->text() + "')");

    if (qu.lastError().isValid()) {
        ok = false;
    } else {
        if (qu.size() < 1) {
            ok = false;
        } else {
            userID = DataPublics::getDbValue("SELECT * FROM users WHERE UserName = '" + ui->UserName->text() + "'", db, "UserID").toString();
            ok = true;
        }
    }
    if (!ok) {
        QMessageBox::critical(this, "Login Error", "Login failed.\nYou may have entered the wrong company information, or you may have selected a company for which you do not have access.\n\nDatabase Error\n" + qu.lastError().text());
    } else {
        this->accept();
    }
}






/* while (qu.next()) {
    QSqlRecord rec = qu.record();
    if (rec.value("PayrollAccess") == "Yes")
        payrollAccess = true;

    userID = rec.value("UserID").toString();

    companyDb = QSqlDatabase::addDatabase("QMYSQL", ui->cboCompanies->currentText());
    companyDb.setHostName(db.hostName());
    companyDb.setUserName(db.userName());
    companyDb.setPassword(db.password());
    companyDb.setDatabaseName(qu.record().value("DatabaseName").toString());

    companyName = ui->cboCompanies->currentText();
    ok = true;
//                if (companyDb.open()) {
//                    ok = true;
//                } else {
//                    dbOk = false;
//                    ok = false;
//                }
} */
