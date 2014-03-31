#ifndef CRMMAINWINDOW_H
#define CRMMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class CRMMainWindow;
}

class CRMMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CRMMainWindow(QWidget *parent = 0,
                           QSqlDatabase database = QSqlDatabase()
                           );
    ~CRMMainWindow();
    
private:
    Ui::CRMMainWindow *ui;
    QSqlDatabase db;
};

#endif // CRMMAINWINDOW_H
