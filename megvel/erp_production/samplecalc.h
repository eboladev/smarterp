#ifndef SAMPLECALC_H
#define SAMPLECALC_H

#include <QDialog>

namespace Ui {
class SampleCalc;
}

class SampleCalc : public QDialog
{
    Q_OBJECT
    
public:
    explicit SampleCalc(QWidget *parent = 0);
    ~SampleCalc();
    
private:
    Ui::SampleCalc *ui;
};

#endif // SAMPLECALC_H
