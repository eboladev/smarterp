#ifndef MYDOCK_H
#define MYDOCK_H

#include <QWidget>

namespace Ui {
    class MyDock;
}

class MyDock : public QWidget
{
    Q_OBJECT

public:
    explicit MyDock(QWidget *parent = 0);
    ~MyDock();

private:
    Ui::MyDock *ui;
};

#endif // MYDOCK_H
