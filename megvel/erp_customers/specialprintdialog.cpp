#include "specialprintdialog.h"
#include "ui_specialprintdialog.h"

#include <QPrinterInfo>
#include "datapublics.h"
SpecialPrintDialog::SpecialPrintDialog(QPrinter *PrinterToUse, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpecialPrintDialog),
    printer(PrinterToUse)
{
    ui->setupUi(this);

    QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
    for (int i = 0; i < printers.count(); i++) {
        ui->lstPrinters->addItem(printers.at(i).printerName());
    }

}

SpecialPrintDialog::~SpecialPrintDialog()
{
    delete ui;
}

void SpecialPrintDialog::on_cmdPrint_clicked()
{
    if (ui->lstPrinters->selectedItems().count() < 1) {
        DataPublics::showWarning("Select a printer");
        return;
    }

    printer->setPrinterName(ui->lstPrinters->selectedItems().at(0)->text());
    QSizeF size(8.5, 5.5);
    printer->setPaperSize(size, QPrinter::Inch);
    this->accept();
}

void SpecialPrintDialog::on_lstPrinters_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    on_cmdPrint_clicked();

}
