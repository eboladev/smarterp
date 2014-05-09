#ifndef JOBTICKET_H
#define JOBTICKET_H

#include <QObject>

class JobTicket : public QObject
{
    Q_OBJECT
public:
    explicit JobTicket(QObject *parent = 0);
    
    QString productID() const;
    void setProductID(const QString &productID);

    int qty() const;
    void setQty(const int &qty);

    float hdpe() const;

    float masterBatch() const;

    float inks() const;

    QString pricePerPiece() const;
    void setPricePerPiece(const QString &pricePerPiece);

    QString pricePer1000() const;
    void setPricePer1000(const QString &pricePer1000);

    QString packing() const;
    void setPacking(const QString &packing);

    QString piecesPerPack() const;
    void setPiecesPerPack(const QString &piecesPerPack);

    bool hasBottles() const;
    void setHasBottles(bool hasBottles);

    QString bottleName() const;
    void setBottleName(const QString &bottleName);

    double capPrice() const;
    void setCapPrice(double capPrice);

    double bottlePrice() const;
    void setBottlePrice(double bottlePrice);

    double totalCapPrice() const;
    void setTotalCapPrice(double totalCapPrice);

    double totalBottlePrice() const;
    void setTotalBottlePrice(double totalBottlePrice);

    double grandPrice() const;
    void setGrandPrice(double grandPrice);

    QString closureName() const;
    void setClosureName(const QString &closureName);

    double piecePrice() const;
    void setPiecePrice(double piecePrice);



    int bottleQty() const;
    void setBottleQty(int bottleQty);

    int fullPacks() const;
    void setFullPacks(int fullPacks);

    int partialPacks() const;
    void setPartialPacks(int partialPacks);

    int totalPacks() const;
    void setTotalPacks(int totalPacks);

    int capsInFullPacks() const;
    void setCapsInFullPacks(int capsInFullPacks);

    int capsInPartialPacks() const;
    void setCapsInPartialPacks(int capsInPartialPacks);

    int totalCapsInFull() const;
    void setTotalCapsInFull(int totalCapsInFull);

    double totalCapsInPart() const;
    void setTotalCapsInPart(double totalCapsInPart);

    int packingCapsTotal() const;
    void setPackingCapsTotal(int packingCapsTotal);

private:
    QString m_productID;
    int m_qty;
    float m_hdpe;
    float m_masterBatch;
    float m_inks;

    double m_wt;

    QString m_pricePerPiece;
    QString m_pricePer1000;
    QString m_packing;
    QString m_piecesPerPack;

    bool m_hasBottles;
    int m_bottleQty;

    QString m_bottleName;
    QString m_closureName;
    double m_capPrice;
    double m_bottlePrice;

    double m_totalCapPrice;
    double m_totalBottlePrice;


    double m_piecePrice;
    double m_grandPrice;


    int m_fullPacks;
    int m_partialPacks;
    int m_totalPacks;

    int m_capsInFullPacks;
    int m_capsInPartialPacks;
    int m_packingCapsTotal;

    int m_totalCapsInFull;
    double m_totalCapsInPart;
signals:
    void detailsChanged();
public slots:
    void recalculate();
};

#endif // JOBTICKET_H
