#include "product.h"
#include "datapublics.h"
#include "math.h"
Product::Product(QObject *parent, QSqlDatabase database) :
    QObject(parent)
{
    db = database;
    intB = 1.35;
    intC = 1.45;
    EE = 1.25;
    M = 1000000;
    //qDebug() << "New Product Instance";
}

QString Product::getRecordValue(QSqlRecord rec, QString column)
{
    QString ret = rec.value(column).toString();
    //qDebug() << column + " is " + ret;
    return ret;
}
QString Product::productId() const
{
    return m_productId;
}

void Product::setProductId(const QString &productId)
{
    //qDebug() << "Setting product ID";
    m_productId = productId;
    QSqlQuery qu = db.exec("SELECT * FROM products WHERE `Product ID` = '" + productId + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }
    qu.first();
    QSqlRecord rec = qu.record();
    setArtwork(qu.record().value("Artwork").toString());
    setProductName(qu.record().value("Product").toString());
    setProductCode(qu.record().value(4).toString());

    //qDebug() << m_productCode;
    setCustomerId(rec.value("Customer").toInt());
    setProductType(qu.record().value("`Product Type`").toString());

    setPL(qu.record().value("PL").toString());
    setPly(qu.record().value("Ply").toString());

    setDescription(qu.record().value("Description").toString());

    setID_L(qu.record().value("ID_L").toString());
    setID_W(qu.record().value("ID_W").toString());
    setID_H(qu.record().value("ID_H").toString());

    setOD_L(qu.record().value("OD_L").toString());
    setOD_H(qu.record().value("OD_H").toString());
    setOD_W(qu.record().value("OD_W").toString());

    setDieUnit(qu.record().value("DieUnit").toString());
    setDieType(qu.record().value("DieType").toString());

    setFlap(qu.record().value("Flap").toString());
    setWaxing(qu.record().value("Waxing").toString());

    setFitments(qu.record().value("Fitments").toString());
    setFitments_L(qu.record().value("Fitments_L").toString());
    setFitments_S(qu.record().value("Fitments_S").toString());
    setFitmentSlots(qu.record().value("FitmentSlots").toString());
    setFitmentSlots_L(qu.record().value("FitmentSlots_L").toString());
    setFitmentQtyS(qu.record().value("FitmentQtyS").toString());
    setFitmentQtyL(qu.record().value("FitmentQtyL").toString());
    setFitmentL(qu.record().value("FitmentL").toString());
    setFitmentL_L(qu.record().value("FitmentL_L").toString());
    setFitmentH(qu.record().value("FitmentH").toString());
    setFitmentH_L(qu.record().value("FitmentH_L").toString());

    setLayerPads(qu.record().value("LayerPads").toString());
    setLayerPadsL(qu.record().value("LayerPadsL").toString());
    setLayerPadsQty(qu.record().value("LayerPadsQty").toString());
    setLayerPadsH(qu.record().value("LayerPadsH").toString());

    setInk1(qu.record().value("Ink1").toString());
    setInk2(qu.record().value("Ink2").toString());
    setInk3(qu.record().value("Ink3").toString());
    setInk4(qu.record().value("Ink4").toString());

    setSterio(qu.record().value("Sterio").toString());
    setSample(qu.record().value("Sample").toString());

    setB(qu.record().value("B").toString());
    setC(qu.record().value("C").toString());
    setE(qu.record().value("E").toString());

    setGram1(qu.record().value("Gram1").toString());
    setGram2(qu.record().value("Gram2").toString());
    setGram3(qu.record().value("Gram3").toString());
    setGram4(qu.record().value("Gram4").toString());
    setGram5(qu.record().value("Gram5").toString());

    setType1(qu.record().value("Type1").toString());
    setType2(qu.record().value("Type2").toString());
    setType3(qu.record().value("Type3").toString());
    setType4(qu.record().value("Type4").toString());
    setType5(qu.record().value("Type5").toString());

    setRp(qu.record().value("RetailPrice").toString());
    setPrice(qu.record().value("Price").toString());

    setBL(qu.record().value("BL").toString());
    setBW(qu.record().value("BW").toString());
    setGSM(qu.record().value("GSM").toString());
    setWT(qu.record().value("WT").toString());
    setSpec(qu.record().value("Spec").toString());
    setID(qu.record().value("ID").toString());
    setOuts(qu.record().value("Outs").toString());

    setDieInstructions(qu.record().value("DieInstructions").toString());
    setSpecialInstructions(qu.record().value("SpecialInstructions").toString());

    setF1(qu.record().value("F1").toString());
    setF2(qu.record().value("F2").toString());
    setF3(qu.record().value("F3").toString());

    setL(qu.record().value("L").toString());
    setS(qu.record().value("S").toString());

    setDivided(qu.record().value("Divided").toString());

    setNoOfColors(qu.record().value("NumberOfColors").toString());

    setCurrency(qu.record().value("Currency").toString());

    setDirectorApproved(qu.record().value("DirectorApproved").toString());


    emit detailsChanged();
    emit calculationChanged();
}
int Product::productTypeId() const
{
    return m_productTypeId;
}

void Product::setProductTypeId(int productTypeId)
{
    m_productTypeId = productTypeId;
}
QString Product::productName() const
{
    return m_productName;
}

void Product::setProductName(const QString &productName)
{
    m_productName = productName;
}

void Product::save()
{
    if (m_outs.toDouble() > 1) {
        setDieInstructions("Number of outs: " + m_outs);
    }

    QString query = ""
            "UPDATE products SET "
            " Product = '" + m_productName + "'"
            ", `Product Code` = '" + m_productCode + "'"
            ", Customer = '" + QString::number(m_customerId) + "'"
            ", `Product Type` = '" + m_productType + "'"
            ", PL = '" + m_PL + "'"
            ", Description = '" + m_description + "'"
            ", ID_L = '" + m_ID_L +  "'"
            ", ID_W = '" + m_ID_W + "'"
            ", ID_H = '" + m_ID_H + "'"
            ", OD_L = '" + m_OD_L + "'"
            ", OD_W = '" + m_OD_W + "'"
            ", OD_H = '" + m_OD_H + "'"
            ", DieUnit = '" + m_dieUnit + "'"
            ", DieType = '" + m_dieType + "'"
            ", Flap = '" + m_flap + "'"
            ", Waxing = '" + m_waxing + "'"
            ", Fitments = '" + m_fitments + "'"
            ", Fitments_L = '" + m_fitments_L + "'"
            ", Fitments_S = '" + m_fitments_S + "'"
            ", FitmentSlots = '" + m_fitmentSlots  + "'"
            ", FitmentSlots_L = '" + m_fitmentSlots_L + "'"
            ", FitmentQtyS = '" + m_fitmentQtyS+ "'"
            ", FitmentQtyL = '" + fitmentQtyL() + "'"
            ", FitmentL = '" + fitmentL() + "'"
            ", FitmentL_L = '" + fitmentL_L() + "'"
            ", FitmentH = '" + fitmentH() + "'"
            ", FitmentH_L = '" + fitmentH_L() + "'"
            ", LayerPads = '" + m_layerPads + "'"
            ", LayerPadsL = '" + m_layerPadsL + "'"
            ", LayerPadsQty = '" + m_layerPadsQty + "'"
            ", LayerPadsH = '" + m_layerPadsH + "'"
            ", Ink1 = '" + ink1() + "'"
            ", Ink2 = '" + ink2() + "'"
            ", Ink3 = '" + ink3() + "'"
            ", Ink4 = '" + ink4() + "'"
            ", Artwork = '" + artwork() + "'"
            ", Sterio = '" + sterio() + "'"
            ", Sample = '" + sample() + "'"
            ", B = '" + m_b + "'"
            ", C = '" + m_c + "'"
            ", E = '" + m_e + "'"
            ", Outs = '" + m_outs + "'"
            ", Gram1 = '" + gram1() + "'"
            ", Type1 = '" + type1() + "'"
            ", Gram2 = '" + gram2() + "'"
            ", Type2 = '" + type2() + "'"
            ", Gram3 = '" + gram3() + "'"
            ", Type3 = '" + type3() + "'"
            ", Gram4 = '" + gram4() + "'"
            ", Type4 = '" + type4() + "'"
            ", Gram5 = '" + gram5() + "'"
            ", Type5 = '" + type5() + "'"
            ", SpecialInstructions = '" + specialInstructions() + "'"
            ", RetailPrice = '" + rp() + "'"
            ", Price = '" + price() + "'"
            ", BL = '" + BL() + "'"
            ", BW = '" + BW() + "'"
            ", GSM = '" + GSM() + "'"
            ", WT = '" + WT() + "'"
            ", Spec = '" + spec() + "'"
            ", ID = '" + ID() + "'"
            ", Outs = '" + outs() + "'"
            ", DieInstructions = '" + dieInstructions() + "'"
            ", F1 = '" + F1() + "'"
            ", F2 = '" + F2() + "'"
            ", F3 = '" + F3() + "'"
            ", L = '" + L() + "'"
            ", S = '" + S() + "'"
            ", Divided = '" + divided() + "'"
            ", NumberOfColors = '" + noOfColors() + "'"
            ", Currency = '" + currency() + "'"
            " WHERE `Product ID` = '" + m_productId + "'";


    //qDebug() << query;

    QSqlQuery qu = db.exec(query);


    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }

}

void Product::recalculate()
{
    double d_id1 = 0;
    double d_id2 = 0;
    double d_id3 = 0;

    if (m_ID_L.toDouble() > 0)
        d_id1 = m_ID_L.toDouble();
    if (m_ID_W.toDouble() > 0)
        d_id2 = m_ID_W.toDouble();
    if (m_ID_H.toDouble() > 0)
        d_id3 = m_ID_H.toDouble();

    double d_gram1 = 0;
    double d_gram2 = 0;
    double d_gram3 = 0;
    double d_gram4 = 0;
    double d_gram5 = 0;

    if (m_gram1.toDouble() > 0)
        d_gram1 = m_gram1.toDouble();
    if (m_gram2.toDouble() > 0)
        d_gram2 = m_gram2.toDouble();
    if (m_gram3.toDouble() > 0)
        d_gram3 = m_gram3.toDouble();
    if (m_gram4.toDouble() > 0)
        d_gram4 = m_gram4.toDouble();
    if (m_gram5.toDouble() > 0)
        d_gram5 = m_gram5.toDouble();

    double iW = d_id2, iL = d_id1, iH = d_id3;

    double BL, BW, GSM, WT, RP, d_Price, BWEIGHT, TONS,
            bceRate, plyRate1, plyRate2
            ;
    QString paperSpec, dat, bce, sSpec;


    BL = (2 * iW) + (2 * iL);
    BW = (iW + iH);

    BWEIGHT = 0;
    TONS = 0;

    d_Price = 0;
    if (m_price.toDouble() > 0)
        d_Price = m_price.toDouble();

    bce = "";
    if (m_b == "True")
        bce = "B";

    if (m_c == "True")
        bce = bce + "C";

    if (m_e == "True")
        bce = bce + "E";

    if (m_PL.contains("3") && bce == "B") {
        bceRate = intB;
        BL = BL + 42;
        BW = BW + 12;
    }
    if (m_PL.contains("3") && bce == "C") {
        bceRate = intC;
        BL = BL + 46;
        BW = BW + 16;
    }
    if (m_PL.contains("3") && bce == "E") {
        bceRate = EE;
        BL = BL + 38;
        BW = BW + 8;
    }
    if (m_PL.contains("5") && bce == "BC") {
        plyRate1 = intB;
        plyRate2 = intC;
        BL = BL + 58;
        BW = BW + 28;
    }
    if (m_PL.contains("5") && bce == "BE") {
        plyRate1 = intB;
        plyRate2 = EE;
        BL = BL + 58;
        BW = BW + 28;
    }
    if (m_PL.contains("5") && bce == "CE") {
        plyRate1 = intC;
        plyRate2 = EE;
        BL = BL + 58;
        BW = BW + 28;
    }

    if (BL > 2400)
    {
        BL = BL + 30;
    }

    if (m_PL.contains("Die")) {
        BL = m_BL.toDouble();
        BW =  m_BW.toDouble();
    }

    sSpec = "";

    if (type2() == "B")
        plyRate1 = intB;

    if (type2() == "C")
        plyRate1 = intC;

    if (type2() == "E")
        plyRate1 = EE;

    if (type4() == "B")
        plyRate2 = intB;

    if (type4() == "C")
        plyRate2 = intC;

    if (type4() == "E")
        plyRate2 = EE;

    if (m_PL.contains("3")) {
        sSpec = gram1() + type1() + "/" + gram2() + type2() + "/" +
                gram3() + type3();
        GSM = (d_gram1 + (d_gram2 * bceRate) + d_gram3) / 1000;
    }

    if (m_PL.contains("5")) {
        sSpec = gram1() + type1() + "/" + gram2() + type2() + "/" +
                gram3() + type3()+ gram4() + type4() + "/"
                + gram5() + type5();
        GSM = (d_gram1 + (d_gram2 * plyRate1) + d_gram3 + (d_gram4 * plyRate2) + d_gram5) / 1000;
    }

    round_nplaces(GSM, 3);
    BWEIGHT = ((BL * BW * GSM) / M) * 1.05;
    RP = (d_Price / BWEIGHT);
    round_nplaces(RP, 2);

    WT = BWEIGHT;

    round_nplaces(WT, 3);

    m_rp = QString::number(RP);
    m_BL = QString::number(BL);
    m_BW = QString::number(BW);
    m_GSM = QString::number(GSM);
    m_WT = QString::number(WT);

    if (m_PL.contains("Die")) {
        if (m_outs == "")
            m_outs = "1";

        if (m_outs == "0")
            m_outs = "1";

        double d  = BWEIGHT / m_outs.toDouble();
        double r = d_Price / WT;
        round_nplaces(d, 3);

        m_divided = QString::number(d);
        WT = m_divided.toDouble();


        round_nplaces(r, 2);
        RP = r;
        RP = RP * (m_outs.toDouble());
        round_nplaces(RP, 2);
        m_rp = QString::number(RP);
    }

    //ALL CALCULATIONS ARE DONE
    emit calculationChanged();
}

void Product::idChanged()
{
    //qDebug() << "ID Changed. Calculating new OD";

    if (m_PL.contains("SFK"))
        return;

    if (m_PL.contains("2 Ply"))
    {
        m_OD_L = m_ID_L;
        m_OD_H = m_ID_H;
        m_OD_W = m_ID_W;
    }


    if (m_PL.contains("SFK"))
    {
        m_OD_L  = "";
        m_OD_W  = "";
        m_OD_H  = "";
    }

    if (m_PL.contains("3 Ply"))
    {
        if (m_b == "True") {
            m_OD_L = QString::number(m_ID_L.toInt() + 3);
            m_OD_W = QString::number(m_ID_W.toInt() + 3);
            m_OD_H = QString::number(m_ID_H.toInt() + 6);
        }
        if (m_c == "True") {
            m_OD_L = QString::number(m_ID_L.toInt() + 4);
            m_OD_W = QString::number(m_ID_W.toInt() + 4);
            m_OD_H = QString::number(m_ID_H.toInt() + 7);
        }
        if (m_e == "True") {
            m_OD_L = QString::number(m_ID_L.toInt() + 2);
            m_OD_W = QString::number(m_ID_W.toInt() + 2);
            m_OD_H = QString::number(m_ID_H.toInt() + 5);
        }
    }

    if (m_PL.contains("5 Ply"))
    {
        m_OD_L = QString::number(m_ID_L.toInt() + 5);
        m_OD_W = QString::number(m_ID_W.toInt() + 5);
        m_OD_H = QString::number(m_ID_H.toInt() + 10);
    }

    if (m_PL.contains("Die Cut Carton 3 Ply"))
    {
        m_OD_L  = "";
        m_OD_W  = "";
        m_OD_H  = "";
    }

    if (m_PL.contains("Die Cut Carton 5 Ply"))
    {
        m_OD_L  = "";
        m_OD_W  = "";
        m_OD_H  = "";
    }

    recalculate();
}

void Product::odChanged()
{
    //qDebug() << "OD Changed. Calculating new ID";
    if (m_PL.contains("SFK"))
        return;

    if (m_PL.contains("2 Ply"))
    {
        m_ID_L = m_OD_L;
        m_ID_H = m_OD_H;
        m_ID_W = m_OD_W;
    }


    if (m_PL.contains("SFK"))
    {
        m_ID_L  = "";
        m_ID_W  = "";
        m_ID_H  = "";
    }

    if (m_PL.contains("3 Ply"))
    {
        if (m_b == "True") {
            m_ID_L = QString::number(m_OD_L.toInt() - 3);
            m_ID_W = QString::number(m_OD_W.toInt() - 3);
            m_ID_H = QString::number(m_OD_H.toInt() - 6);
        }
        if (m_c == "True") {
            m_ID_L = QString::number(m_OD_L.toInt() - 4);
            m_ID_W = QString::number(m_OD_W.toInt() - 4);
            m_ID_H = QString::number(m_OD_H.toInt() - 7);
        }
        if (m_e == "True") {
            m_ID_L = QString::number(m_OD_L.toInt() - 2);
            m_ID_W = QString::number(m_OD_W.toInt() - 2);
            m_ID_H = QString::number(m_OD_H.toInt() - 5);
        }
    }

    if (m_PL.contains("5 Ply"))
    {
        m_ID_L = QString::number(m_OD_L.toInt() - 5);
        m_ID_W = QString::number(m_OD_W.toInt() - 5);
        m_ID_H = QString::number(m_OD_H.toInt() - 10);
    }

    if (m_PL.contains("Die Cut Carton 3 Ply"))
    {
        m_ID_L  = "";
        m_ID_W  = "";
        m_ID_H  = "";
    }

    if (m_PL.contains("Die Cut Carton 5 Ply"))
    {
        m_ID_L  = "";
        m_ID_W  = "";
        m_ID_H  = "";
    }

    recalculate();
}

void Product::paperSpecChanged()
{
    //qDebug() << "PaperSpec Changed. Calculating new values";

    recalculate();
}
QString Product::gram5() const
{
    return m_gram5;
}

void Product::setGram5(const QString &gram5)
{
    m_gram5 = gram5;
}

void Product::round_nplaces(double &value, const uint32_t &to)
{
    uint32_t places = 1, whole = *(&value);
    for(uint32_t i = 0; i < to; i++) places *= 10;
    value -= whole; //leave decimals
    value *= places;  //0.1234 -> 123.4
    value  = round2(value);//123.4 -> 123
    value /= places;  //123 -> .123
    value += whole; //bring the whole value back
}

QString Product::type5() const
{
    return m_type5;
}

double Product::round2(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

void Product::setType5(const QString &type5)
{
    m_type5 = type5;
}

QString Product::productCode() const
{
    return m_productCode;
}

void Product::setProductCode(const QString &productCode)
{
    m_productCode = productCode;
}

QString Product::PL() const
{
    return m_PL;
}

void Product::setPL(const QString &PL)
{
    m_PL = PL;
}

QString Product::Ply() const
{
    return m_Ply;
}

void Product::setPly(const QString &Ply)
{
    m_Ply = Ply;
    recalculate();
}

QString Product::description() const
{
    return m_description;
}

void Product::setDescription(const QString &description)
{
    m_description = description;
}

QString Product::ID_L() const
{
    return m_ID_L;
}

void Product::setID_L(const QString &ID_L)
{
    m_ID_L = ID_L;
}

QString Product::ID_W() const
{
    return m_ID_W;
}

void Product::setID_W(const QString &ID_W)
{
    m_ID_W = ID_W;
}

QString Product::ID_H() const
{
    return m_ID_H;
}

void Product::setID_H(const QString &ID_H)
{
    m_ID_H = ID_H;
}

QString Product::OD_L() const
{
    return m_OD_L;
}

void Product::setOD_L(const QString &OD_L)
{
    m_OD_L = OD_L;
}

QString Product::OD_W() const
{
    return m_OD_W;
}

void Product::setOD_W(const QString &OD_W)
{
    m_OD_W = OD_W;
}

QString Product::OD_H() const
{
    return m_OD_H;
}

void Product::setOD_H(const QString &OD_H)
{
    m_OD_H = OD_H;
}

QString Product::dieUnit() const
{
    return m_dieUnit;
}

void Product::setDieUnit(const QString &dieUnit)
{
    m_dieUnit = dieUnit;
}

QString Product::dieType() const
{
    return m_dieType;
}

void Product::setDieType(const QString &dieType)
{
    m_dieType = dieType;
}

QString Product::flap() const
{
    return m_flap;
}

void Product::setFlap(const QString &flap)
{
    m_flap = flap;
}

QString Product::waxing() const
{
    return m_waxing;
}

void Product::setWaxing(const QString &waxing)
{
    m_waxing = waxing;
}

QString Product::fitments() const
{
    return m_fitments;
}

void Product::setFitments(const QString &fitments)
{
    m_fitments = fitments;
}

QString Product::fitments_L() const
{
    return m_fitments_L;
}

void Product::setFitments_L(const QString &fitments_L)
{
    m_fitments_L = fitments_L;
}

QString Product::fitments_S() const
{
    return m_fitments_S;
}

void Product::setFitments_S(const QString &fitments_S)
{
    m_fitments_S = fitments_S;
}

QString Product::fitmentSlots() const
{
    return m_fitmentSlots;
}

void Product::setFitmentSlots(const QString &fitmentSlots)
{
    m_fitmentSlots = fitmentSlots;
}

QString Product::fitmentSlots_L() const
{
    return m_fitmentSlots_L;
}

void Product::setFitmentSlots_L(const QString &fitmentSlots_L)
{
    m_fitmentSlots_L = fitmentSlots_L;
}

QString Product::fitmentQtyS() const
{
    return m_fitmentQtyS;
}

void Product::setFitmentQtyS(const QString &fitmentQtyS)
{
    m_fitmentQtyS = fitmentQtyS;
}

QString Product::fitmentQtyL() const
{
    return m_fitmentQtyL;
}

void Product::setFitmentQtyL(const QString &fitmentQtyL)
{
    m_fitmentQtyL = fitmentQtyL;
}

QString Product::fitmentL() const
{
    return m_fitmentL;
}

void Product::setFitmentL(const QString &fitmentL)
{
    m_fitmentL = fitmentL;
}

QString Product::fitmentL_L() const
{
    return m_fitmentL_L;
}

void Product::setFitmentL_L(const QString &fitmentL_L)
{
    m_fitmentL_L = fitmentL_L;
}

QString Product::fitmentH() const
{
    return m_fitmentH;
}

void Product::setFitmentH(const QString &fitmentH)
{
    m_fitmentH = fitmentH;
}

QString Product::fitmentH_L() const
{
    return m_fitmentH_L;
}

void Product::setFitmentH_L(const QString &fitmentH_L)
{
    m_fitmentH_L = fitmentH_L;
}

QString Product::getLayerPads() const
{
    return m_layerPads;
}

void Product::setLayerPads(const QString &value)
{
    m_layerPads = value;
}

QString Product::getLayerPadsL() const
{
    return m_layerPadsL;
}

void Product::setLayerPadsL(const QString &value)
{
    m_layerPadsL = value;
}

QString Product::getLayerPadsH() const
{
    return m_layerPadsH;
}

void Product::setLayerPadsH(const QString &value)
{
    m_layerPadsH = value;
}

QString Product::getLayerPadsQty() const
{
    return m_layerPadsQty;
}

void Product::setLayerPadsQty(const QString &value)
{
    m_layerPadsQty = value;
}

QString Product::ink1() const
{
    return m_ink1;
}

void Product::setInk1(QString ink1)
{
    m_ink1 = ink1;
}

QString Product::ink2() const
{
    return m_ink2;
}

void Product::setInk2(QString ink2)
{
    m_ink2 = ink2;
}

QString Product::ink3() const
{
    return m_ink3;
}

void Product::setInk3(QString ink3)
{
    m_ink3 = ink3;
}

QString Product::ink4() const
{
    return m_ink4;
}

void Product::setInk4(QString ink4)
{
    m_ink4 = ink4;
}

QString Product::artwork() const
{
    return m_artwork;
}

void Product::setArtwork(const QString &artwork)
{
    m_artwork = artwork;
}

QString Product::sterio() const
{
    return m_sterio;
}

void Product::setSterio(const QString &sterio)
{
    m_sterio = sterio;
}

QString Product::sample() const
{
    return m_sample;
}

void Product::setSample(const QString &sample)
{
    m_sample = sample;
}

QString Product::b() const
{
    return m_b;
}

void Product::setB(const QString &b)
{
    m_b = b;
}

QString Product::c() const
{
    return m_c;
}

void Product::setC(const QString &c)
{
    m_c = c;
}

QString Product::e() const
{
    return m_e;
}

void Product::setE(const QString &e)
{
    m_e = e;
}

QString Product::gram1() const
{
    return m_gram1;
}

void Product::setGram1(const QString &gram1)
{
    m_gram1 = gram1;
}

QString Product::gram2() const
{
    return m_gram2;
}

void Product::setGram2(const QString &gram2)
{
    m_gram2 = gram2;
}

QString Product::gram3() const
{
    return m_gram3;
}

void Product::setGram3(const QString &gram3)
{
    //qDebug() << "Setting gram 3" << gram3;
    m_gram3 = gram3;
}

QString Product::gram4() const
{
    return m_gram4;
}

void Product::setGram4(const QString &gram4)
{
    m_gram4 = gram4;
}

QString Product::type1() const
{
    return m_type1;
}

void Product::setType1(const QString &type1)
{
    m_type1 = type1;
}

QString Product::type2() const
{
    return m_type2;
}

void Product::setType2(const QString &type2)
{
    m_type2 = type2;
}

QString Product::type3() const
{
    return m_type3;
}

void Product::setType3(const QString &type3)
{
    m_type3 = type3;
}

QString Product::type4() const
{
    return m_type4;
}

void Product::setType4(const QString &type4)
{
    m_type4 = type4;
}

QString Product::specialInstructions() const
{
    return m_specialInstructions;
}

void Product::setSpecialInstructions(const QString &specialInstructions)
{
    m_specialInstructions = specialInstructions;
}

QString Product::rp() const
{
    return m_rp;
}

void Product::setRp(const QString &rp)
{
    m_rp = rp;
}

QString Product::price() const
{
    return m_price;
}

void Product::setPrice(const QString &price)
{
    m_price = price;
}

QString Product::BL() const
{
    return m_BL;
}

void Product::setBL(const QString &BL)
{
    m_BL = BL;
}

QString Product::BW() const
{
    return m_BW;
}

void Product::setBW(const QString &BW)
{
    m_BW = BW;
}

QString Product::GSM() const
{
    return m_GSM;
}

void Product::setGSM(const QString &GSM)
{
    m_GSM = GSM;
}

QString Product::WT() const
{
    return m_WT;
}

void Product::setWT(const QString &WT)
{
    m_WT = WT;
}

QString Product::spec() const
{
    return m_spec;
}

void Product::setSpec(const QString &spec)
{
    m_spec = spec;
}

QString Product::ID() const
{
    return m_ID;
}

void Product::setID(const QString &ID)
{
    m_ID = ID;
}

QString Product::outs() const
{
    return m_outs;
}

void Product::setOuts(const QString &outs)
{
    m_outs = outs;
}

QString Product::dieInstructions() const
{
    return m_dieInstructions;
}

void Product::setDieInstructions(const QString &dieInstructions)
{
    m_dieInstructions = dieInstructions;
}

QString Product::confirmed() const
{
    return m_confirmed;
}

void Product::setConfirmed(const QString &confirmed)
{
    m_confirmed = confirmed;
}

QString Product::locked() const
{
    return m_locked;
}

void Product::setLocked(const QString &locked)
{
    m_locked = locked;
}

QString Product::F1() const
{
    return m_F1;
}

void Product::setF1(const QString &F1)
{
    m_F1 = F1;
}

QString Product::F2() const
{
    return m_F2;
}

void Product::setF2(const QString &F2)
{
    m_F2 = F2;
}

QString Product::F3() const
{
    return m_F3;
}

void Product::setF3(const QString &F3)
{
    m_F3 = F3;
}

QString Product::L() const
{
    return m_L;
}

void Product::setL(const QString &L)
{
    m_L = L;
}

QString Product::S() const
{
    return m_S;
}

void Product::setS(const QString &S)
{
    m_S = S;
}

QString Product::divided() const
{
    return m_divided;
}

void Product::setDivided(const QString &divided)
{
    m_divided = divided;
}

QString Product::noOfColors() const
{
    return m_noOfColors;
}

void Product::setNoOfColors(const QString &noOfColors)
{
    m_noOfColors = noOfColors;
}

QString Product::currency() const
{
    return m_currency;
}

void Product::setCurrency(const QString &currency)
{
    m_currency = currency;
}

QString Product::directorApproved() const
{
    return m_directorApproved;
}

void Product::setDirectorApproved(const QString &directorApproved)
{
    m_directorApproved = directorApproved;
}

QString Product::directorComment() const
{
    return m_directorComment;
}

void Product::setDirectorComment(const QString &directorComment)
{
    m_directorComment = directorComment;
}

QString Product::productType() const
{
    return m_productType;
}

void Product::setProductType(const QString &productType)
{
    m_productType = productType;
}

int Product::customerId() const
{
    return m_customerId;
}

void Product::setCustomerId(int customerId)
{
    m_customerId = customerId;
}




/*
 *query.prepare("UPDATE products SET "
                  ", Product = :Product "
                  ", Product Code = :ProductCode "
                  ", Customer = :Customer "
                  ", `Product Type` = :ProductType "
                  ", PL = :PL"
                  ", Ply = :Ply"
                  ", Description = :Description"
                  ", ID_L = :ID_L"
                  ", ID_W = :ID_W"
                  ", ID_H = :ID_H"
                  ", OD_L = :OD_L"
                  ", OD_W = :OD_W"
                  ", OD_H = :OD_H"
                  ", DieUnit = :DieUnit"
                  ", DieType = :DieType"
                  ", Flap = :Flap"
                  ", Waxing = :Waxing"
                  ", Fitments = :Fitments"
                  ", Fitments_L = :Fitments_L"
                  ", Fitments_S = :Fitments_S"
                  ", FitmentSlots = :FitmentSlots"
                  ", FitmentSlots_L = :FitmentSlots_L"
                  ", FitmentQtyS = :FitmentQtyS"
                  ", FitmentQtyL = :FitmentQtyL"
                  ", FitmentL = :FitmentL"
                  ", FitmentL_L = :FitmentL_L"
                  ", FitmentH = :Fitment_H"
                  ", FitmentH_L = :Fitment_H_L"
                  ", LayerPads = :LayerPads"
                  ", LayerPadsL = :LayerPadsL"
                  ", LayerPadsQty = :LayerPadsQty"
                  ", LayerPadsH = :LayerPadsH"
                  ", Ink1 = :Ink1"
                  ", Ink2 = :Ink2"
                  ", Ink3 = :Ink3"
                  ", Ink4 = :Ink4"
                  ", Artwork = :Artwork"
                  ", Sterio = :Sterio"
                  ", Sample = :Sample"
                  ", B = :B"
                  ", C = :C"
                  ", E = :E"
                  ", Gram1 = :Gram1"
                  ", Type1 = :Type1"
                  ", Gram2 = :Gram2"
                  ", Type2 = :Type2"
                  ", Gram3 = :Gram3"
                  ", Type3 = :Type3"
                  ", Gram4 = :Gram4"
                  ", Type4 = :Type4"
                  ", Gram5 = :Gram5"
                  ", Type5 = :Type5"
                  ", SpecialInstructions = :SpecialInstructions"
                  ", RetailPrice = :RP"
                  ", Price = :Price"
                  ", BL = :BL"
                  ", BW = :BW"
                  ", GSM = :GSM"
                  ", WT = :WT"
                  ", Spec = :Spec"
                  ", ID = :ID"
                  ", Outs = :Outs"
                  ", DieInstructions = :DieInstructions"
                  ", F1 = :F1"
                  ", F2 = :F2"
                  ", F3 = :F3"
                  ", L = :L"
                  ", S = :S"
                  ", Divided = :Divided"
                  ", NumberOfColors = :NoOfColors"
                  ", Currency = :Currency"
                  " WHERE `Product ID` = '" + m_productId + "'");

    query.bindValue(":Product",  m_productName);
    query.bindValue(":ProductCode", m_productCode);
    query.bindValue(":Customer", m_customerId);
    query.bindValue(":ProductType", m_productType);
    query.bindValue(":PL", m_PL);
    query.bindValue(":Ply", m_Ply);
    query.bindValue(":Description", m_description);
    query.bindValue(":ID_L", m_ID_L);
    query.bindValue(":ID_W", m_ID_W);
    query.bindValue(":ID_H", m_ID_H);
    query.bindValue(":OD_L", m_OD_L);
    query.bindValue(":OD_W", m_OD_W);
    query.bindValue(":OD_H", m_OD_H);
    query.bindValue(":DieUnit", m_dieUnit);
    query.bindValue(":DieType", m_dieType);
    query.bindValue(":Flap", m_flap);
    query.bindValue(":Waxing", m_waxing);
    query.bindValue(":Fitments", m_fitments);
    query.bindValue(":Fitments_L", m_fitments_L);
    query.bindValue(":Fitments_S", m_fitments_S);
    query.bindValue(":FitmentSlots", m_fitmentSlots);
    query.bindValue(":FitmentSlots_L", m_fitmentSlots_L);
    query.bindValue(":FitmentQtyS", m_fitmentQtyS);
    query.bindValue(":FitmentQtyL", m_fitmentQtyL);
    query.bindValue(":FitmentL", m_fitmentL);
    query.bindValue(":FitmentL_L", m_fitmentL_L);
    query.bindValue(":Fitment_H", m_fitmentH);
    query.bindValue(":Fitment_H_L", m_fitmentH_L);
    query.bindValue(":LayerPads", m_layerPads);
    query.bindValue(":LayerPadsL", m_layerPadsL);
    query.bindValue(":LayerPadsQty", m_layerPadsQty);
    query.bindValue(":LayerPadsH", m_layerPadsH);
    query.bindValue(":Ink1", m_ink1);
    query.bindValue(":Ink2", m_ink2);
    query.bindValue(":Ink3", m_ink3);
    query.bindValue(":Ink4", m_ink4);
    query.bindValue(":Artwork", m_artwork);
    query.bindValue(":Sterio", m_sterio);
    query.bindValue(":Sample", m_sample);
    query.bindValue(":B", m_b);
    query.bindValue(":C", m_c);
    query.bindValue(":E", m_e);
    query.bindValue(":Gram1", m_gram1);
    query.bindValue(":Type1", m_type1);
    query.bindValue(":Gram2", m_gram2);
    query.bindValue(":Type2", m_type2);
    query.bindValue(":Gram3", m_gram3);
    query.bindValue(":Type3", m_type3);
    query.bindValue(":Gram4", m_gram4);
    query.bindValue(":Type4", m_type4);
    query.bindValue(":Gram5", m_gram5);
    query.bindValue(":Type5", m_type5);
    query.bindValue(":SpecialInstructions", m_specialInstructions);
    query.bindValue(":RP", m_rp);
    query.bindValue(":Price", m_price);
    query.bindValue(":BL", m_BL);
    query.bindValue(":BW", m_BW);
    query.bindValue(":GSM", m_GSM);
    query.bindValue(":WT", m_WT);
    query.bindValue(":Spec", m_spec);
    query.bindValue(":ID", m_ID);
    query.bindValue(":Outs", m_outs);
    query.bindValue(":DieInstructions", m_dieInstructions);
    query.bindValue(":F1", m_F1);
    query.bindValue(":F2", m_F2);
    query.bindValue(":F3", m_F3);
    query.bindValue(":L", m_L);
    query.bindValue(":S", m_S);
    query.bindValue(":Divided", m_divided);
    query.bindValue(":NoOfColors", m_noOfColors);
    query.bindValue(":Currency", m_currency);

    */
