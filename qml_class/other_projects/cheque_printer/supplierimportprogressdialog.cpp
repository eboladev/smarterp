#include "supplierimportprogressdialog.h"
#include "ui_supplierimportprogressdialog.h"
#include "threadedexcelimporter.h"
SupplierImportProgressDialog::SupplierImportProgressDialog(QWidget *parent, QString fileName) :
    QDialog(parent), ui(new Ui::SupplierImportProgressDialog), path(fileName)
{
    ui->setupUi(this);
    ui->lblFileName->setText("Source File: "
                              + path);

    ThreadedExcelImporter *th = new ThreadedExcelImporter(this);
    th->setFileName(path);

    connect (ui->buttonBox, SIGNAL(rejected()), th, SLOT(terminate()));
    connect (ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    //connect (th, SIGNAL(finished()), this, SLOT(accept()));


    connect (th, SIGNAL(message(QString)), this, SLOT(threadMessage(QString)));
    connect (th, SIGNAL(error(QString)), this, SLOT(threadError(QString)));

    th->start();
}

SupplierImportProgressDialog::~SupplierImportProgressDialog()
{
    delete ui;
}

void SupplierImportProgressDialog::threadMessage(QString msg)
{
    ui->lblImportStatus->setText(msg);
}

void SupplierImportProgressDialog::threadError(QString msg)
{
    ui->lblImportStatus->setText(msg);
}
