#ifndef NEWFILMREQUISITION_H
#define NEWFILMREQUISITION_H

#include <QDialog>

namespace Ui {
class NewFilmRequisition;
}

class NewFilmRequisition : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewFilmRequisition(QWidget *parent = 0);
    ~NewFilmRequisition();
    
private slots:
    void on_cmdCancel_clicked();

    void on_cmdOK_clicked();

    void on_cboCustomer_currentIndexChanged(const QString &arg1);

private:
    Ui::NewFilmRequisition *ui;
};

#endif // NEWFILMREQUISITION_H
