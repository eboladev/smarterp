#include "datamanager.h"
#include "ui_datamanager.h"
#include <QFile>
#include <QDir>

DataManager::DataManager(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::DataManager)
{
    ui->setupUi(this);
    db = database;
}

DataManager::~DataManager()
{
    delete ui;
}
