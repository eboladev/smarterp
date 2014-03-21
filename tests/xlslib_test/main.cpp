#include <QtGui/QApplication>
#include "xlsmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XLSMainWindow w;
    w.show();
    
    return a.exec();
}
