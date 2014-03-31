#ifndef ADVANCES_H
#define ADVANCES_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Advances;
}

class Advances : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Advances(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Advances();
    
private slots:

    void on_cboMonths_currentIndexChanged(const QString &arg1);

    void on_actionNew_Advance_triggered();

    void on_cmdDelete_clicked();

    void on_actionRefresh_triggered();

private:
    Ui::Advances *ui;
    QSqlDatabase db;
};

#endif // ADVANCES_H
