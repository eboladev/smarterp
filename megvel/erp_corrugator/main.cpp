#include "corrugatormw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CorrugatorMW w;
    w.showFullScreen();
    
    return a.exec();
}
