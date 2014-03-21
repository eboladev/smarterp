#include "chequeprinter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Cheque Printer");
    a.setOrganizationName("Smart Software");

    ChequePrinter w;
    w.show();

    return a.exec();
}
