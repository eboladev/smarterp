#include "saccomainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("FreeSacco");
    a.setApplicationDisplayName("Free Sacco");
    a.setOrganizationName("Smart Software Ltd");
    a.setOrganizationDomain("smartsoftware.co.ke");


    a.setStyle("Fusion");

    SaccoMainWindow w;
    w.showMaximized();

    return a.exec();
}
