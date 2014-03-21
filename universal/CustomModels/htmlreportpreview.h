#ifndef HTMLREPORTPREVIEW_H
#define HTMLREPORTPREVIEW_H

#include <QMainWindow>
#include <QtSql>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewWidget>
#include <QtPrintSupport/QPageSetupDialog>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewWidget>
#include <QPageSetupDialog>
#endif

#include <QActionGroup>
namespace Ui {
class HTMLReportPreview;
}

class HTMLReportPreview : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit HTMLReportPreview(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
                               QSqlQuery query = QSqlQuery(),
                               QString title = QString(""),
                               bool firstColumnHidden = true,
                               QString reportQuery = "SELECT (NOW)",
                               QStringList columnsToSum = QStringList());

    explicit HTMLReportPreview(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
                               QString query = QString(),
                               QString title = QString(""),
                               bool firstColumnHidden = true,
                               QString reportQuery = "SELECT (NOW)",
                               QStringList columnsToSum = QStringList());

    explicit HTMLReportPreview(QWidget *parent = 0, QString html = QString());

    ~HTMLReportPreview();
    
private:
    Ui::HTMLReportPreview *ui;
    void initGui();
    QSqlDatabase db;
    QSqlQuery qu;
    QString s_query;
    QString s_title;
    bool rawHtml;
    QString s_rawHtml;
    bool hideFirstColumn;

    QPrintPreviewWidget *previewWidget;
    QPrinter *printer;
    QStringList sumColumns;

    QActionGroup *orientationGroup;
private slots:
    void print(QPrinter *printer);

    void actionPrint();
    void actionPageSetup();
    void firstPage();
    void previousPage();
    void nextPage();
    void lastPage();

    void viewChanged();


};

#endif // HTMLREPORTPREVIEW_H
