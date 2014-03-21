#include <QApplication>
#include "queueclientdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationDisplayName("Queue Client");
    a.setApplicationName("queue_client");
    a.setOrganizationDomain("megvel.me.ke");
    a.setOrganizationName("Megvel Cartons Ltd");

    QueueClientDialog *cl = new QueueClientDialog(0);
    cl->exec();

    return a.exec();
}
