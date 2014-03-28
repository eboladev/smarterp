#include "queueservermainwindow.h"
#include <QApplication>
#include <QtSql>
#include "datapublics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = DataPublics::getDatabase("tlm", "cartons");
    if (db.open()) {
        QueueServerMW w;
        w.show();
        return a.exec();
    } else {
        DataPublics::showWarning("Database Error:\n\n" + db.lastError().text());
        return 0;
    }
}
