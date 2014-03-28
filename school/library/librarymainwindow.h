#ifndef LIBRARYMAINWINDOW_H
#define LIBRARYMAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class LibraryMainWindow;
}

class LibraryMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LibraryMainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~LibraryMainWindow();
    
private:
    Ui::LibraryMainWindow *ui;
    QSqlDatabase db;
};

#endif // LIBRARYMAINWINDOW_H
