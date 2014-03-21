#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QMap>
#include <QPrintPreviewWidget>
#include <QtSql>
#include <QtXml>
#include <QPrinter>
#include "loadreportfromsql.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~MainWindow();

    QString name;
private:
    Ui::MainWindow *ui;
    QPrintPreviewWidget *m_view;
    QSqlDatabase db;
    QPrinter *printer;

    QLabel *zoomLabel;
    QLabel *pageLabel;

    bool isreloading;
    QString StartDate, EndDate;
    bool  isRange;
    bool hasDate;
public slots:
    virtual void helpAbout();
    virtual void helpAboutQt();
    virtual void loadReport(QString reportName);
    virtual void selectDbReport();
    void paintRequested(QPrinter* p);

    void firstPage();
    void previousPage();
    void nextPage();
    void lastPage();

    void loadReportXML(QString xml);

    void viewChanged();
    void singlePage();
    void facingPages();
    void allPages();

    bool getDateRange(QString start, QString end, bool isRange = false);
protected:
    QMap<QString, QList<QPair<QString,QString> > > _lists;
    QDomDocument _doc;
    QMap<QString, QVariant> _params;
private slots:
    void on_actionReload_triggered();
    void on_actionGenerate_Report_From_SQL_triggered();
    void on_actionPrint_triggered();
    void on_actionPDF_triggered();
    void on_actionOrder_Qty_Trail_triggered();
    void on_actionDetailed_Order_Trail_triggered();
};

#endif // MAINWINDOW_H
