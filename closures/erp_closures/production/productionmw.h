#ifndef PRODUCTIONMW_H
#define PRODUCTIONMW_H

#include <QMainWindow>

namespace Ui {
class ProductionMW;
}

class ProductionMW : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductionMW(QWidget *parent = 0);
    ~ProductionMW();

private:
    Ui::ProductionMW *ui;
};

#endif // PRODUCTIONMW_H
