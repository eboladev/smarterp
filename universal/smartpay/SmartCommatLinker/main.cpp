#include "linkermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationDisplayName("Smart Commat Linker");
    a.setApplicationName("SmartCommatLinker");
    a.setOrganizationName("Smart Software Ltd");
    a.setOrganizationDomain("smartsoftware.co.ke");

    LinkerMainWindow w;
    w.show();

    return a.exec();
}
