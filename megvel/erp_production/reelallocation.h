#ifndef REELALLOCATION_H
#define REELALLOCATION_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class ReelAllocation;
}

class ReelAllocation : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ReelAllocation(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~ReelAllocation();
    
private slots:
    void on_actionNew_Entry_triggered();

private:
    Ui::ReelAllocation *ui;
    QSqlDatabase db;
    void reload();
};

#endif // REELALLOCATION_H
