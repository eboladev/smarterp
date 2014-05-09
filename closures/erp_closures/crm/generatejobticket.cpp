#include "generatejobticket.h"
#include "ui_generatejobticket.h"
#include "jobticket.h"
#include <QtSql>
#include <QTextBrowser>
#include <QDateEdit>
#include <QTableWidget>
#include <QSpinBox>
#include <QLineEdit>
#include "datapublics.h"
GenerateJobTicket::GenerateJobTicket(QWidget *parent, QString ProductID) :
    QDialog(parent),
    m_productID(ProductID),
    ui(new Ui::GenerateJobTicket)
{
    ui->setupUi(this);
    JobTicket *jt = new JobTicket(this);
    setJobTicket(jt);
    m_jobTicket->setProductID(m_productID);

    QSqlQuery prodQu = QSqlDatabase::database("closures").exec("SELECT * FROM vw_products WHERE product_id = '" + m_productID + "'");
    if (!prodQu.lastError().isValid()) {
        prodQu.first();
        QString html = "<html>";
        html += "<table>";

        QString color_name = DataPublics::getDbValue(
                    "SELECT * FROM colors WHERE color_id = '" + prodQu.record().value("color").toString() + "'", QSqlDatabase::database(), "color_name")
                .toString();

        html += tr("<tr><td><b>Customer: </b></td><td>%1</td></tr>")
                .arg(prodQu.record().value("CompanyName").toString());
        html += tr("<tr><td><b>Telephone: </b></td><td>%1</td></tr>")
                .arg(prodQu.record().value("Telephone").toString());
        html += tr("<tr><td><b>Address: </b></td><td>%1</td></tr>")
                .arg(prodQu.record().value("Address").toString());

        html += tr("<tr><td><b>Product Name: </b></td><td>%1</td></tr>")
                .arg(prodQu.record().value("product_name").toString());

        m_jobTicket->setClosureName(prodQu.record().value("product_name").toString());

        html += tr("<tr><td><b>Product Code: </b></td><td>%1</td></tr>")
                .arg(prodQu.record().value("product_code").toString());
        html += tr("<tr><td><b>Weight: </b></td><td>%1</td></tr>")
                .arg(prodQu.record().value("wt").toString());
        html += tr("<tr><td><b>Color: </b></td><td>%1</td></tr>")
                .arg(color_name);

        html += "</table>";
        html += "</html>";
        ui->txtProductDetails->setHtml(html);

        ui->txtFinishing->setText(DataPublics::getDbValue("SELECT * FROM products WHERE product_id = '" + m_productID + "'", QSqlDatabase::database(), "finishing").toString());
    }

    ui->drpOrderDate->setDate(QDate::currentDate());
    ui->dtpRequiredDate->setDate(QDate::currentDate().addDays(4));

    ui->spinOrderQty->setValue(1);
    on_spinOrderQty_editingFinished();
}

GenerateJobTicket::~GenerateJobTicket()
{
    delete ui;
}
QString GenerateJobTicket::productID() const
{
    return m_productID;
}

void GenerateJobTicket::setProductID(const QString &productID)
{
    m_productID = productID;
}
JobTicket *GenerateJobTicket::jobTicket() const
{
    return m_jobTicket;
}

void GenerateJobTicket::setJobTicket(JobTicket *jobTicket)
{
    m_jobTicket = jobTicket;
    connect (m_jobTicket, SIGNAL(detailsChanged()), SLOT(refreshGui()));
}

QString GenerateJobTicket::lpoID() const
{
    return m_lpoID;
}

void GenerateJobTicket::setLpoID(const QString &lpoID)
{
    m_lpoID = lpoID;

    QSqlQuery lpoQuery = QSqlDatabase::database("closures").exec("SELECT * FROM purchase_orders_details WHERE EntryID = '" + m_lpoID  + "'");
    if (lpoQuery.lastError().isValid()) {
        QMessageBox::critical(this, "Error", "There was an error while looking for LPO Details\n\n" + lpoQuery.lastError().text());
        return;
    }
    lpoQuery.first();
    //All OK
    orderId = lpoQuery.record().value("OrderID").toString();

    QString lpoNo = DataPublics::getDbValue("SELECT * FROM purchase_orders WHERE EntryID = '" + orderId + "'", QSqlDatabase::database(), "OrderNo").toString();

    ui->txtLPONo->setText(lpoNo);
    ui->txtLPONo->setReadOnly(true);

    QPalette bg;
    QColor col(10,10,200);
    bg.setColor(QPalette::Background, col);
    ui->txtLPONo->setBackgroundRole(bg.Background);
}


void GenerateJobTicket::refreshGui()
{
    QLocale m_locale(QLocale::English, QLocale::Kenya);


    ui->txtOrderTotal->setText(m_locale.toCurrencyString(m_jobTicket->grandPrice()));
    ui->txtPacking->setText(m_jobTicket->packing());
    ui->txtHDPE->setText(QString::number(m_jobTicket->hdpe()));
    ui->txtInks->setText(QString::number(m_jobTicket->inks()));
    ui->txtMasterBatch->setText(QString::number(m_jobTicket->masterBatch()));


    QTableWidgetItem *bottleName = new QTableWidgetItem(m_jobTicket->bottleName());
    QTableWidgetItem *closureName = new QTableWidgetItem(m_jobTicket->closureName());
    QTableWidgetItem *piecePrice = new QTableWidgetItem(m_locale.toCurrencyString(m_jobTicket->piecePrice()));

    QTableWidgetItem *bottlePrice = new QTableWidgetItem(m_locale.toCurrencyString(m_jobTicket->bottlePrice()));
    QTableWidgetItem *capPrice = new QTableWidgetItem(m_locale.toCurrencyString(m_jobTicket->capPrice()));

    QTableWidgetItem *qty1 = new QTableWidgetItem(m_locale.toString(m_jobTicket->bottleQty()));
    QTableWidgetItem *qty2 = new QTableWidgetItem(m_locale.toString(ui->spinOrderQty->value()));


    QTableWidgetItem *bottleTotal= new QTableWidgetItem(m_locale.toCurrencyString(m_jobTicket->totalBottlePrice()));
    QTableWidgetItem *capTotal= new QTableWidgetItem(m_locale.toCurrencyString(m_jobTicket->totalCapPrice()));
    QTableWidgetItem *grandTotal= new QTableWidgetItem(m_locale.toCurrencyString(m_jobTicket->grandPrice()));

    ui->tblSalesDetails->setItem(0, 0, bottleName);
    ui->tblSalesDetails->setItem(1, 0, closureName);
    ui->tblSalesDetails->setItem(2, 2, piecePrice);
    ui->tblSalesDetails->setItem(0, 1, qty1);
    ui->tblSalesDetails->setItem(1, 1, qty2);
    ui->tblSalesDetails->setItem(0, 2, bottlePrice);
    ui->tblSalesDetails->setItem(1, 2, capPrice);
    ui->tblSalesDetails->setItem(0, 3, bottleTotal);
    ui->tblSalesDetails->setItem(1, 3, capTotal);
    ui->tblSalesDetails->setItem(2, 3, grandTotal);



    QTableWidgetItem *fullPacks = new QTableWidgetItem(m_locale.toString(m_jobTicket->fullPacks()));
    QTableWidgetItem *partialPacks = new QTableWidgetItem(m_locale.toString(m_jobTicket->partialPacks()));
    QTableWidgetItem *totalPacks = new QTableWidgetItem(m_locale.toString(m_jobTicket->totalPacks()));
    QTableWidgetItem *capsInFullPacks = new QTableWidgetItem(m_locale.toString(m_jobTicket->capsInFullPacks()));
    QTableWidgetItem *capsInPartialPacks = new QTableWidgetItem(m_locale.toString(m_jobTicket->capsInPartialPacks()));

    QTableWidgetItem *capsInFull = new QTableWidgetItem(m_locale.toString(m_jobTicket->totalCapsInFull()));
    QTableWidgetItem *capsInPart = new QTableWidgetItem(m_locale.toString(m_jobTicket->capsInPartialPacks()));
    QTableWidgetItem *allCaps = new QTableWidgetItem(m_locale.toString(m_jobTicket->packingCapsTotal()));


    ui->tblPackingBreakdown->setItem(0, 0, fullPacks);
    ui->tblPackingBreakdown->setItem(1, 0, partialPacks);
    ui->tblPackingBreakdown->setItem(2, 0, totalPacks);
    ui->tblPackingBreakdown->setItem(0, 1, capsInFullPacks);
    ui->tblPackingBreakdown->setItem(1, 1, capsInPartialPacks);
    ui->tblPackingBreakdown->setItem(0, 2, capsInFull);
    ui->tblPackingBreakdown->setItem(1, 2, capsInPart);
    ui->tblPackingBreakdown->setItem(2, 2, allCaps);
}



void GenerateJobTicket::on_spinOrderQty_editingFinished()
{
    m_jobTicket->setQty(ui->spinOrderQty->value());

    m_jobTicket->recalculate();
}

void GenerateJobTicket::on_cmdGenerateJobTicket_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("closures");
    QString customerID, customerName, productCode, productName;
    customerID = DataPublics::getDbValue("SELECT * FROM products WHERE product_id = '" + m_productID + "'", db, "customer_id").toString();
    customerName = DataPublics::getDbValue("SELECT * FROM customers WHERE CustomerID = '" + customerID + "'", db, "CompanyName").toString();
    productCode = DataPublics::getDbValue("SELECT * FROM products WHERE product_id = '" + m_productID + "'", db, "product_code").toString();
    productName = DataPublics::getDbValue("SELECT * FROM products WHERE product_id = '" + m_productID + "'", db, "product_name").toString();


    QLocale loc(QLocale::English, QLocale::Kenya);

    QString bottles = "no";
    if (m_jobTicket->hasBottles())
        bottles = "yes";

    QString query = "INSERT INTO oc (product_id, customer_id, customer_name, "
            "product_code, product_name, lpo_no, order_date, required_date,"
            "order_qty, total_price, price_per_piece, price_per_k, packing, caps_per_pack, "
            "hdpe, finishing, master_batch, bottle_name, bottle_price, bottle_qty, "
            "caps_in_full_packs, caps_in_partial_packs, full_packs, grand_price, has_bottles,"
            "packing_caps_total, partial_packs, total_bottle_price, total_cap_price,"
            "total_caps_in_full, total_caps_in_part, total_packs,"
            "inks) VALUES ('"
            + m_productID + "', '"
            + customerID  + "', '"
            + customerName  + "', '"
            + productCode  + "', '"
            + productName + "', '"
            + ui->txtLPONo->text() + "', '"
            + ui->drpOrderDate->date().toString("yyyy-MM-dd") + "', '"
            + ui->dtpRequiredDate->date().toString("yyyy-MM-dd") + "', '"
            + QString::number(ui->spinOrderQty->value())  + "', '"
            + ui->txtOrderTotal->text() + "', '"
            + m_jobTicket->pricePerPiece() + "', '"
            + m_jobTicket->pricePer1000() + "', '"
            + m_jobTicket->packing() + "', '"
            + m_jobTicket->piecesPerPack() + "', '"
            + QString::number(m_jobTicket->hdpe()) + "', '"
            + ui->txtFinishing->text() + "', '"
            + QString::number(m_jobTicket->masterBatch()) + "', '"
            + m_jobTicket->bottleName() + "', '"
            + QString::number(m_jobTicket->bottlePrice()) + "', '"
            + QString::number(m_jobTicket->bottleQty()) + "', '"
            + QString::number(m_jobTicket->capsInFullPacks()) + "', '"
            + QString::number(m_jobTicket->capsInPartialPacks()) + "', '"
            + QString::number(m_jobTicket->fullPacks()) + "', '"
            + QString::number(m_jobTicket->grandPrice()) + "', '"
            + bottles + "', '"
            + QString::number(m_jobTicket->packingCapsTotal()) + "', '"
            + QString::number(m_jobTicket->partialPacks()) + "', '"
            + QString::number(m_jobTicket->totalBottlePrice()) + "', '"
            + QString::number(m_jobTicket->totalCapPrice()) + "', '"
            + QString::number(m_jobTicket->totalCapsInFull()) + "', '"
            + QString::number(m_jobTicket->totalCapsInPart())  + "', '"
            + QString::number(m_jobTicket->totalPacks()) + "', '"
            + QString::number(m_jobTicket->inks()) + "')";

    QSqlQuery qu = db.exec(query);


//    if (qu.lastError().isValid()) {
//        DataPublics::showWarning(qu.lastError().text());
//    } else {
//        QString orderID = qu.lastInsertId().toString();
//        if (orderID.length() > 0) {
//            db.exec("UPDATE oc SET LastUpdated = NOW() WHERE entry_id = '" + orderID + "'");
//            ReportShower *rpt = new ReportShower(this, true);
//            rpt->addDateParam("Select Date", true);
//            rpt->prepareReport("OC", false, true, " WHERE entry_id = '" + orderID + "'");
//        }
//        this->accept();
//    }
}
