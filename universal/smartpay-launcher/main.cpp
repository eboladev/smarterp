#include <QApplication>
#include "launcherdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("Panther Technologies Ltd");
    a.setOrganizationDomain("panthertechno.com");
    a.setApplicationName("SmartPay");

    LauncherDialog w;
    w.show();
    
    return a.exec();
}
