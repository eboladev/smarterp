#ifndef CHEQUEPRINTER_H
#define CHEQUEPRINTER_H

#include <QMainWindow>
#include <QtSql>
#include "sqlmodels.h"
#include <QPrinter>
#include <QPrintPreviewWidget>
#include <QAction>
#include <QLineEdit>
#include <QActionGroup>
#include <QPrintDialog>
class QComboBox;
class QLabel;


namespace Ui {
class ChequePrinter;
class LineEdit;
}

class ZoomFactorValidator : public QDoubleValidator
{
public:
    ZoomFactorValidator(QObject* parent)
        : QDoubleValidator(parent) {}
    ZoomFactorValidator(qreal bottom, qreal top, int decimals, QObject *parent)
        : QDoubleValidator(bottom, top, decimals, parent) {}

    State validate(QString &input, int &pos) const
    {
        bool replacePercent = false;
        if (input.endsWith(QLatin1Char('%'))) {
            input = input.left(input.length() - 1);
            replacePercent = true;
        }
        State state = QDoubleValidator::validate(input, pos);
        if (replacePercent)
            input += QLatin1Char('%');
        const int num_size = 4;
        if (state == Intermediate) {
            int i = input.indexOf(QLocale::system().decimalPoint());
            if ((i == -1 && input.size() > num_size)
                    || (i != -1 && i > num_size))
                return Invalid;
        }
        return state;
    }
};

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget* parent = 0)
        : QLineEdit(parent)
    {
        setContextMenuPolicy(Qt::NoContextMenu);
        connect(this, SIGNAL(returnPressed()), SLOT(handleReturnPressed()));
    }

protected:
    void focusInEvent(QFocusEvent *e)
    {
        origText = text();
        QLineEdit::focusInEvent(e);
    }

    void focusOutEvent(QFocusEvent *e)
    {
        if (isModified() && !hasAcceptableInput())
            setText(origText);
        QLineEdit::focusOutEvent(e);
    }

private slots:
    void handleReturnPressed()
    {
        origText = text();
    }

private:
    QString origText;
};




class ChequePrinter : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChequePrinter(QWidget *parent = 0);
    ~ChequePrinter();

private slots:
    void on_actionImport_Suppliers_From_Excel_triggered();


    void on_cmdFillAmountInWords_clicked();
    void loadCheques();
    void on_cmdNewCheque_clicked();

    void on_cmdDelete_clicked();

    void on_cmdSave_clicked();

    void on_actionExport_PDF_triggered();

    void on_actionPrintout_Settings_triggered();

    void on_cmdDeleteAll_clicked();

    void on_actionAbout_Cheque_Printer_triggered();
    void printPreviewRequested(QPrinter *printer);

    void _q_fit(QAction *action);
    void _q_zoomIn();
    void _q_zoomOut();
    void _q_navigate(QAction *action);
    void _q_setMode(QAction *action);
    void _q_pageNumEdited();
    void _q_print();
    void _q_pageSetup();
    void _q_previewChanged();
    void _q_zoomFactorChanged();

    void updateNavActions();
    void setFitting(bool on);
    bool isFitting();
    void updatePageNumLabel();
    void updateZoomFactor();

    void refreshPrintPreview();

    void reloadProfiles();
    void on_cboProfile_currentIndexChanged(const QString &arg1);

    void on_cboProfile_activated(const QString &arg1);
    void realPrint();
private:
    Ui::ChequePrinter *ui;
    QSqlDatabase db;
    QString amountInWords(uint number);
    SqlTableModel *model;
    QPrintPreviewWidget *previewWidget;

    // widgets:
    QLineEdit *pageNumEdit;
    QLabel *pageNumLabel;
    QComboBox *zoomFactor;
    //Action Groups
    QActionGroup *navGroup;
    QActionGroup *fitGroup;
    QActionGroup* zoomGroup;
    QActionGroup* modeGroup;
    QActionGroup *printerGroup;

    QPrintDialog *printDialog;
    QPrinter *printer;
};

#endif // CHEQUEPRINTER_H
