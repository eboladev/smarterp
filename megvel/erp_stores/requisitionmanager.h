#ifndef REQUISITIONMANAGER_H
#define REQUISITIONMANAGER_H

#include <QDialog>

namespace Ui {
class RequisitionManager;
}

class RequisitionManager : public QDialog
{
    Q_OBJECT
    
public:
    explicit RequisitionManager(QWidget *parent = 0);
    ~RequisitionManager();
    
private slots:
    void on_cmdApproveRequisition_clicked();

    void on_cmdPostToQuickbooks_clicked();

private:
    Ui::RequisitionManager *ui;
    void reloadRequisitions();
};

#endif // REQUISITIONMANAGER_H
