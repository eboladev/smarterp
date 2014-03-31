#include "dialogproducttest.h"
#include "ui_dialogproducttest.h"
#include <QMessageBox>

#include "editproduct.h"
DialogProductTest::DialogProductTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProductTest)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL", "productTestConnection");
    db.setHostName("192.168.0.8");
    db.setUserName("erp_user");
    db.setPassword("Salander123!!");
    db.setDatabaseName("cartons");

    if (!db.open()) {
        QMessageBox::critical(this, "Error", db.lastError().text());
        return;
    }
}

DialogProductTest::~DialogProductTest()
{
    delete ui;
}

void DialogProductTest::on_pushButton_clicked()
{
//    EditProduct *ed = new EditProduct(this, db);
//    ed->Edit(ui->lineEdit->text());
//    ed->exec();
}
