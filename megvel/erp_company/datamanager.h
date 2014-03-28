#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
#include <QMainWindow>
#include <QDialog>
namespace Ui {
class DataManager;
}

class DataManager : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DataManager(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~DataManager();
    
private:
    Ui::DataManager *ui;
    QSqlDatabase db;
};

#endif // DATAMANAGER_H
