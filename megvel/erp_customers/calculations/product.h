#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>
#include <QtSql>

#include <iostream>
#include <cmath>
#include <stdint.h>

class Product : public QObject
{
    Q_OBJECT
public:
    explicit Product(QObject *parent = 0, QSqlDatabase database = QSqlDatabase());
    
    QString getRecordValue(QSqlRecord rec, QString column);

    QString productId() const;
    void setProductId(const QString &productId);

    int productTypeId() const;
    void setProductTypeId(int productTypeId);

    QString productName() const;
    void setProductName(const QString &productName);

    int customerId() const;
    void setCustomerId(int customerId);

    QString productType() const;
    void setProductType(const QString &productType);

    QString directorComment() const;
    void setDirectorComment(const QString &directorComment);

    QString directorApproved() const;
    void setDirectorApproved(const QString &directorApproved);

    QString currency() const;
    void setCurrency(const QString &currency);

    QString noOfColors() const;
    void setNoOfColors(const QString &noOfColors);

    QString divided() const;
    void setDivided(const QString &divided);

    QString S() const;
    void setS(const QString &S);

    QString L() const;
    void setL(const QString &L);

    QString F3() const;
    void setF3(const QString &F3);

    QString F2() const;
    void setF2(const QString &F2);

    QString F1() const;
    void setF1(const QString &F1);

    QString locked() const;
    void setLocked(const QString &locked);

    QString confirmed() const;
    void setConfirmed(const QString &confirmed);

    QString dieInstructions() const;
    void setDieInstructions(const QString &dieInstructions);

    QString outs() const;
    void setOuts(const QString &outs);

    QString ID() const;
    void setID(const QString &ID);

    QString spec() const;
    void setSpec(const QString &spec);

    QString WT() const;
    void setWT(const QString &WT);

    QString GSM() const;
    void setGSM(const QString &GSM);

    QString BW() const;
    void setBW(const QString &BW);

    QString BL() const;
    void setBL(const QString &BL);

    QString price() const;
    void setPrice(const QString &price);

    QString rp() const;
    void setRp(const QString &rp);

    QString specialInstructions() const;
    void setSpecialInstructions(const QString &specialInstructions);

    QString type4() const;
    void setType4(const QString &type4);

    QString type3() const;
    void setType3(const QString &type3);

    QString type2() const;
    void setType2(const QString &type2);

    QString type1() const;
    void setType1(const QString &type1);

    QString gram4() const;
    void setGram4(const QString &gram4);

    QString gram3() const;
    void setGram3(const QString &gram3);

    QString gram2() const;
    void setGram2(const QString &gram2);

    QString gram1() const;
    void setGram1(const QString &gram1);

    QString e() const;
    void setE(const QString &e);

    QString c() const;
    void setC(const QString &c);

    QString b() const;
    void setB(const QString &b);

    QString sample() const;
    void setSample(const QString &sample);

    QString sterio() const;
    void setSterio(const QString &sterio);

    QString artwork() const;
    void setArtwork(const QString &artwork);

    QString ink4() const;
    void setInk4(QString ink4);

    QString ink3() const;
    void setInk3(QString ink3);

    QString ink2() const;
    void setInk2(QString ink2);

    QString ink1() const;
    void setInk1(QString ink1);

    QString getLayerPadsQty() const;
    void setLayerPadsQty(const QString &value);

    QString getLayerPadsH() const;
    void setLayerPadsH(const QString &value);

    QString getLayerPadsL() const;
    void setLayerPadsL(const QString &value);

    QString getLayerPads() const;
    void setLayerPads(const QString &value);

    QString fitmentH_L() const;
    void setFitmentH_L(const QString &fitmentH_L);

    QString fitmentH() const;
    void setFitmentH(const QString &fitmentH);

    QString fitmentL_L() const;
    void setFitmentL_L(const QString &fitmentL_L);

    QString fitmentL() const;
    void setFitmentL(const QString &fitmentL);

    QString fitmentQtyL() const;
    void setFitmentQtyL(const QString &fitmentQtyL);

    QString fitmentQtyS() const;
    void setFitmentQtyS(const QString &fitmentQtyS);

    QString fitmentSlots_L() const;
    void setFitmentSlots_L(const QString &fitmentSlots_L);

    QString fitmentSlots() const;
    void setFitmentSlots(const QString &fitmentSlots);

    QString fitments_S() const;
    void setFitments_S(const QString &fitments_S);

    QString fitments_L() const;
    void setFitments_L(const QString &fitments_L);

    QString fitments() const;
    void setFitments(const QString &fitments);

    QString waxing() const;
    void setWaxing(const QString &waxing);

    QString flap() const;
    void setFlap(const QString &flap);

    QString dieType() const;
    void setDieType(const QString &dieType);

    QString dieUnit() const;
    void setDieUnit(const QString &dieUnit);

    QString OD_H() const;
    void setOD_H(const QString &OD_H);

    QString OD_W() const;
    void setOD_W(const QString &OD_W);

    QString OD_L() const;
    void setOD_L(const QString &OD_L);

    QString ID_H() const;
    void setID_H(const QString &ID_H);

    QString ID_W() const;
    void setID_W(const QString &ID_W);

    QString ID_L() const;
    void setID_L(const QString &ID_L);

    QString description() const;
    void setDescription(const QString &description);

    QString Ply() const;
    void setPly(const QString &Ply);

    QString PL() const;
    void setPL(const QString &PL);

    QString productCode() const;
    void setProductCode(const QString &productCode);

    QString type5() const;
    void setType5(const QString &type5);

    QString gram5() const;
    void setGram5(const QString &gram5);

    double intB;
    double intC;
    double EE;
    double M;
    void round_nplaces(double &value, const uint32_t &to);
    double round2(double number);
signals:
    void detailsChanged();
    void calculationChanged();
public slots:
    void save();
    void recalculate();

    void idChanged();
    void odChanged();
    void paperSpecChanged();
private:
    QSqlDatabase db;
    QString m_productId;
    int m_productTypeId;
    QString m_productName;
    QString m_productCode;
    int m_customerId;
    QString m_productType;
    QString m_PL;
    QString m_Ply;
    QString m_description;
    QString m_ID_L;
    QString m_ID_W;
    QString m_ID_H;
    QString m_OD_L;
    QString m_OD_W;
    QString m_OD_H;
    QString m_dieUnit;
    QString m_dieType;
    QString m_flap;
    QString m_waxing;
    QString m_fitments;
    QString m_fitments_L;
    QString m_fitments_S;
    QString m_fitmentSlots;
    QString m_fitmentSlots_L;
    QString m_fitmentQtyS;
    QString m_fitmentQtyL;
    QString m_fitmentL;
    QString m_fitmentL_L;
    QString m_fitmentH;
    QString m_fitmentH_L;
    QString m_layerPads;
    QString m_layerPadsL;
    QString m_layerPadsH;
    QString m_layerPadsQty;
    QString m_ink1;
    QString m_ink2;
    QString m_ink3;
    QString m_ink4;
    QString m_artwork;
    QString m_sterio;
    QString m_sample;
    QString m_b, m_c, m_e;
    QString m_gram1;
    QString m_gram2;
    QString m_gram3;
    QString m_gram4;
    QString m_gram5;
    QString m_type1;
    QString m_type2;
    QString m_type3;
    QString m_type4;
    QString m_type5;
    QString m_specialInstructions;
    QString m_rp;
    QString m_price;
    QString m_BL;
    QString m_BW;
    QString m_GSM;
    QString m_WT;
    QString m_spec;
    QString m_ID;
    QString m_outs;
    QString m_dieInstructions;
    QString m_confirmed, m_locked;
    QString m_F1;
    QString m_F2;
    QString m_F3;
    QString m_L;
    QString m_S;
    QString m_divided;
    QString m_noOfColors;
    QString m_currency;
    QString m_directorApproved;
    QString m_directorComment;
};

#endif // PRODUCT_H
