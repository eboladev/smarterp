#include "updateservermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // a.setQuitOnLastWindowClosed(false);
    a.setApplicationName("UpdateServer");
    a.setApplicationDisplayName("ERP Update Server");

    UpdateServerMainWindow w;
    w.show();
    
    return a.exec();
}
