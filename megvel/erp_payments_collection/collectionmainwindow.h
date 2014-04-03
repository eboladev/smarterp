#ifndef COLLECTIONMAINWINDOW_H
#define COLLECTIONMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class CollectionMainWindow;
}

class CollectionMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CollectionMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CollectionMainWindow();
    
private:
    Ui::CollectionMainWindow *ui;
    QSqlDatabase db;
};

#endif // COLLECTIONMAINWINDOW_H
