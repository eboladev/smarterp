#ifndef NEWREQUISITION_H
#define NEWREQUISITION_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class NewRequisition;
}

class NewRequisition : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewRequisition(QWidget *parent = 0);
    ~NewRequisition();
    
private slots:
    void on_cmdSave_clicked();

private:
    Ui::NewRequisition *ui;
};

#endif // NEWREQUISITION_H
