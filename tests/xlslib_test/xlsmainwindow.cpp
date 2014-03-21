#include "xlsmainwindow.h"
#include "ui_xlsmainwindow.h"
#include <QMessageBox>

#include "xlslib.h"
#include <QDebug>
//#include <QMYSQLDriver>
using namespace xlslib_core;

XLSMainWindow::XLSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XLSMainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL", "xlslib_test");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("cartons");
    db.setUserName("root");
    db.setPassword("pledge");

    //QMYSQLDriver *drv = new QMYSQLDriver(this);

    //qDebug() << drv;

    if (!db.open()) {
        QMessageBox::critical(this, "Error", db.lastError().text());
    } else {
        runQuery("SHOW FULL PROCESSLIST;");
    }
}

XLSMainWindow::~XLSMainWindow()
{
    delete ui;
}

void XLSMainWindow::on_actionExecute_Query_triggered()
{
    runQuery(ui->txtQuery->toPlainText());
}

void XLSMainWindow::runQuery(QString query)
{
    model = new QSqlQueryModel(this);

    model->setQuery(query, db);
    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "Error", model->lastError().text());
    } else {
        ui->tblResult->setModel(model);
    }
}

void XLSMainWindow::on_actionGenerate_Excel_FIle_triggered()
{
    workbook wb;
    worksheet* sh = wb.sheet("Sheet 1");

    for (int h = 0; h < model->columnCount(); h++) {
        QString headerData = model->headerData(h, Qt::Horizontal).toString();
        sh->label(0, h, headerData.toStdString())->fontbold(BOLDNESS_BOLD);
        //cell.fontbold(BOLDNESS_BOLD);

    }

    for (int r = 0; r < model->rowCount(); r++) {
        for (int c = 0; c < model->columnCount(); c++) {
            QString data = model->data(model->index(r, c)).toString();
            sh->label(r + 1, c, data.toStdString());
        }
    }

    int err = wb.Dump("TEST.xls");
    qDebug() << err;
}
