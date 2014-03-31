#include "storequeuemw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StoreQueueMW w;
    w.show();
    
    return a.exec();
}
