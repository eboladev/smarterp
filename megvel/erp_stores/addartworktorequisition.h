#ifndef ADDARTWORKTOREQUISITION_H
#define ADDARTWORKTOREQUISITION_H

#include <QDialog>

namespace Ui {
class AddArtworkToRequisition;
}

class AddArtworkToRequisition : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddArtworkToRequisition(QWidget *parent = 0);
    ~AddArtworkToRequisition();
    QString artworkID;
    QString paperSize;
    QString customer;
    QString product;
    QString qty;
private slots:
    void on_cmdAdd_clicked();

private:
    Ui::AddArtworkToRequisition *ui;
};

#endif // ADDARTWORKTOREQUISITION_H
