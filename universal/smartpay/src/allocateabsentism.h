#ifndef ALLOCATEABSENTISM_H
#define ALLOCATEABSENTISM_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AllocateAbsentism;
}

class AllocateAbsentism : public QDialog
{
    Q_OBJECT
    
public:
    explicit AllocateAbsentism(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~AllocateAbsentism();
    
private slots:
    void on_dtpDate_dateChanged(const QDate &date);

    void on_cmdAddToLeave_clicked();

    void on_cmdAddToAbsent_clicked();

    void on_cmdRemoveFromLeave_clicked();

    void on_cmdRemoveFromAbsent_clicked();

    void on_toolButton_clicked();

private:
    Ui::AllocateAbsentism *ui;
    QSqlDatabase db;
};

#endif // ALLOCATEABSENTISM_H
