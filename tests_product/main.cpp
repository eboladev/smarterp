#include "dialogproducttest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogProductTest w;
    w.show();
    
    return a.exec();
}
