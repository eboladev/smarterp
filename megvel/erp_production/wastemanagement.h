#ifndef WASTEMANAGEMENT_H
#define WASTEMANAGEMENT_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class WasteManagement;
}

class WasteManagement : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit WasteManagement(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~WasteManagement();
    
private slots:
    void on_cmdRefresh_clicked();

    void on_actionNew_Entry_triggered();

    void on_trvWaste_doubleClicked(const QModelIndex &index);

private:
    Ui::WasteManagement *ui;
    QSqlDatabase db;
};

#endif // WASTEMANAGEMENT_H
