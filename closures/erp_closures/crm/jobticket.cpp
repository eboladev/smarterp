#include "jobticket.h"
#include <QtSql>
#include "datapublics.h"
JobTicket::JobTicket(QObject *parent) :
    QObject(parent)
{
}
QString JobTicket::productID() const
{
    return m_productID;
}

void JobTicket::setProductID(const QString &productID)
{
    m_productID = productID;
    QSqlQuery qu = QSqlDatabase::database("closures").exec("SELECT * FROM products WHERE product_id = '" + m_productID + "'");
    if (!qu.lastError().isValid()) {
        qu.first();
        m_wt = qu.record().value("wt").toDouble();

        m_pricePer1000 = qu.record().value("price_per_thousand").toString();
        m_pricePerPiece = qu.record().value("price_per_piece").toString();
        m_packing = qu.record().value("packing").toString();
        m_piecesPerPack = qu.record().value("caps_per_pack").toString();
        if (m_packing == "Both") {
            m_packing = "Carton + Liner";
        } else {
            m_packing = "Liner Only";
        }

        m_hasBottles = false;
        m_bottleName = " ";
        m_bottlePrice = 0;
        m_totalBottlePrice = 0;
        m_bottleQty = 0;

        if (qu.record().value("has_bottles") == "yes") {
            m_hasBottles = true;
            m_bottlePrice = qu.record().value("bottle_price").toDouble();
            QString bottleName = DataPublics
                    ::getDbValue("SELECT * FROM bottle_names WHERE entry_id = '" + qu.record().value("bottle_name").toString() + "'"
                                 , QSqlDatabase::database(), "bottle_name"
                                 ).toString();

            QString bottletype = DataPublics
                    ::getDbValue("SELECT * FROM bottle_types WHERE entry_id = '" + qu.record().value("bottle_type").toString() + "'"
                                 , QSqlDatabase::database(), "bottle_type"
                                 ).toString();

            setBottleName(bottleName + "-" + bottletype);
            m_bottlePrice = qu.record().value("bottle_price").toDouble();
            m_capPrice = qu.record().value("price_per_piece").toDouble();
        }
        m_piecePrice = qu.record().value("total_price").toDouble();
        m_closureName = qu.record().value("product_name").toString();

        emit detailsChanged();
    }
}
int JobTicket::qty() const
{
    return m_qty;
}

void JobTicket::setQty(const int &qty)
{
    m_qty = qty;
}
float JobTicket::hdpe() const
{
    return m_hdpe;
}


float JobTicket::masterBatch() const
{
    return m_masterBatch;
}

float JobTicket::inks() const
{
    return m_inks;
}
QString JobTicket::pricePerPiece() const
{
    return m_pricePerPiece;
}

void JobTicket::setPricePerPiece(const QString &pricePerPiece)
{
    m_pricePerPiece = pricePerPiece;
}
QString JobTicket::pricePer1000() const
{
    return m_pricePer1000;
}

void JobTicket::setPricePer1000(const QString &pricePer1000)
{
    m_pricePer1000 = pricePer1000;
}
QString JobTicket::packing() const
{
    return m_packing;
}

void JobTicket::setPacking(const QString &packing)
{
    m_packing = packing;
}
QString JobTicket::piecesPerPack() const
{
    return m_piecesPerPack;
}

void JobTicket::setPiecesPerPack(const QString &piecesPerPack)
{
    m_piecesPerPack = piecesPerPack;
}
bool JobTicket::hasBottles() const
{
    return m_hasBottles;
}

void JobTicket::setHasBottles(bool hasBottles)
{
    m_hasBottles = hasBottles;
}
QString JobTicket::bottleName() const
{
    return m_bottleName;
}

void JobTicket::setBottleName(const QString &bottleName)
{
    m_bottleName = bottleName;
}
double JobTicket::capPrice() const
{
    return m_capPrice;
}

void JobTicket::setCapPrice(double capPrice)
{
    m_capPrice = capPrice;
}
double JobTicket::bottlePrice() const
{
    return m_bottlePrice;
}

void JobTicket::setBottlePrice(double bottlePrice)
{
    m_bottlePrice = bottlePrice;
}
double JobTicket::totalCapPrice() const
{
    return m_totalCapPrice;
}

void JobTicket::setTotalCapPrice(double totalCapPrice)
{
    m_totalCapPrice = totalCapPrice;
}
double JobTicket::totalBottlePrice() const
{
    return m_totalBottlePrice;
}

void JobTicket::setTotalBottlePrice(double totalBottlePrice)
{
    m_totalBottlePrice = totalBottlePrice;
}
double JobTicket::grandPrice() const
{
    return m_grandPrice;
}

void JobTicket::setGrandPrice(double grandPrice)
{
    m_grandPrice = grandPrice;
}


QString JobTicket::closureName() const
{
    return m_closureName;
}

void JobTicket::setClosureName(const QString &closureName)
{
    m_closureName = closureName;
}
double JobTicket::piecePrice() const
{
    return m_piecePrice;
}

void JobTicket::setPiecePrice(double piecePrice)
{
    m_piecePrice = piecePrice;
}
int JobTicket::bottleQty() const
{
    return m_bottleQty;
}

void JobTicket::setBottleQty(int bottleQty)
{
    m_bottleQty = bottleQty;
}
int JobTicket::fullPacks() const
{
    return m_fullPacks;
}

void JobTicket::setFullPacks(int fullPacks)
{
    m_fullPacks = fullPacks;
}
int JobTicket::partialPacks() const
{
    return m_partialPacks;
}

void JobTicket::setPartialPacks(int partialPacks)
{
    m_partialPacks = partialPacks;
}
int JobTicket::totalPacks() const
{
    return m_totalPacks;
}

void JobTicket::setTotalPacks(int totalPacks)
{
    m_totalPacks = totalPacks;
}
int JobTicket::capsInFullPacks() const
{
    return m_capsInFullPacks;
}

void JobTicket::setCapsInFullPacks(int capsInFullPacks)
{
    m_capsInFullPacks = capsInFullPacks;
}
int JobTicket::capsInPartialPacks() const
{
    return m_capsInPartialPacks;
}

void JobTicket::setCapsInPartialPacks(int capsInPartialPacks)
{
    m_capsInPartialPacks = capsInPartialPacks;
}
int JobTicket::totalCapsInFull() const
{
    return m_totalCapsInFull;
}

void JobTicket::setTotalCapsInFull(int totalCapsInFull)
{
    m_totalCapsInFull = totalCapsInFull;
}
double JobTicket::totalCapsInPart() const
{
    return m_totalCapsInPart;
}

void JobTicket::setTotalCapsInPart(double totalCapsInPart)
{
    m_totalCapsInPart = totalCapsInPart;
}
int JobTicket::packingCapsTotal() const
{
    return m_packingCapsTotal;
}

void JobTicket::setPackingCapsTotal(int packingCapsTotal)
{
    m_packingCapsTotal = packingCapsTotal;
}















void JobTicket::recalculate()
{
    //Calculate sales details
    if (m_hasBottles) {
        m_bottleQty = m_qty;
    }
    m_totalBottlePrice = m_bottlePrice * m_bottleQty;
    m_totalCapPrice = m_capPrice * m_qty;
    m_grandPrice = m_piecePrice * m_qty;

    //Calculate production details
    m_hdpe = (m_wt * m_qty) / 1000;
    m_masterBatch = m_hdpe * 0.01;
    m_inks = 0;


    emit detailsChanged();
    //packing
    double t_packs = m_qty / m_piecesPerPack.toDouble();
    QString s_packs = QString::number(t_packs);
    m_fullPacks = 0;
    m_partialPacks = 0;
    m_totalPacks = 0;
    m_capsInFullPacks = 0;
    m_capsInPartialPacks = 0;
    m_packingCapsTotal = 0;

    if (s_packs.contains(".")) {
        QStringList lst_packs = s_packs.split(".");
        double full = 0;
        double partial = 0;
        full = lst_packs.at(0).toDouble();
        partial = 1;//lst_packs.at(1).toDouble();
        m_fullPacks = full;
        m_partialPacks = partial;
        m_capsInPartialPacks = (t_packs - full) * m_piecesPerPack.toDouble();
    } else {
        m_fullPacks = t_packs;
    }

    m_capsInFullPacks = m_piecesPerPack.toDouble();
    m_totalPacks = m_fullPacks + m_partialPacks;

    m_totalCapsInFull = m_fullPacks * m_capsInFullPacks;

    //qDebug() << m_fullPacks << m_capsInFullPacks << m_totalCapsInFull;

    m_totalCapsInPart = m_partialPacks * m_capsInPartialPacks;

    m_packingCapsTotal = m_totalCapsInFull + m_totalCapsInPart;

    emit detailsChanged();
}








