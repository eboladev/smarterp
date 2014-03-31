#include "editproduct.h"
#include "ui_editproduct.h"
#include "datapublics.h"
EditProduct::EditProduct(QWidget *parent, QSqlDatabase database, bool costing) :
    QDialog(parent), m_isCosting(costing),
    ui(new Ui::EditProduct)
{
    ui->setupUi(this);
    calculating = true;
    db = database;

    m_product = new Product(this, db);
    setProduct(m_product);
    connect (m_product, SIGNAL(detailsChanged()), this, SLOT(reloadDetails()));
    connect (m_product, SIGNAL(calculationChanged()), this, SLOT(reloadCalculated()));

    DataPublics::loadQueryToComboBox("SELECT * FROM colors ORDER BY ColorName", "ColorName", db, ui->Ink1);
    DataPublics::loadQueryToComboBox("SELECT * FROM colors ORDER BY ColorName", "ColorName", db, ui->Ink2);
    DataPublics::loadQueryToComboBox("SELECT * FROM colors ORDER BY ColorName", "ColorName", db, ui->Ink3);
    DataPublics::loadQueryToComboBox("SELECT * FROM colors ORDER BY ColorName", "ColorName", db, ui->Ink4);

    DataPublics::loadQueryToComboBox("SELECT * FROM dietypes  ORDER BY DieType", "DieType", db, ui->DieType);
    DataPublics::loadQueryToComboBox("SELECT * FROM dieunits Order BY DieUnit", "DieUnit", db, ui->DieUnit);
    DataPublics::loadQueryToComboBox("SELECT * FROM artwork ORDER By Artwork", "Artwork", db,  ui->Artwork);
    DataPublics::loadQueryToComboBox("SELECT * FROM sterio ORDER By Sterio", "Sterio", db,    ui->Sterio);
    DataPublics::loadQueryToComboBox("SELECT * FROM sample ORDER By Sample", "Sample", db,    ui->Sample);

    DataPublics::loadQueryToComboBox("SELECT * FROM customers ORDER By CompanyName", "CompanyName", db, ui->cboCustomer);


    ui->grpSFK->setVisible(false);


    connect (ui->txtID_H, SIGNAL(editingFinished()), SLOT(idChanged()));
    connect (ui->txtID_W, SIGNAL(editingFinished()), SLOT(idChanged()));
    connect (ui->txtID_L, SIGNAL(editingFinished()), SLOT(idChanged()));

    connect (ui->txtOD_L, SIGNAL(editingFinished()), SLOT(odChanged()));
    connect (ui->txtOD_W, SIGNAL(editingFinished()), SLOT(odChanged()));
    connect (ui->txtOD_H, SIGNAL(editingFinished()), SLOT(odChanged()));

    connect (ui->txtGram1, SIGNAL(editingFinished()), SLOT(paperSpecChanged()));
    connect (ui->txtGram2, SIGNAL(editingFinished()), SLOT(paperSpecChanged()));
    connect (ui->txtGram3, SIGNAL(editingFinished()), SLOT(paperSpecChanged()));
    connect (ui->txtGram4, SIGNAL(editingFinished()), SLOT(paperSpecChanged()));
    connect (ui->txtGram5, SIGNAL(editingFinished()), SLOT(paperSpecChanged()));

    connect (ui->cboType1, SIGNAL(currentIndexChanged(int)), SLOT(paperSpecChanged()));
    connect (ui->cboType2, SIGNAL(currentIndexChanged(int)), SLOT(paperSpecChanged()));
    connect (ui->cboType3, SIGNAL(currentIndexChanged(int)), SLOT(paperSpecChanged()));
    connect (ui->cboType4, SIGNAL(currentIndexChanged(int)), SLOT(paperSpecChanged()));
    connect (ui->cboType5, SIGNAL(currentIndexChanged(int)), SLOT(paperSpecChanged()));

    connect (ui->txtBL, SIGNAL(editingFinished()), SLOT(boardChanged()));
    connect (ui->txtBW, SIGNAL(editingFinished()), SLOT(boardChanged()));

    connect (ui->txtF1, SIGNAL(editingFinished()), SLOT(boardChanged()));
    connect (ui->txtF2, SIGNAL(editingFinished()), SLOT(boardChanged()));
    connect (ui->txtF3, SIGNAL(editingFinished()), SLOT(boardChanged()));
    connect (ui->txtS, SIGNAL(editingFinished()), SLOT(boardChanged()));
    connect (ui->txtL, SIGNAL(editingFinished()), SLOT(boardChanged()));

    connect (ui->cboOuts, SIGNAL(currentIndexChanged(int)), SLOT(boardChanged()));

    connect (ui->txtPrice, SIGNAL(editingFinished()), SLOT(recalculateAll()));

    if (costing) {
        ui->cmdSaveChanges->setVisible(false);
        ui->cmdDelete->setVisible(false);
        ui->txtProductCode->setEnabled(false);
        ui->txtProductName->setEnabled(false);
        ui->cboCustomer->setEnabled(false);
    }

    ui->lblChanges->setVisible(false);
    changesCount = 0;
    changesTimer = new QTimer(this);
    connect (changesTimer, SIGNAL(timeout()), SLOT(onChangesTimer()));
    changesTimer->start(500);
}

EditProduct::~EditProduct()
{
    delete ui;
}

void EditProduct::Edit(QString ProductID)
{
    m_product->setProductId(ProductID);
}
Product *EditProduct::getProduct() const
{
    return m_product;
}

void EditProduct::setProduct(Product *value)
{
    m_product = value;
}

void EditProduct::reloadDetails()
{
    calculating = false;
    ui->txtPrice->setText(m_product->price());

    ui->txtProductName->setText(m_product->productName());
    ui->txtProductCode->setText(m_product->productCode());
    QString customerName = DataPublics::getDbValue("SELECT * FROM customers WHERE CustomerID = '" + QString::number(m_product->customerId()) + "'", db, "CompanyName").toString();
    ui->cboCustomer->setCurrentText(customerName);
    ui->cboPL->setCurrentText(m_product->PL());

    ui->DieUnit->setCurrentText(m_product->dieUnit());
    ui->DieType->setCurrentText(m_product->dieType());
    ui->cboFlap->setCurrentText(m_product->flap());
    ui->cboWaxing->setEditText(m_product->waxing());
    //Fitments
    //LayerPads
    ui->Ink1->setEditText(m_product->ink1() );
    ui->Ink2->setEditText(m_product->ink2() );
    ui->Ink3->setEditText(m_product->ink3() );
    ui->Ink4->setEditText(m_product->ink4() );

    ui->Artwork->setCurrentText(m_product->artwork());
    ui->Sterio->setCurrentText(m_product->sterio());
    ui->Sample->setCurrentText(m_product->sample());

    ui->optB->setChecked(m_product->b() == "True");
    ui->optC->setChecked(m_product->c() == "True");
    ui->optE->setChecked(m_product->e() == "True");

    //qDebug() << m_product->gram1() << m_product->gram2();

    ui->txtGram1->setText(m_product->gram1());
    ui->txtGram2->setText(m_product->gram2());
    ui->txtGram3->setText(m_product->gram3());
    ui->txtGram4->setText(m_product->gram4());
    ui->txtGram5->setText(m_product->gram5());

    ui->cboType1->setCurrentText(m_product->type1());
    ui->cboType2->setCurrentText(m_product->type2());
    ui->cboType3->setCurrentText(m_product->type3());
    ui->cboType4->setCurrentText(m_product->type4());
    ui->cboType5->setCurrentText(m_product->type5());

    ui->txtSpecialIinstructions->setPlainText(m_product->specialInstructions());


    ui->cboFlap->setEditText(m_product->flap());
    ui->cboFitments->setEditText(m_product->fitments());


    ui->txtFitmentsSlotsL->setText(m_product->fitmentSlots_L());
    ui->txtFitmentsSlotsS->setText(m_product->fitmentSlots());

    ui->txtFitmentsQrtL->setText(m_product->fitmentQtyL());
    ui->txtFitmentsQtyS->setText(m_product->fitmentQtyS());

    ui->txtFitmentsLL->setText(m_product->fitmentL_L());
    ui->txtFitmentsLS->setText(m_product->fitmentL());

    ui->txtFitmentsHS->setText(m_product->fitmentH());
    ui->txtFirmentsHL->setText(m_product->fitmentH_L());


    ui->cboLayerPads->setEditText(m_product->getLayerPads());
    ui->txtLayerPadsH->setText(m_product->getLayerPadsH());
    ui->txtLayerPadsL->setText(m_product->getLayerPadsL());
    ui->txtLayerPadsQTy->setText(m_product->getLayerPadsQty());

    ui->cboCurrency->setCurrentText(m_product->currency());

    if (m_product->directorApproved() == "Yes")
    {
        disableInputs();
    } else {
        plyChanged();
        calculating = true;
    }

    ui->NoOfInks->setValue(m_product->noOfColors().toInt());
    on_NoOfInks_valueChanged(m_product->noOfColors().toInt());
}

void EditProduct::plyChanged()
{

    ui->txtBL->setEnabled(false);
    ui->txtBW->setEnabled(false);

    ui->txtGram1->setEnabled(false);
    ui->txtGram2->setEnabled(false);
    ui->txtGram3->setEnabled(false);
    ui->txtGram4->setEnabled(false);
    ui->txtGram5->setEnabled(false);

    ui->cboType1->setEnabled(false);
    ui->cboType2->setEnabled(false);
    ui->cboType3->setEnabled(false);
    ui->cboType4->setEnabled(false);
    ui->cboType5->setEnabled(false);

    ui->grpID->setEnabled(false);
    ui->grpOD->setEnabled(false);

    ui->grpID->setVisible(true);
    ui->grpOD->setVisible(true);

    ui->cboOuts->setVisible(false);
    ui->txtDivided->setEnabled(false);
    ui->grpSFK->setVisible(false);

    if (ui->cboPL->currentText() == "2 Ply") {
        ui->groupBox5->setEnabled(true);
        ui->grpID->setEnabled(true);
        ui->grpOD->setEnabled(true);
        enable2();
    }

    if (ui->cboPL->currentText() == "SFK") {
        enable2();
        calculating = false;
        clearDimensions();
        calculating = true;
    }

    if (ui->cboPL->currentText() == "3 Ply") {

        ui->groupBox5->setEnabled(true);
        ui->grpID->setEnabled(true);
        ui->grpOD->setEnabled(true);
        enable3();
    }

    if (ui->cboPL->currentText() == "5 Ply") {
        ui->groupBox5->setEnabled(true);
        ui->grpID->setEnabled(true);
        ui->grpOD->setEnabled(true);
        enable5();
    }

    if (ui->cboPL->currentText().startsWith("Die Cut Carton 3")) {
        ui->groupBox5->setEnabled(true);
        enable3();

        ui->cboOuts->setVisible(true);
    }

    if (ui->cboPL->currentText().startsWith("Die Cut Carton 5")) {
        enable5();

        ui->cboOuts->setVisible(true);
    }

    if (ui->cboPL->currentText().contains("Die")) {
        clearDimensions();
        ui->grpID->setVisible(false);
        ui->grpOD->setVisible(false);
        ui->groupBox5->setVisible(false);

        ui->grpSFK->setVisible(true);

        ui->txtBL->setDisabled(false);
        ui->txtBW->setDisabled(false);
        ui->cboOuts->setVisible(true);
        ui->cboOuts->setEnabled(true);
    }

    if (ui->cboPL->currentText().contains("SFK")) {
        clearDimensions();
        ui->grpID->setVisible(false);
        ui->grpOD->setVisible(false);
        ui->txtBL->setDisabled(true);
        ui->txtBW->setDisabled(true);
    }

    ui->txtF1->setDisabled(true);
    ui->txtF2->setDisabled(true);
    ui->txtF3->setDisabled(true);
    ui->txtS->setDisabled(true);
    ui->txtL->setDisabled(true);


    if (ui->cboPL->currentText().contains("Ply (H)")) {
        ui->txtF1->setDisabled(false);
        ui->txtF2->setDisabled(false);
        ui->txtF3->setDisabled(false);
        ui->txtS->setDisabled(true);
        ui->txtL->setDisabled(true);
    }

    if (ui->cboPL->currentText().contains("Die")) {
        if (ui->cboPL->currentText().contains("(H)")) {
            ui->txtS->setText("0");
            ui->txtL->setText("0");
        } else {
            ui->txtF1->setText("0");
            ui->txtF2->setText("0");
            ui->txtF3->setText("0");
        }
    }

}

void EditProduct::enable2()
{
    ui->txtGram1->setEnabled(true);
    ui->txtGram2->setEnabled(true);
    ui->cboType1->setEnabled(true);
    ui->cboType2->setEnabled(true);

}

void EditProduct::enable3()
{
    enable2();
    ui->txtGram3->setEnabled(true);
    ui->cboType3->setEnabled(true);
}

void EditProduct::enable5()
{
    enable3();
    ui->txtGram4->setEnabled(true);
    ui->txtGram5->setEnabled(true);
    ui->cboType4->setEnabled(true);
    ui->cboType5->setEnabled(true);
}

void EditProduct::clearDimensions()
{
    ui->txtID_H->setText("");
    ui->txtID_L->setText("");
    ui->txtID_W->setText("");
    ui->txtOD_L->setText("");
    ui->txtOD_W->setText("");
    ui->txtOD_H->setText("");
}

int EditProduct::countBCE()
{
    int ret = 0;

    if (ui->optB->isChecked())
        ret++;

    if (ui->optC->isChecked())
        ret++;

    if (ui->optE->isChecked())
        ret++;

    return ret;
}

void EditProduct::checkBCE(QCheckBox *chk)
{
    if (ui->cboPL->currentText().contains("3")) {
        if (countBCE() > 1)
            chk->setChecked(false);
    }

    if (ui->cboPL->currentText().contains("5")) {
        if (countBCE() > 2)
            chk->setChecked(false);
    }
    recalculateAll();
}


void EditProduct::on_cboPL_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    plyChanged();
    if (calculating) {
        m_product->setPly(ui->cboPL->currentText());
    }
}

void EditProduct::on_optB_toggled(bool checked)
{
    Q_UNUSED(checked);
    checkBCE(ui->optB);
}

void EditProduct::on_optE_toggled(bool checked)
{
    Q_UNUSED(checked);
    checkBCE(ui->optE);
}

void EditProduct::on_optC_toggled(bool checked)
{
    Q_UNUSED(checked);
    checkBCE(ui->optC);
}

void EditProduct::reloadCalculated()
{
    calculating = false;
    //qDebug() << "Reloading calculated values on gui...";
    ui->txtID_L->setText(m_product->ID_L());
    ui->txtID_W->setText(m_product->ID_W());
    ui->txtID_H->setText(m_product->ID_H());
    ui->txtOD_L->setText(m_product->OD_L());
    ui->txtOD_W->setText(m_product->OD_W());
    ui->txtOD_H->setText(m_product->OD_H());

    ui->txtRP->setText(m_product->rp());
    // ui->txtPrice->setText(m_product->price());

    ui->txtBL->setText(m_product->BL());
    ui->txtBW->setText(m_product->BW());
    ui->txtGSM->setText(m_product->GSM());
    ui->txtWt->setText(m_product->WT());

    ui->txtDivided->setText(m_product->divided());
    ui->cboOuts->setCurrentText(m_product->outs());

    //SFK
    ui->txtF1->setText(m_product->F1());
    ui->txtF2->setText(m_product->F2());
    ui->txtF3->setText(m_product->F3());
    ui->txtS->setText(m_product->S());
    ui->txtL->setText(m_product->L());


    if (ui->cboPL->currentText().contains("Die") && !ui->cboPL->currentText().contains("Ply (H)")) {
        ui->txtF1->setDisabled(true);
        ui->txtF2->setDisabled(true);
        ui->txtF3->setDisabled(true);
        ui->txtS->setDisabled(false);
        ui->txtL->setDisabled(false);
    }
    else if (ui->cboPL->currentText().contains("Die") && ui->cboPL->currentText().contains("Ply (H)")) {
        ui->txtF1->setDisabled(false);
        ui->txtF2->setDisabled(false);
        ui->txtF3->setDisabled(false);
        ui->txtS->setDisabled(true);
        ui->txtL->setDisabled(true);
    }

    calculating = true;
}

void EditProduct::idChanged()
{
    //qDebug() << "ID Changed";
    if (calculating) {
        saveID();
        m_product->idChanged();
    }
}

void EditProduct::odChanged()
{
    //qDebug() << "OD Changed";
    if (calculating) {
        saveOD();
        m_product->odChanged();
    }
}

void EditProduct::saveID()
{
    m_product->setID_H(ui->txtID_H->text());
    m_product->setID_L(ui->txtID_L->text());
    m_product->setID_W(ui->txtID_W->text());
}

void EditProduct::saveOD()
{
    m_product->setOD_H(ui->txtOD_H->text());
    m_product->setOD_L(ui->txtOD_L->text());
    m_product->setOD_W(ui->txtOD_W->text());
}

void EditProduct::savePaperSpec()
{
    QString b = "False", c= "False", e = "False";
    if (ui->optB->isChecked())
        b = "True";

    if (ui->optC->isChecked())
        c = "True";

    if (ui->optE->isChecked())
        e = "True";

    m_product->setB(b);
    m_product->setC(c);
    m_product->setE(e);

    m_product->setPL(ui->cboPL->currentText());

    m_product->setGram1(ui->txtGram1->text());
    m_product->setGram2(ui->txtGram2->text());
    m_product->setGram3(ui->txtGram3->text());
    m_product->setGram4(ui->txtGram4->text());
    m_product->setGram5(ui->txtGram5->text());

    m_product->setType1(ui->cboType1->currentText());
    m_product->setType2(ui->cboType2->currentText());
    m_product->setType3(ui->cboType3->currentText());
    m_product->setType4(ui->cboType4->currentText());
    m_product->setType5(ui->cboType5->currentText());

    if (calculating) {
        m_product->paperSpecChanged();
    }

}

void EditProduct::saveBoardDetails()
{
    m_product->setOuts(ui->cboOuts->currentText());
    m_product->setF1(ui->txtF1->text());
    m_product->setF2(ui->txtF2->text());
    m_product->setF3(ui->txtF3->text());

    m_product->setS(ui->txtS->text());
    m_product->setL(ui->txtL->text());

    m_product->setBL(ui->txtBL->text());
    m_product->setBW(ui->txtBW->text());

    if (calculating) {
        m_product->paperSpecChanged();
    }
}

void EditProduct::boardChanged()
{
    if (calculating) {
        saveBoardDetails();
        m_product->paperSpecChanged();
    }
}

void EditProduct::paperSpecChanged()
{
    //qDebug() << "Paper Spec Changed";
    if (calculating) {
        savePaperSpec();
        m_product->paperSpecChanged();
    }
}

void EditProduct::recalculateAll()
{
    if (calculating) {
        m_product->setPrice(ui->txtPrice->text());
        saveID();
        saveOD();
        savePaperSpec();
        saveBoardDetails();
        m_product->recalculate();
    }
}

void EditProduct::on_cmdSaveChanges_clicked()
{
    m_product->setProductName(ui->txtProductName->text());
    m_product->setProductCode(ui->txtProductCode->text());
    m_product->setPL(ui->cboPL->currentText());
    m_product->setDescription(ui->txtDescription->toPlainText());
    m_product->setSpecialInstructions(ui->txtSpecialIinstructions->toPlainText());
    m_product->setCurrency(ui->cboCurrency->currentText());


    m_product->setOuts(ui->cboOuts->currentText());

    m_product->setNoOfColors(QString::number(ui->NoOfInks->value()));
    m_product->setInk1(ui->Ink1->currentText());
    m_product->setInk2(ui->Ink2->currentText());
    m_product->setInk3(ui->Ink3->currentText());
    m_product->setInk4(ui->Ink4->currentText());

    m_product->setFitments(ui->cboFitments->currentText());
    m_product->setFlap(ui->cboFlap->currentText());
    m_product->setWaxing(ui->cboWaxing->currentText());

    int customerID = DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'"
                                             , db, "CustomerID").toInt();
    m_product->setCustomerId(customerID);


    m_product->setFitmentSlots_L(ui->txtFitmentsSlotsL->text());
    m_product->setFitmentSlots(ui->txtFitmentsSlotsS->text());

    m_product->setFitmentQtyL(ui->txtFitmentsQrtL->text());
    m_product->setFitmentQtyS(ui->txtFitmentsQtyS->text());

    m_product->setFitmentL_L(ui->txtFitmentsLL->text());
    m_product->setFitmentL(ui->txtFitmentsLS->text());

    m_product->setFitmentH(ui->txtFitmentsHS->text());
    m_product->setFitmentH_L(ui->txtFirmentsHL->text());

    m_product->setLayerPads(ui->cboLayerPads->currentText());
    m_product->setLayerPadsH(ui->txtLayerPadsH->text());
    m_product->setLayerPadsL(ui->txtLayerPadsL->text());
    m_product->setLayerPadsQty(ui->txtLayerPadsQTy->text());

    m_product->save();
    changesCount = 0;
    ui->lblChanges->setVisible(true);
    emit changed();
}

void EditProduct::disableInputs()
{
    disableParent(this);
}

void EditProduct::disableParent(QWidget *parent)
{
    for (int i = 0; i < parent->children().count(); i++) {
        //qDebug() << "Disabling " << parent->children().at(i)->objectName();
        if (parent->children().at(i)->children().count() > 0) {
            if (qobject_cast<QWidget *>(parent->children().at(i))) {
                QWidget *wid = qobject_cast<QWidget *>(parent->children().at(i));
                //qDebug() << "This is a parent" << wid->objectName();
                if (wid->children().count() > 0) {
                    wid->setDisabled(true);
                    disableParent(wid);
                }
            }
        } else {
            if (qobject_cast<QLineEdit *>(parent->children().at(i))) {
                QLineEdit *txt = qobject_cast<QLineEdit *>(parent->children().at(i));
                txt->setEnabled(false);
                //qDebug() << "Disabled Text Box" << txt->objectName();
            }
            if (qobject_cast<QComboBox *>(parent->children().at(i))) {
                QComboBox *cbo = qobject_cast<QComboBox *>(parent->children().at(i));
                cbo->setEnabled(false);
                //qDebug() << "Disabled Combo Box" << cbo->objectName();
            }

            if (qobject_cast<QCheckBox *>(parent->children().at(i))) {
                QCheckBox *thisWidget = qobject_cast<QCheckBox *>(parent->children().at(i));
                thisWidget->setEnabled(false);
                //qDebug() << "Disabled Check Box" << thisWidget->objectName();
            }

            if (qobject_cast<QSpinBox *>(parent->children().at(i))) {
                QSpinBox *thisWidget = qobject_cast<QSpinBox *>(parent->children().at(i));
                thisWidget->setEnabled(false);
                //qDebug() << "Disabled Spin Box" << thisWidget->objectName();
            }

            if (qobject_cast<QPushButton *>(parent->children().at(i))) {
                QPushButton *thisWidget = qobject_cast<QPushButton *>(parent->children().at(i));
                thisWidget->setEnabled(false);
                //qDebug() << "Disabled PushButton" << thisWidget->objectName();
            }
        }
    }
}

void EditProduct::on_cmdDelete_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this product?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        QString qu = "DELETE FROM products WHERE `Product Id` = '" + m_product->productId() + "'";
        //DataPublics::showInformation(qu);
        db.exec(qu);
        if (db.lastError().isValid()) {
            DataPublics::showWarning(db.lastError().text());
            return;
        }
        emit changed();
        this->close();
    }
}

void EditProduct::on_NoOfInks_valueChanged(int arg1)
{
    ui->Ink1->setEnabled(false);
    ui->Ink2->setEnabled(false);
    ui->Ink3->setEnabled(false);
    ui->Ink4->setEnabled(false);
    if (arg1 > 0) {
        ui->Ink1->setEnabled(true);
    }
    if (arg1 > 1) {
        ui->Ink2->setEnabled(true);
    }
    if (arg1 > 2) {
        ui->Ink3->setEnabled(true);
    }
    if (arg1 > 3) {
        ui->Ink4->setEnabled(true);
    }
}

void EditProduct::onChangesTimer()
{
    changesCount++;
    if (changesCount>3)
        ui->lblChanges->setVisible(false);
}
bool EditProduct::isCosting() const
{
    return m_isCosting;
}

void EditProduct::setIsCosting(bool isCosting)
{
    m_isCosting = isCosting;
}

