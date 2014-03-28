#include <QApplication>
#include "tlmmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TLMMainWindow w;
    w.show();
    
    return a.exec();
}
