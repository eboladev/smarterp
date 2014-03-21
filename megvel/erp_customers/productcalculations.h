#ifndef PRODUCTCALCULATIONS_H
#define PRODUCTCALCULATIONS_H

#include <QObject>
#include <QtSql>

class ProductCalculations : public QObject
{
    Q_OBJECT
public:
    explicit ProductCalculations(QObject *parent = 0);
    double ID1, ID2, ID3;
    QString productName, paperSpec;
    double BL, BW, GSM, WT, RP, BWEIGHT;
    QString specs;
    double Price;
    QString customerName,customerAddress,dat,validity,creditTerms;
    double gram1, gram2,gram3,gram4,gram5;
    QString type1,type2,type3,type4,type5;
    /*const double B;
    const double C;
    const double EE;
    const double M; */
    QString att,totalPrice,totalSpecs,totalWeight;
signals:
    
public slots:
    void Calculations();
    QString getSellingPrice();
    QString GetWeightKgs(QString qty);
    QString GetWeightTonnes(QString qty);
private:
    QSqlDatabase db;
    QString s_prodID;
    
};

#endif // PRODUCTCALCULATIONS_H
