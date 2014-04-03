#include "chequeprinter.h"
#include "ui_chequeprinter.h"
#include "xlsxdocument.h"
#include "datapublics.h"
#include "supplierimportprogressdialog.h"
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPageSetupDialog>
#include "chequerenderer.h"
#include "printoutsettingsdialog.h"
ChequePrinter::ChequePrinter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChequePrinter), printDialog(0)
{
    //Database Setup
    db = QSqlDatabase::addDatabase("QSQLITE", "cp");
    db.setHostName("127.0.0.1");
    db.setDatabaseName(qApp->applicationDirPath() + QDir::separator() + "db.sqlite");

    if (db.open()) {
        qDebug() << "Database Open";

        db.exec("CREATE table cheques (EntryID Integer Primary Key autoincrement,"
                "Account text,"
                "ChequeDate text,"
                "Amount text, LocaleAmount text, "
                "AmountInWords text)");

        QSqlQuery field_qu = db.exec("CREATE TABLE fields (id Integer Primary Key autoincrement,"
                                     " Profile text,"
                                     " Description text,"
                                     " Column text,"
                                     " Width text default '0', "
                                     " Height text default '25', "
                                     " X text, "
                                     " Y text, "
                                     " FontSize text default 8, WordWrap text default 'No')");
        if (!field_qu.lastError().isValid()) {
            qDebug() << "Writing Fields";
            //Populate initial fields
            db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
                    "'First Bank', 'Account Name', 'Account', '395', '25', '120', '30', 8)");
            db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
                    "'First Bank', 'Amount', 'LocaleAmount', '135', '25', '495', '90', 8)");
            db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
                    "'First Bank', 'Cheque Date', 'ChequeDate', '170', '25', '495', '10', 8)");
            db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize, WordWrap) VALUES("
                    "'First Bank', 'Amount In Words', 'AmountInWords', '525', '50', '30', '265', 8, 'Yes')");
            db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
                    "'First Bank', 'Amount', 'LocaleAmount', '135', '25', '495', '90', 8)");
        }

        QSqlQuery pg_qu = db.exec("CREATE TABLE page_settings ("
                        "PageHeight text default '4',"
                        "PageWidth text default '7')");
        if (!pg_qu.lastError().isValid()) {
            db.exec("INSERT INTO page_settings (PageWidth, PageHeight) VALUES ('7', '4')");
        }

        //Database Is OK
        printer = new QPrinter(QPrinter::HighResolution);
        //User Interface Setup
        ui->setupUi(this);
        ui->menuEdit->setHidden(true);
        reloadProfiles();
        //Create dummy preview widget to avoid errors
        previewWidget = new QPrintPreviewWidget();
        ui->vLay->addWidget(previewWidget);
        ui->tabWidget->setCurrentIndex(0);

        pageNumEdit = new LineEdit;
        pageNumEdit->setAlignment(Qt::AlignRight);
        pageNumEdit->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        pageNumEdit->setMaximumWidth(50);
        pageNumLabel = new QLabel;
        QObject::connect(pageNumEdit, SIGNAL(editingFinished()), this, SLOT(_q_pageNumEdited()));

        zoomFactor = new QComboBox;
        zoomFactor->setEditable(true);
        zoomFactor->setMinimumContentsLength(7);
        zoomFactor->setInsertPolicy(QComboBox::NoInsert);
        LineEdit *zoomEditor = new LineEdit;
        zoomEditor->setValidator(new ZoomFactorValidator(1, 1000, 1, zoomEditor));
        zoomFactor->setLineEdit(zoomEditor);
        static const short factorsX2[] = { 25, 50, 100, 200, 250, 300, 400, 800, 1600 };
        for (int i = 0; i < int(sizeof(factorsX2) / sizeof(factorsX2[0])); ++i)
            zoomFactor->addItem(tr("%1%").arg(factorsX2[i] / 2.0));
        QObject::connect(zoomFactor->lineEdit(), SIGNAL(editingFinished()),
                         this, SLOT(_q_zoomFactorChanged()));
        QObject::connect(zoomFactor, SIGNAL(currentIndexChanged(int)),
                         this, SLOT(_q_zoomFactorChanged()));
        zoomFactor->setCurrentIndex(3);

        QWidget *pageEdit = new QWidget(ui->toolBar);
        QVBoxLayout *vboxLayout = new QVBoxLayout;
        vboxLayout->setContentsMargins(0, 0, 0, 0);
#ifdef Q_OS_MAC
        // We query the widgets about their size and then we fix the size.
        // This should do the trick for the laying out part...
        QSize pageNumEditSize, pageNumLabelSize;
        pageNumEditSize = pageNumEdit->minimumSizeHint();
        pageNumLabelSize = pageNumLabel->minimumSizeHint();
        pageNumEdit->resize(pageNumEditSize);
        pageNumLabel->resize(pageNumLabelSize);
#endif
        QFormLayout *formLayout = new QFormLayout;
#ifdef Q_OS_MAC
        // We have to change the growth policy in Mac.
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
#endif
        formLayout->setWidget(0, QFormLayout::LabelRole, pageNumEdit);
        formLayout->setWidget(0, QFormLayout::FieldRole, pageNumLabel);
        vboxLayout->addLayout(formLayout);
        vboxLayout->setAlignment(Qt::AlignVCenter);
        pageEdit->setLayout(vboxLayout);

        navGroup = new QActionGroup(this);
        navGroup->setExclusive(false);
        navGroup->addAction(ui->actionNext_Page);
        navGroup->addAction(ui->actionPrevious_Page);
        navGroup->addAction(ui->actionFirst_Page);
        navGroup->addAction(ui->actionLast_Page);
        connect (navGroup, SIGNAL(triggered(QAction*))
                 , SLOT(_q_navigate(QAction*)));

        fitGroup = new QActionGroup(this);
        fitGroup->addAction(ui->actionFit_Page_Width);
        fitGroup->addAction(ui->actionFit_Whole_Page);
        ui->actionFit_Page_Width->setCheckable(true);
        ui->actionFit_Whole_Page->setCheckable(true);
        connect (fitGroup, SIGNAL(triggered(QAction*))
                 , SLOT(_q_fit(QAction*)));

        zoomGroup = new QActionGroup(this);
        zoomGroup->addAction(ui->actionZoom_In);
        zoomGroup->addAction(ui->actionZoom_Out);

        modeGroup = new QActionGroup(this);
        modeGroup->addAction(ui->actionSinge_Page);
        modeGroup->addAction(ui->actionFacing_Pages);
        modeGroup->addAction(ui->actionAll_Pages);
        ui->actionSinge_Page->setCheckable(true);
        ui->actionFacing_Pages->setCheckable(true);
        ui->actionAll_Pages->setCheckable(true);
        connect (modeGroup, SIGNAL(triggered(QAction*))
                 , SLOT(_q_setMode(QAction*)));

        connect (ui->actionPrint, SIGNAL(triggered())
                 , SLOT(realPrint()));
        connect (ui->actionPage_Setup, SIGNAL(triggered())
                 , SLOT(_q_pageSetup()));

        ui->toolBar->addAction(ui->actionFit_Page_Width);
        ui->toolBar->addAction(ui->actionFit_Whole_Page);
        ui->toolBar->addSeparator();
        ui->toolBar->addWidget(zoomFactor);
        ui->toolBar->addAction(ui->actionZoom_Out);
        ui->toolBar->addAction(ui->actionZoom_In);
        ui->toolBar->addSeparator();
        ui->toolBar->addAction(ui->actionFirst_Page);
        ui->toolBar->addAction(ui->actionPrevious_Page);
        ui->toolBar->addWidget(pageEdit);
        ui->toolBar->addAction(ui->actionNext_Page);
        ui->toolBar->addAction(ui->actionLast_Page);
        ui->toolBar->addSeparator();
        ui->toolBar->addAction(ui->actionSinge_Page);
        ui->toolBar->addAction(ui->actionFacing_Pages);
        ui->toolBar->addAction(ui->actionAll_Pages);
        ui->toolBar->addSeparator();
        ui->toolBar->addAction(ui->actionPage_Setup);
        ui->toolBar->addAction(ui->actionPrint);

        // Cannot use the actions' triggered signal here, since it doesn't autorepeat
        QToolButton *zoomInButton = static_cast<QToolButton *>(ui->toolBar->widgetForAction(ui->actionZoom_In));
        QToolButton *zoomOutButton = static_cast<QToolButton *>(ui->toolBar->widgetForAction(ui->actionZoom_Out));
        zoomInButton->setAutoRepeat(true);
        zoomInButton->setAutoRepeatInterval(200);
        zoomInButton->setAutoRepeatDelay(200);
        zoomOutButton->setAutoRepeat(true);
        zoomOutButton->setAutoRepeatInterval(200);
        zoomOutButton->setAutoRepeatDelay(200);
        QObject::connect(zoomInButton, SIGNAL(clicked()), this, SLOT(_q_zoomIn()));
        QObject::connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(_q_zoomOut()));


        model = new SqlTableModel(this, db);
        loadCheques();
    } else {
        DataPublics::showWarning("Database Not Open");
        this->close();
        return;
    }

}

ChequePrinter::~ChequePrinter()
{
    delete ui;
}

void ChequePrinter::on_actionImport_Suppliers_From_Excel_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select an Excel File", QDir::homePath(), "Excel Files (*.xlsx)");
    if (fileName.length() > 0) {
        if (QMessageBox::question(this, "Warning", "This will clear all existing cheques. Proceed?",
                                  QMessageBox::Yes, QMessageBox::No
                                  ) == QMessageBox::No) {
            return;
        }
        db.exec("DELETE FROM cheques");
        QXlsx::Document excel(fileName);
        bool blanks;
        blanks = false;
        for (int r = 1; r < 1000; r++) {
            if (!blanks) {
                QString supplier = excel.read(r, 1).toString();
                QString date = excel.read(r, 2).toString();
                QString amount = excel.read(r, 3).toString();
                if (supplier == "")
                    blanks = true;

                //qDebug() << supplier << date << amount;

                db.exec("INSERT INTO cheques (Account, ChequeDate, Amount) VALUES ('"
                        + supplier + "', '"
                        + date  + "', '"
                        + amount + "')");
                loadCheques();
            } else {
                break;
            }
        }
    }
}


QString ChequePrinter::amountInWords(uint number)
{
    static QMap<uint, QString> numbers;

    //Only initialize once
    if (numbers.isEmpty())
    {
        numbers[0] = "zero";
        numbers[1] = "one";
        numbers[2] = "two";
        numbers[3] = "three";
        numbers[4] = "four";
        numbers[5] = "five";
        numbers[6] = "six";
        numbers[7] = "seven";
        numbers[8] = "eight";
        numbers[9] = "nine";
        numbers[10] = "ten";
        numbers[11] = "eleven";
        numbers[12] = "twelve";
        numbers[13] = "thirteen";
        numbers[14] = "fourteen";
        numbers[15] = "fifteen";
        numbers[16] = "sixteen";
        numbers[17] = "seventeen";
        numbers[18] = "eighteen";
        numbers[19] = "nineteen";
        numbers[20] = "twenty";
        numbers[30] = "thirty";
        numbers[40] = "forty";
        numbers[50] = "fifty";
        numbers[60] = "sixty";
        numbers[70] = "seventy";
        numbers[80] = "eighty";
        numbers[90] = "ninety";
    }

    static QMap<uint, QString> powers;

    //Only initialize once
    if (powers.isEmpty())
    {
        powers[2] = "hundred";
        powers[3] = "thousand";
        powers[6] = "million";
        powers[9] = "billion";
    }

    QString output;

    if (number < 21)
    {
        output = numbers[number];
    }
    else if (number < 100)
    {
        output = numbers[10 * qFloor(number / 10)];
        uint remainder = number % 10;

        if (remainder > 0)
            output += "-" + amountInWords(remainder);
    }
    else
    {
        uint power = 2;
        uint place = 0;
        QString powerString;

        //QMap::keys is ordered
        foreach (uint pow, powers.keys())
        {
            uint place_value = qPow(10, pow);
            uint tmp_place = qFloor(number / place_value);
            if (tmp_place < 1)
                break;

            place = tmp_place;
            power = pow;
            powerString = powers[pow];
        }

        if (power > 0)
        {
            output = amountInWords(place) + " " + powerString;
            uint remainder = number % uint(qPow(10, power));

            if (remainder > 0)
                output += " " + amountInWords(remainder);
        }
    }

    return output;
}

void ChequePrinter::on_cmdFillAmountInWords_clicked()
{
    //    for (int r = 0; r < ui->tblCheques->rowCount(); r++) {
    //        QString amount = ui->tblCheques->item(r, 2)->text();
    //        qDebug() << r << amount << amount.toUInt() << amountInWords(amount.toUInt());
    //        QTableWidgetItem *it = new QTableWidgetItem(amountInWords(amount.toUInt()).toUpper());
    //        ui->tblCheques->setItem(r, 3, it);
    //    }

    model->submitAll();
    QSqlQuery qu = db.exec("SELECT * FROM cheques");
    while (qu.next()) {
        QString amount = qu.record().value("Amount").toString();
        double amt = amount.toDouble();
        QLocale loc(QLocale::English, QLocale::Kenya);
        QString newAmt = loc.toCurrencyString(amt, " ");
        QString words = "";
        if (newAmt.contains(".")) {
            QString n_left = amount.split(".").at(0);
            QString n_right = newAmt.split(".").at(1);


            n_right = n_right.left(2);

            QString w_left = amountInWords(n_left.toUInt());
            QString w_right = amountInWords(n_right.toUInt());



            words = w_left + " shillings cents " + w_right + "****";

            if (n_right == "00") {
                words = w_left + " shillings only ****";
            }
        } else {
            words = amountInWords(amount.toUInt()) + " shillings only ****";
        }

        db.exec("UPDATE cheques SET AmountInWords = '" + words.toUpper()
                + "', LocaleAmount = '" + newAmt +"' WHERE EntryID = '" + qu.record().value("EntryID").toString()
                + "'");
    }
    loadCheques();
}

void ChequePrinter::loadCheques()
{
    model = new SqlTableModel(this, db);
    model->setSchema("cheque_printer");
    model->setTable("cheques");
    model->setEditStrategy(SqlTableModel::OnFieldChange);
    model->select();
    ui->tblCheques->setModel(model);
    ui->tblCheques->setColumnHidden(0, true);
    ui->tblCheques->resizeColumnsToContents();
    ui->tblCheques->resizeRowsToContents();

    refreshPrintPreview();
}

void ChequePrinter::on_cmdNewCheque_clicked()
{
    model->insertRows(model->rowCount(), 1);
    model->setData(model->index(model->rowCount() - 1, 3), "0.00");
    ui->tblCheques->resizeRowsToContents();
    on_cmdSave_clicked();
}

void ChequePrinter::on_cmdDelete_clicked()
{
    //    for (int r = 0; r < model->rowCount(); r++) {
    //        if (ui->tblCheques->selec)
    //    }
    model->removeRows(ui->tblCheques->currentIndex().row(), 1);
    on_cmdSave_clicked();
}

void ChequePrinter::on_cmdSave_clicked()
{
    ui->tblCheques->selectRow(ui->tblCheques->currentIndex().row());
    if (!model->submitAll())
    {
        int ret = QMessageBox::question(this, qApp->applicationName(),
                                        tr("There is a pending transaction in progress. That cannot be commited now."\
                                           "\nError: %1\n"\
                                           "Perform rollback?").arg(model->lastError().text()),
                                        QMessageBox::Yes, QMessageBox::No);
        if(ret == QMessageBox::Yes)
            model->revertAll();
        model->setPendingTransaction(false);
        return;
    }
    model->setPendingTransaction(false);
    ui->tblCheques->resizeRowsToContents();
    on_cmdFillAmountInWords_clicked();
    //loadCheques();
}

void ChequePrinter::on_actionExport_PDF_triggered()
{
    printer->setOutputFormat(QPrinter::PdfFormat);
    _q_print();
}

void ChequePrinter::on_actionPrintout_Settings_triggered()
{
    PrintoutSettingsDialog *dg = new
            PrintoutSettingsDialog(this, db);
    if (dg->exec() == QDialog::Accepted) {
        reloadProfiles();
        refreshPrintPreview();
    }
}

void ChequePrinter::on_cmdDeleteAll_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete all cheques?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;

    db.exec("DELETE FROM cheques");
    loadCheques();
}

#include "aboutdialog.h"
void ChequePrinter::on_actionAbout_Cheque_Printer_triggered()
{
    AboutDialog(this).exec();
}

void ChequePrinter::printPreviewRequested(QPrinter *printer)
{
    if (db.isValid())
        ChequeRenderer::renderOnPrinter(printer, db, ui->cboProfile->currentText());
}

void ChequePrinter::_q_fit(QAction *action)
{
    setFitting(true);
    if (action == ui->actionFit_Whole_Page)
        previewWidget->fitInView();
    else
        previewWidget->fitToWidth();
}

void ChequePrinter::_q_zoomIn()
{
    setFitting(false);
    previewWidget->zoomIn();
    updateZoomFactor();
}

void ChequePrinter::_q_zoomOut()
{
    setFitting(false);
    previewWidget->zoomOut();
    updateZoomFactor();
}

void ChequePrinter::_q_navigate(QAction *action)
{
    int curPage = previewWidget->currentPage();
    if (action == ui->actionPrevious_Page)
        previewWidget->setCurrentPage(curPage - 1);
    else if (action == ui->actionNext_Page)
        previewWidget->setCurrentPage(curPage + 1);
    else if (action == ui->actionFirst_Page)
        previewWidget->setCurrentPage(1);
    else if (action == ui->actionLast_Page)
        previewWidget->setCurrentPage(previewWidget->pageCount());
    updateNavActions();
}

void ChequePrinter::_q_setMode(QAction *action)
{
    if (action == ui->actionAll_Pages) {
        previewWidget->setViewMode(QPrintPreviewWidget::AllPagesView);
        setFitting(false);
        fitGroup->setEnabled(false);
        navGroup->setEnabled(false);
        pageNumEdit->setEnabled(false);
        pageNumLabel->setEnabled(false);
    } else if (action == ui->actionFacing_Pages) {
        previewWidget->setViewMode(QPrintPreviewWidget::FacingPagesView);
    } else {
        previewWidget->setViewMode(QPrintPreviewWidget::SinglePageView);
    }
    if (action == ui->actionFacing_Pages || action == ui->actionSinge_Page) {
        fitGroup->setEnabled(true);
        navGroup->setEnabled(true);
        pageNumEdit->setEnabled(true);
        pageNumLabel->setEnabled(true);
        setFitting(true);
    }
}

void ChequePrinter::_q_pageNumEdited()
{
    bool ok = false;
    int res = pageNumEdit->text().toInt(&ok);
    if (ok)
        previewWidget->setCurrentPage(res);
}

void ChequePrinter::_q_print()
{
#if defined(Q_OS_WIN) || defined(Q_OS_MAC)
    if (printer->outputFormat() != QPrinter::NativeFormat) {
        QString title = QCoreApplication::translate("QPrintPreviewDialog", "Export to PDF");
        QString suffix = QLatin1String(".pdf");
        QString fileName = QFileDialog::getSaveFileName(this, title, printer->outputFileName(),
                                                        QLatin1Char('*') + suffix);
        if (!fileName.isEmpty()) {
            if (QFileInfo(fileName).suffix().isEmpty())
                fileName.append(suffix);
            printer->setOutputFileName(fileName);
        }
        if (!printer->outputFileName().isEmpty())
            previewWidget->print();
        return;
    }
#endif

    if (!printDialog)
        printDialog = new QPrintDialog(printer, this);
    if (printDialog->exec() == QDialog::Accepted) {
        previewWidget->print();
    }
}

void ChequePrinter::_q_pageSetup()
{
//    QPageSetupDialog pageSetup(printer, this);
//    if (pageSetup.exec() == QDialog::Accepted) {
//        // update possible orientation changes
//        if (previewWidget->orientation() == QPrinter::Portrait) {
//            //portraitAction->setChecked(true);
//            //preview->setPortraitOrientation();
//        }else {
//           //landscapeAction->setChecked(true);
//           // preview->setLandscapeOrientation();
//        }
//    }
    on_actionPrintout_Settings_triggered();
}

void ChequePrinter::_q_previewChanged()
{
    updateNavActions();
    updatePageNumLabel();
    updateZoomFactor();
}

void ChequePrinter::_q_zoomFactorChanged()
{
    QString text = zoomFactor->lineEdit()->text();
    bool ok;
    qreal factor = text.remove(QLatin1Char('%')).toFloat(&ok);
    factor = qMax(qreal(1.0), qMin(qreal(1000.0), factor));
    if (ok) {
        previewWidget->setZoomFactor(factor/100.0);
        zoomFactor->setEditText(QString::fromLatin1("%1%").arg(factor));
        //setFitting(false);
    }
}

void ChequePrinter::updateNavActions()
{
    int curPage = previewWidget->currentPage();
    int numPages = previewWidget->pageCount();
    ui->actionNext_Page->setEnabled(curPage < numPages);
    ui->actionPrevious_Page->setEnabled(curPage > 1);
    ui->actionFirst_Page->setEnabled(curPage > 1);
    ui->actionLast_Page->setEnabled(curPage < numPages);
    pageNumEdit->setText(QString::number(curPage));
}

void ChequePrinter::setFitting(bool on)
{
    if (isFitting() == on)
        return;
    fitGroup->setExclusive(on);
    if (on) {
        QAction* action = ui->actionFit_Page_Width->isChecked() ? ui->actionFit_Page_Width : ui->actionFit_Whole_Page;
        action->setChecked(true);
        if (fitGroup->checkedAction() != action) {
            // work around exclusitivity problem
            fitGroup->removeAction(action);
            fitGroup->addAction(action);
        }
    } else {
        ui->actionFit_Page_Width->setChecked(false);
        ui->actionFit_Whole_Page->setChecked(false);
    }
}

bool ChequePrinter::isFitting()
{
    return (fitGroup->isExclusive()
            && (ui->actionFit_Page_Width->isChecked() || ui->actionFit_Whole_Page->isChecked()));
}

void ChequePrinter::updatePageNumLabel()
{
    int numPages = previewWidget->pageCount();
    int maxChars = QString::number(numPages).length();
    pageNumLabel->setText(QString::fromLatin1("/ %1").arg(numPages));
    int cyphersWidth =  this->fontMetrics().width(QString().fill(QLatin1Char('8'), maxChars));
    int maxWidth = pageNumEdit->minimumSizeHint().width() + cyphersWidth;
    pageNumEdit->setMinimumWidth(maxWidth);
    pageNumEdit->setMaximumWidth(maxWidth);
    pageNumEdit->setValidator(new QIntValidator(1, numPages, pageNumEdit));
    // any old one will be deleted later along with its parent pageNumEdit

}

void ChequePrinter::updateZoomFactor()
{
    zoomFactor->lineEdit()->setText(QString().sprintf("%.1f%%", previewWidget->zoomFactor()*100));
}

void ChequePrinter::refreshPrintPreview()
{
    delete(previewWidget);

    previewWidget = new QPrintPreviewWidget(printer);
    connect (previewWidget, SIGNAL(paintRequested(QPrinter *)), this,
             SLOT(printPreviewRequested(QPrinter*)));

    connect (previewWidget, SIGNAL(previewChanged()),
             SLOT(_q_previewChanged()));

    ui->vLay->addWidget(previewWidget);
    _q_zoomFactorChanged();
}

void ChequePrinter::reloadProfiles()
{
    QSqlQuery qu = db.exec("SELECT Profile from Fields Group By Profile");
    ui->cboProfile->clear();
    while (qu.next()) {
        ui->cboProfile->addItem(qu.record().value("Profile").toString());
    }
}


void ChequePrinter::on_cboProfile_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    //refreshPrintPreview();
}

void ChequePrinter::on_cboProfile_activated(const QString &arg1)
{
    Q_UNUSED(arg1);
    refreshPrintPreview();
}

void ChequePrinter::realPrint()
{
    printer->setOutputFormat(QPrinter::NativeFormat);
    _q_print();
}
