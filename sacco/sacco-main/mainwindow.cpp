#include "../sacco-main/mainwindow.h"
#include "../sacco-main/ui_mainwindow.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#include "../sacco-main/members.h"
#include "../sacco-main/lists.h"
#include "datapublics.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString baseName = QApplication::style()->objectName();
#ifdef Q_WS_X11
    if (baseName == QLatin1String("windows")) {
        // Sometimes we get the standard windows 95 style as a fallback
        // e.g. if we are running on a KDE4 desktop
        QByteArray desktopEnvironment = qgetenv("DESKTOP_SESSION");
        if (desktopEnvironment == "kde")
            baseName = QLatin1String("plastique");
        else
            baseName = QLatin1String("cleanlooks");
    }
#endif
    qApp->setStyle(new ManhattanStyle(baseName));
    Utils::StyleHelper::setBaseColor(QColor(128,128,128));

    db = QSqlDatabase::addDatabase("QMYSQL", "saccoConnection");
    db.setHostName("192.168.0.8");
    db.setUserName("root");
    db.setPassword("pledge");
    db.setPort(3306);
    db.setDatabaseName("mfi");

    if (db.open()) {
        Lists *cmp = new Lists(this, db);
        ui->widget->insertTab(cmp);

        Members *mb = new Members(this, db);
        ui->widget->insertTab(mb);


    } else {
        DataPublics::showWarning(db.lastError().text());
        this->close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
