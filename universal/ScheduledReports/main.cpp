#include <QApplication>
#include "scheduledreportsmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScheduledReportsMainWindow w;
    w.show();
    
    return a.exec();
}
