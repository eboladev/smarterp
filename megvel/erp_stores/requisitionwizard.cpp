#include "requisitionwizard.h"
#include "ui_requisitionwizard.h"
#include <QtSql>
#include "datapublics.h"
#include <QDebug>

RequisitionWizard::RequisitionWizard(QWidget *parent, bool isFilm) :
    QWizard(parent),
    ui(new Ui::RequisitionWizard)
{
    saved = false;
    ui->setupUi(this);
    m_isFilm = isFilm;
    QSqlDatabase db = QSqlDatabase::database();

    DataPublics::loadQueryToComboBox("SELECT * FROM suppliers ORDER By SupplierName", "SupplierName", db, ui->cboSupplier);

    //    QSqlQuery qu = db.exec("SELECT * FROM inventory ORDER BY ItemName");
    //    if (qu.lastError().isValid()) {
    //        DataPublics::showWarning(qu.lastError().text());
    //    } else {
    //        while (qu.next()) {
    //            QTableWidgetItem *nameItem = new QTableWidgetItem(1);
    //            QTableWidgetItem *idItem = new QTableWidgetItem(1);
    //            QTableWidgetItem *onHandItem = new QTableWidgetItem(1);
    //            QTableWidgetItem *reorderLevelItem = new QTableWidgetItem(1);
    //            QTableWidgetItem *requiredItem = new QTableWidgetItem(1);

    //            idItem->setText(qu.record().value("ItemID").toString());
    //            nameItem->setText(qu.record().value("ItemName").toString());
    //            onHandItem->setText(qu.record().value("OnHand").toString());
    //            reorderLevelItem->setText(qu.record().value("ReorderLevel").toString());
    //            requiredItem->setText("0");

    //            int row = ui->tblSelectedItems->rowCount();
    //            ui->tblSelectedItems->insertRow(row);

    //            ui->tblSelectedItems->setItem(row, 4, idItem);
    //            ui->tblSelectedItems->setItem(row, 0, nameItem);
    //            ui->tblSelectedItems->setItem(row, 1, onHandItem);
    //            ui->tblSelectedItems->setItem(row, 2, reorderLevelItem);
    //            ui->tblSelectedItems->setItem(row, 3, requiredItem);
    //        }
    //        ui->tblSelectedItems->resizeColumnToContents(0);
    //        ui->tblSelectedItems->resizeRowsToContents();
    //        ui->tblSelectedItems->setColumnHidden(4, true);
    //    }

    ui->dtpDateRequested->setDate(QDate::currentDate());
    ui->dtpDateRequired->setDate(QDate::currentDate());

    reloadDetails();
}

RequisitionWizard::~RequisitionWizard()
{
    delete ui;
}

void RequisitionWizard::on_RequisitionWizard_currentIdChanged(int id)
{
    Q_UNUSED(id);
    reloadDetails();
}

void RequisitionWizard::reloadDetails()
{
    //    QString html = "<h2>Requisition Note</h2>";
    //    html += "<b>Supplier:</b> " + ui->cboSupplier->currentText() + "<br/>";
    //    html += "<b>Requesed by:</b> " + ui->txtRequestedBy->text() + " <b>department:</b> " +
    //            ui->txtDepartment->text() + "<br/>";
    //    html += "<b>Requisition Date:</b> " + ui->dtpDateRequested->date().toString("dd MMM yyyy") + "<br/>";
    //    html += "<b>Required Date:</b> " + ui->dtpDateRequired->date().toString("dd MMM yyyy") + "<br/>";
    //    html += "<br/>";
    //    html += "<br/>";
    //    html += "<b>Requisition Items</b><br/>";

    //    html += "<table width = 30%, cellpadding=0 cellspacing=0, border=1>";
    //    html += "<tr><td>Item</td> <td>On Hand</td> <td>Reorder Level</td> <td>Required Items</td></tr>";
    //    for (int i = 0; i < ui->tblSelectedItems->rowCount(); i++) {
    //        if (ui->tblSelectedItems->item(i, 3)->text() != "0") {
    //            //add item
    //            html += "<tr>";
    //            html += "<td>" + ui->tblSelectedItems->item(i, 0)->text() + "</td>";
    //            html += "<td>" + ui->tblSelectedItems->item(i, 1)->text() + "</td>";
    //            html += "<td>" + ui->tblSelectedItems->item(i, 2)->text() + "</td>";
    //            html += "<td>" + ui->tblSelectedItems->item(i, 3)->text() + "</td>";
    //            html += "</tr>";
    //        }
    //    }

    //    html += "</table>";
    //    ui->txtRqnDetails->setText(html);
}

void RequisitionWizard::saveRequisition()
{
    if (saved) {
        this->accept();
    }
    saved = true;
    int cnt = ui->lstRequisition->invisibleRootItem()->childCount();
    //    for (int i = 0; i < ui->tblSelectedItems->rowCount(); ++i) {
    //        if (ui->tblSelectedItems->item(i, 3)->text() != "0") {
    //            cnt = cnt + 1;
    //        }
    //    }
    if (cnt == 0) {
        DataPublics::showWarning("No items have been requested. Ensure that at least one item has a requested value of more that 1.");
        return;
    }
    QSqlDatabase db = QSqlDatabase::database();
    QString supplierID = DataPublics::getDbValue(
                "SELECT * FROM suppliers WHERE SupplierName = '" + ui->cboSupplier->currentText() + "'"
                , db, "SupplierID").toString();

    QSqlQuery masterQu = db.exec("INSERT INTO store_requisition_master (RequisitionDate,"
                                 "DateRequired, SupplierID, RequestedBy, Department, Status) VALUES ('"
                                 + ui->dtpDateRequested->date().toString("yyyy-MM-dd") + "', '"
                                 + ui->dtpDateRequired->date().toString("yyyy-MM-dd")  + "', '"
                                 + supplierID + "', '"
                                 + ui->txtRequestedBy->text()  + "', '"
                                 + ui->txtDepartment->text() + "', 'Pending')");
    if (masterQu.lastError().isValid()) {
        DataPublics::showWarning(masterQu.lastError().text());
        return;
    }

    QString masterID = masterQu.lastInsertId().toString();
    QString detailError = "";
    for (int iii = 0; iii < ui->lstRequisition->invisibleRootItem()->childCount(); iii++) {
        //if (ui->tblSelectedItems->item(i, 3)->text() != "0") {
        qDebug() << iii;
        QTreeWidgetItem *it = ui->lstRequisition->invisibleRootItem()->child(iii);
        qDebug() << it->text(0);
        QString itemID = DataPublics::getDbValue("SELECT * FROM inventory WHERE ItemName = '" + it->text(0).split("(").at(0) + "'", db, "ItemID").toString();
        QString qty = it->text(1);
        QSqlQuery detailQu = db.exec("INSERT INTO store_requisition_detail"
                                     "(MasterID, ItemID, ItemName, UnitPrice, VATPercent, Qty) VALUES ('"
                                     + masterID + "', '"
                                     + itemID  + "', '"
                                     + it->text(0)  + "', '"
                                     + it->text(3)  + "', '"
                                     + it->text(4)  + "', '"
                                     + qty + "')");
        if (detailQu.lastError().isValid())
            detailError.append("\n" + detailQu.lastError().text());

        //}
        if (iii > 10) {
            break;
        }
    }
    if (detailError.length() > 0) {
        DataPublics::showWarning("The following errors have occurred:\n\n" + detailError);
        return;
    }

    this->accept();
}

void RequisitionWizard::on_tblSelectedItems_cellChanged(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    // reloadDetails();
}

void RequisitionWizard::on_cboSupplier_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    reloadDetails();
}

void RequisitionWizard::on_txtRequestedBy_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    reloadDetails();
}

void RequisitionWizard::on_txtDepartment_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    reloadDetails();
}

void RequisitionWizard::on_dtpDateRequested_dateTimeChanged(const QDateTime &dateTime)
{
    Q_UNUSED(dateTime);
    reloadDetails();
}

void RequisitionWizard::on_dtpDateRequested_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    reloadDetails();
}

void RequisitionWizard::on_dtpDateRequired_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    reloadDetails();
}

void RequisitionWizard::on_cmdFinish_clicked()
{
    saveRequisition();
}

void RequisitionWizard::on_RequisitionWizard_finished(int result)
{
    Q_UNUSED(result);
}

#include "additemtorequistion.h"
#include "addartworktorequisition.h"
void RequisitionWizard::on_cmdAddItemToRequisition_clicked()
{
    if (!m_isFilm) {
        AddItemToRequistion *adder = new AddItemToRequistion(this);
        if (adder->exec() == QDialog::Accepted) {
            QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstRequisition);
            it->setText(0, adder->itemName);
            it->setText(1, QString::number(adder->qty));
            it->setText(3, QString::number(adder->unitPrice));
            it->setText(4, QString::number(adder->vat));
        }
    }  else {
        AddArtworkToRequisition *newFilm = new AddArtworkToRequisition(this);
        if (newFilm->exec() == QDialog::Accepted) {
            QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstRequisition);
            QString quoteNumber = QInputDialog::getText(this, "Quote Number", "Enter the quote number");
            it->setText(0, tr("Film-%1 (%2)").arg(newFilm->paperSize, quoteNumber));
            it->setText(1, newFilm->qty);
            it->setText(2, newFilm->customer + ":" + newFilm->product);
            it->setText(3, "19.04");
            it->setText(4, "16");
        }
    }

}

void RequisitionWizard::on_RequisitionWizard_rejected()
{

}
