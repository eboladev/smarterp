#ifndef MAKESACCOPAYMENT_H
#define MAKESACCOPAYMENT_H

#include <QDialog>

namespace Ui {
class MakeSaccoPayment;
}

class MakeSaccoPayment : public QDialog
{
    Q_OBJECT
    
public:
    explicit MakeSaccoPayment(QWidget *parent = 0);
    ~MakeSaccoPayment();
    
private:
    Ui::MakeSaccoPayment *ui;
};

#endif // MAKESACCOPAYMENT_H
