#include "updatermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UpdaterMainWindow w;
    w.show();

    return a.exec();
}
