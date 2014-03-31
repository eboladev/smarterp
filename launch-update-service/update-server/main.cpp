#include "usmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    USMainWindow w;
    w.show();
    
    return a.exec();
}
