#include "htmltoqtprinter.h"
#include <QTextDocument>
#include <QMessageBox>
#include "datapublics.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPrintPreviewDialog>
 HtmlToQtPrinter::HtmlToQtPrinter(QWidget *parent, QSqlDatabase database, QSqlQuery query, QString title, bool firstColumnHidden, QString reportQuery, QStringList columnsToSum)
:  QObject(parent)
 {
     m_parent = parent;
    rawHtml = false;
    db = database;

    sumColumns = columnsToSum;

    if (!db.isOpen()) {
        db.open();
    }

    qu = query;

    s_title = title;
    hideFirstColumn = firstColumnHidden;
    s_query = reportQuery;

    print();
}

 HtmlToQtPrinter::HtmlToQtPrinter(QWidget *parent, QSqlDatabase database, QString query, QString title, bool firstColumnHidden, QString reportQuery, QStringList columnsToSum)
:  QObject(parent){
     m_parent = parent;
    QSqlQuery q2u = db.exec(query);
    HtmlToQtPrinter(parent, database, qu, title, firstColumnHidden,
                    reportQuery, columnsToSum);
}

 HtmlToQtPrinter::HtmlToQtPrinter(QWidget *parent, QString html)
:  QObject(parent){
    rawHtml = true;
    s_rawHtml = html;
    print();
 }

 void HtmlToQtPrinter::printRequested(QPrinter *prnt)
 {
     QTextDocument *doc = new QTextDocument(m_parent);
     doc->setHtml(s_rawHtml);
     doc->print(prnt);
     QFile fl(fileName);
     if (fl.exists()) {
#ifdef Q_OS_WIN32
         QDesktopServices::openUrl(QUrl("file:///" + fileName));
#endif
#ifdef Q_OS_X11
         QDesktopServices::openUrl(QUrl(fileName));
#endif
     }
 }

void HtmlToQtPrinter::print()
{
    printer = new QPrinter(QPrinter::HighResolution);
    printer->setOutputFormat(QPrinter::NativeFormat);
    printer->setPageMargins(0.1,0.1,0.1,0.1,QPrinter::Inch);
    QString html = "";
    if (rawHtml) {
        html = s_rawHtml;
    } else {
        //QSqlQuery qu = db.exec("SELECT * FROM report_ocregister LIMIT 0,200");
        qu = db.exec(s_query);
        //qDebug() << s_query;
        printer->setOrientation(QPrinter::Landscape);
        //Add Heading
        html += "<h1>" + s_title + "</h1>";
        //Start Table
        html += "<table width=100% Border=1 CellSpacing=0 CellPadding=2>";
        //Add Header
        html += "<tr bgcolor=\"lightgray\">";

        int start = 0;
        if (hideFirstColumn)
            start = 1;

        for (int i = start; i < qu.record().count(); i++) {
            html += "<td>          <b>" + qu.record().fieldName(i) + "          </b></td>";
        }
        html += "</tr>";
        //Add Body
        int cnt = 0;
        while (qu.next()) {
            cnt = cnt + 1;
            //        if (cnt == 0) {
            //            if (qu.record().count() > 4) {
            //                printer->setOrientation(QPrinter::Landscape);
            //            }
            //        }
            html += "<tr>";
            for (int i = start; i < qu.record().count(); i++) {
                QSqlRecord rec = qu.record();
                QString txt = rec.value(i).toString();

                if (sumColumns.contains(qu.record().fieldName(i))) {
                    txt = QLocale(QLocale::English).toString(txt.toDouble());
                    html += "<td align=right>" + txt + "</td>";
                } else {
                    html += "<td>" + txt + "</td>";
                }
            }
            html += "</tr>";
        }
        //Add Sum row
        html += "<tr bgcolor=\"lightgray\">";
        QLocale loc(QLocale::English, QLocale::Kenya);
        for (int i = start; i < qu.record().count(); i++) {
            QString sumText = "";
            if (sumColumns.contains(qu.record().fieldName(i))) {
                double sum = 0;

                QSqlQuery sumQuery = qu;
                sumQuery.seek(-1);

                while (sumQuery.next()) {
                    QString thisColText = qu.record().value(qu.record().fieldName(i)).toString();
                    float thisSum = QString::number(thisColText.toFloat(), 'f', 2).toFloat();
                    thisSum = qRound(thisSum);
                    //sum = sum + thisColText.toLong();
                    sum = sum + thisSum;
                    //
                }
                //sumText = QString::number(qRound64(sum), 'f', 0);  //QString::number(sum); //QLocale(QLocale::English).toString((double)sum);
                sumText = loc.toString(sum);
            }
            html += "<td align=right><b>" + sumText + "</b></td>";
        }
        //        //Add Footer Column Heads
        //        html += "<tr bgcolor=\"lightgray\">";

        //        for (int i = start; i < qu.record().count(); i++) {
        //            html += "<td><b>" + qu.record().fieldName(i) + "</b></td>";
        //        }
        //        html += "</tr>";
        //Close table
        html += "</table>";
        html += "<br/>";
        html += "<br/>";
        html += "<br/>";
        //Add Footer

       // html += "Generated On " + QDate::currentDate().toString("dd-MMM-yyyy") + " at " + QTime::currentTime().toString("hh:mm:ss");
        s_rawHtml = html;
    }
     fileName = QDir::tempPath()  + QDir::separator();
     fileName.append("SmartERP-" + QDateTime::currentDateTime().toString(
                                         "yyyy-MM-dd-hh-mm-ss-zzz"
                                         )+ ".pdf"
                     );
     if (!fileName.endsWith(".pdf"))
         fileName.append(".pdf");

     if (fileName.length() > 0) {
         printer->setOutputFormat(QPrinter::PdfFormat);
         printer->setOutputFileName(fileName);
     } else {
         DataPublics::showWarning("Error:\n\nFile name not specified.");
         return;
     }

     printRequested(printer);
}
