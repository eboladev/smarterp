#ifndef NEWSTUDENT_H
#define NEWSTUDENT_H

#include <QtSql>
#include <QMainWindow>

namespace Ui {
class NewStudent;
}

class NewStudent : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit NewStudent(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~NewStudent();
    
private slots:
    void on_cmdFreshStudent_clicked();

private:
    Ui::NewStudent *ui;
    QSqlDatabase db;
};

#endif // NEWSTUDENT_H
