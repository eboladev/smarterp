#ifndef SPECIALPRINTDIALOG_H
#define SPECIALPRINTDIALOG_H

#include <QDialog>
#include <QPrinter>
namespace Ui {
class SpecialPrintDialog;
}

class SpecialPrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpecialPrintDialog(QPrinter *PrinterToUse = new QPrinter(), QWidget *parent = 0);
    ~SpecialPrintDialog();

private slots:
    void on_cmdPrint_clicked();

    void on_lstPrinters_doubleClicked(const QModelIndex &index);

private:
    Ui::SpecialPrintDialog *ui;
    QPrinter *printer;
    QString printerName;
};

#endif // SPECIALPRINTDIALOG_H
