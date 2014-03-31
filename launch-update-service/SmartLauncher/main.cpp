#include "launcherdialog.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    LauncherDialog w;
    w.setModal(true);
    w.show();
    return a.exec();
}
