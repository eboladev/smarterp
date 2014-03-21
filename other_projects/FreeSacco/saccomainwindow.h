#ifndef SACCOMAINWINDOW_H
#define SACCOMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class SaccoMainWindow;
}

class SaccoMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SaccoMainWindow(QWidget *parent = 0);
    ~SaccoMainWindow();

private slots:
    void on_actionMember_Manager_triggered();

    void on_actionMember_Companies_triggered();

private:
    Ui::SaccoMainWindow *ui;

    void addSubWindow(QMainWindow *sub);

    QSqlDatabase db;
};

#endif // SACCOMAINWINDOW_H
