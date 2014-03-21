#ifndef UPDATERMAINWINDOW_H
#define UPDATERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class UpdaterMainWindow;
}

class UpdaterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdaterMainWindow(QWidget *parent = 0);
    ~UpdaterMainWindow();

private:
    Ui::UpdaterMainWindow *ui;
};

#endif // UPDATERMAINWINDOW_H
