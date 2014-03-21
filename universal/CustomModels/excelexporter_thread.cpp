#include "excelexporter_thread.h"

#include "xlslib.h"
#include "xlsxdocument.h"
using namespace xlslib_core;
ExcelExporter_Thread::ExcelExporter_Thread(QObject *parent) :
    QThread(parent)
{
}

void ExcelExporter_Thread::run()
{
    //    workbook wb;
    //    worksheet* sh = wb.sheet("Sheet 1");

    //    for (int h = 0; h < model->columnCount(); h++) {
    //        QString headerData = model->headerData(h, Qt::Horizontal).toString();
    //        sh->label(0, h, headerData.toStdString())->fontbold(BOLDNESS_BOLD);
    //    }
    //    int p;
    //    p = 1;
    //    for (int r = 0; r < model->rowCount(); r++) {
    //        for (int c = 0; c < model->columnCount(); c++) {
    //            QString data = model->data(model->index(r, c)).toString();
    //            emit progress(p);
    //            emit status(data);
    //            //            bool double_b = false;
    //            //            double bData = data.toDouble(&double_b);
    //            //            if (bData) {
    //            //                sh->number(r + 1, c, bData);
    //            //            } else {
    //            //                sh->label(r + 1, c, data.toStdString());
    //            //            }
    //            sh->label(r + 1, c, data.toStdString());
    //            p++;
    //        }
    //    }
    //    if (!filePath.endsWith(".xls"))
    //        filePath.append(".xls");

    //    wb.Dump(filePath.toStdString());

    if (!filePath.endsWith(".xlsx"))
        filePath.append(".xlsx");

    QXlsx::Document xlsx;
    //Write the header
    QXlsx::Format headerFormat;
    headerFormat.setFontBold(true);
    for (int h = 0; h < model->columnCount(); h++) {
        QString headerData = model->headerData(h, Qt::Horizontal).toString();
        xlsx.write(1, h, headerData, headerFormat);
    }
    //Write the details
    int p;
    p = 1;
    for (int r = 0; r < model->rowCount(); r++) {
        for (int c = 0; c < model->columnCount(); c++) {
            QString data = model->data(model->index(r, c)).toString();
            emit progress(p);
            emit status(data);
            xlsx.write(r + 2, c, data);
            p++;
        }
    }
    xlsx.saveAs(filePath);

    QXlsx::Document doc2(filePath);
    doc2.saveAs(filePath);
}

