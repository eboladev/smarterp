#ifndef GENERATEJOBTICKETS_H
#define GENERATEJOBTICKETS_H

#include <datapublics.h>
#include <QDialog>

namespace Ui {
class GenerateJobTickets;
}

class GenerateJobTickets : public QDialog
{
    Q_OBJECT
    
public:
    explicit GenerateJobTickets(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString productID = QString());
    ~GenerateJobTickets();
    
private:
    Ui::GenerateJobTickets *ui;
    QSqlDatabase db;
    QString prodID, productCode, dieUnit, DieType, dieInstructions, origIns, custID;
    QString custName, address, prodName;
    QString ID, OD;
    QString A, W, F1, F2, F3, L, T, FL, S, currency, ink1, ink2, ink3, ink4;
    QString approxQtyTotal, TrimTotal, TrimText, ApproxQty;
    QString ID_L, ID_W, ID_H, OD_L, OD_W, OD_H, iB, iC, iE;
    QString PL, Gram1, Gram2, Gram3, Gram4, Gram5, Type1, Type2, Type3, Type4, Type5;
    QString cID;


    QString flap;
    QString waxing, fitments , layerpads;
    void round_nplaces(double &value, const int &to);
    double intB, intC, intEE, intM;

    int count;
    double round2(double number);
private slots:
    void FetchProductDetails();
    void RefreshTexts();
    void CalculateDetails();
    void on_txtQty_lostFocus();
    void on_cmdGenerate_clicked();
    void on_txtQty_editingFinished();
    void on_txtQty_returnPressed();
};

#endif // GENERATEJOBTICKETS_H
