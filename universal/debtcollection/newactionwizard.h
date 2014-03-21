#ifndef NEWACTIONWIZARD_H
#define NEWACTIONWIZARD_H

#include <QWizard>

namespace Ui {
class NewActionWizard;
}

class NewActionWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit NewActionWizard(QWidget *parent = 0);
    ~NewActionWizard();
    
private:
    Ui::NewActionWizard *ui;
};

#endif // NEWACTIONWIZARD_H
