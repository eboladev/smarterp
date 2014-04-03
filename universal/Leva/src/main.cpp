#include <QApplication>
#include "levamainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevaMainWindow w;
    w.show();    
    return a.exec();
}
