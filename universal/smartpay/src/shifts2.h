#ifndef SHIFTS2_H
#define SHIFTS2_H

#include <QWidget>
#include <QtSql>

namespace Ui {
class Shifts2;
}

class Shifts2 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Shifts2(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Shifts2();
    
private slots:
    void on_cmdNewShift_clicked();
    void reloadShifts();
    void on_lstShifts_doubleClicked(const QModelIndex &index);

    void on_cmdDeleteShift_clicked();

private:
    Ui::Shifts2 *ui;
    QSqlDatabase db;
};

#endif // SHIFTS2_H
