#include "librarymainwindow.h"
#include "ui_librarymainwindow.h"

LibraryMainWindow::LibraryMainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::LibraryMainWindow)
{
    ui->setupUi(this);
    db = database;
}

LibraryMainWindow::~LibraryMainWindow()
{
    delete ui;
}
