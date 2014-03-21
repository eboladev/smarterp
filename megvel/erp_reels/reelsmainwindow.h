#ifndef REELSMAINWINDOW_H
#define REELSMAINWINDOW_H

#include <QtSql>

#include <QMainWindow>

namespace Ui {
class ReelsMainWindow;
}

class ReelsMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ReelsMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~ReelsMainWindow();
    
private slots:
    void on_cmdRefresh_clicked();
    void refresh();
    void on_cmdEditSelectedReel_clicked();

private:
    Ui::ReelsMainWindow *ui;
    QSqlDatabase db;
};

#endif // REELSMAINWINDOW_H
