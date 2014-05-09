#ifndef PRODUCTIONDATAENTRYWIZARD_H
#define PRODUCTIONDATAENTRYWIZARD_H

#include <QWizard>

namespace Ui {
class ProductionDataEntryWizard;
}

class ProductionDataEntryWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit ProductionDataEntryWizard(QWidget *parent = 0);
    ~ProductionDataEntryWizard();
    
private:
    Ui::ProductionDataEntryWizard *ui;
};

#endif // PRODUCTIONDATAENTRYWIZARD_H
