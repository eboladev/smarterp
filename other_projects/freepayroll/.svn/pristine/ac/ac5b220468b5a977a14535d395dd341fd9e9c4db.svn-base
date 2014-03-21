#include "companyinformationdialog.h"
#include "ui_companyinformationdialog.h"


CompanyInformationDialog::CompanyInformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompanyInformationDialog)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("freepayroll");

    model = new QSqlTableModel(this, db);
    model->setTable("company");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->txtAddress, model->fieldIndex("Address"));
    mapper->addMapping(ui->txtCompanyName, model->fieldIndex("Name"));
    mapper->addMapping(ui->txtPostcode, model->fieldIndex("Postcode"));
    mapper->addMapping(ui->txtEmail, model->fieldIndex("Email"));
    mapper->addMapping(ui->txtPayrollMonth, model->fieldIndex("CurrentMonth"));
    mapper->addMapping(ui->txtTown, model->fieldIndex("Town"));
    mapper->addMapping(ui->txtTel, model->fieldIndex("Telephone"));
    mapper->addMapping(ui->txtPIN, model->fieldIndex("PIN"));
    mapper->addMapping(ui->txtNSSF, model->fieldIndex("NSSF"));
    mapper->addMapping(ui->txtNHIF, model->fieldIndex("NHIF"));
    mapper->toFirst();
}

CompanyInformationDialog::~CompanyInformationDialog()
{
    model->submitAll();
    delete ui;
}

void CompanyInformationDialog::on_pushButton_clicked()
{
    model->submitAll();
}
