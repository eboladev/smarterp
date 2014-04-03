#include "threadedexcelimporter.h"
#include "datapublics.h"
#include "xlsxdocument.h"
ThreadedExcelImporter::ThreadedExcelImporter(QObject *parent) :
    QThread(parent)
{
}

void ThreadedExcelImporter::run()
{
    if (db.open()) {
        QXlsx::Document excel(m_fileName);


    } else {
        emit error("Could not open database.");
    }
}

void ThreadedExcelImporter::setFileName(QString path)
{
    m_fileName = path;
    db = DataPublics::getDatabase("cp_thread", "cheque_printer");
}
