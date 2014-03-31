#include <QApplication>
#include "helperdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Cleanlooks");
    HelperDialog w;
    w.show();
    
    return a.exec();
}
