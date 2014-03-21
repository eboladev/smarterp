#ifndef STUDENTSMAINWINDOW_H
#define STUDENTSMAINWINDOW_H

#include <QtGui>
#include <QtSql>
#include <QMainWindow>

class NewStudent;

namespace Ui {
class StudentsMainWindow;
}

class StudentsMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StudentsMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~StudentsMainWindow();
    
private:
    Ui::StudentsMainWindow *ui;
    QSqlDatabase db;

    NewStudent *t_newStudent;
};

#endif // STUDENTSMAINWINDOW_H
