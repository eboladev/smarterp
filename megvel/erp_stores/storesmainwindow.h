#ifndef STORESMAINWINDOW_H
#define STORESMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class StoresMainWindow;
}

class StoresMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StoresMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~StoresMainWindow();
    
private slots:
    void on_actionManage_Suppliers_triggered();

    void on_actionItem_List_triggered();

    void on_actionNew_Requisition_triggered();

    void on_actionView_Requisitions_triggered();

    void on_actionNew_Film_Requisition_triggered();

private:
    Ui::StoresMainWindow *ui;
    QSqlDatabase db;
};

#endif // STORESMAINWINDOW_H
