#ifndef USMAINWINDOW_H
#define USMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class USMainWindow;
}

class USMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit USMainWindow(QWidget *parent = 0);
    ~USMainWindow();
    
private:
    Ui::USMainWindow *ui;
};

#endif // USMAINWINDOW_H
