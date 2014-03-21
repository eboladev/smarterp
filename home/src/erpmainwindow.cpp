#include "erpmainwindow.h"
#include "ui_erpmainwindow.h"

#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include "datapublics.h"
#include "welcomescreen.h"
#include <QtSql>

ERPMainWindow::ERPMainWindow(QWidget *parent, QString pName, QString dbName, QString user_id, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::ERPMainWindow)
{
    ui->setupUi(this);
    userID = user_id;
    db = database;
    //Fetch latest plugins first:
    updateSocket = new QTcpSocket(this);
    connect (updateSocket, SIGNAL(connected()), SLOT(socketConnected()));
    connect (updateSocket, SIGNAL(readyRead()), SLOT(socketReadyRead()));
    updateSocket->connectToHost(QHostAddress("127.0.0.1"), 4317);
    /////////
    tabs = -1;
    projectName = pName;
    databaseName = dbName;
    //db = DataPublics::getDatabase("ERPConnection", databaseName);
    ui->lblMsg->setVisible(false);
    w_currentUserLabel = new QLabel(this);
    w_dbStatusLabel = new QLabel(this);
    w_notificationsLabel = new QLabel(this);
    w_timeLabel = new QLabel(this);

    connect (w_currentUserLabel, SIGNAL(linkActivated(QString)), SLOT(logOff()));

    ui->statusBar->addWidget(w_currentUserLabel, 1);
    ui->statusBar->addWidget(w_dbStatusLabel, 2);
    ui->statusBar->addWidget(w_notificationsLabel, 3);
    ui->statusBar->addWidget(w_timeLabel, 1);

    addFancyWidgets();
    dbTimer = new QTimer(this);
    connect (dbTimer, SIGNAL(timeout(QPrivateSignal)), SLOT(secondTimeOut()));
    dbTimer->start(10000);
    //    if (db.open()) {
    //        addFancyWidgets(); //
    //        dbTimer = new QTimer(this);
    //        connect (dbTimer, SIGNAL(timeout(QPrivateSignal)), SLOT(secondTimeOut()));
    //        dbTimer->start(1000);
    //    }
    //    else {
    //        ui->lblMsg->setText("<h3>Database Error</h3>There was an error while acccessing the database at "+ db.hostName() +".<br/>Error Message: <br/><b>" + db.lastError().text() + "</b><br/>Click <b><a href='http://192.168.0.8/report.php?error=database_login'>here</a></b> to report this error.");
    //        ui->lblMsg->setVisible(true);
    //        ui->fancyWidget->setVisible(false);
    //    }

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
    w_notificationsLabel->setText("<a href=''>0</a> Notifications");
    w_dbStatusLabel->setText("Connected to " + db.userName() + "@" + db.hostName());
    connect (ui->fancyWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

//    this->setWindowState(Qt::WindowMinimized);
//    this->setWindowState(Qt::WindowMaximized);
}

ERPMainWindow::~ERPMainWindow()
{
    delete ui;
}

void ERPMainWindow::init()
{
}

void ERPMainWindow::addFancyWidgets()
{   
    tabWindows.clear();
    sectionWindows.clear();
    m_fancyWelcomeScreen =   new WelcomeScreen(this, db, userID);
    m_fancyWelcomeScreen->projectName = projectName;
    connect (m_fancyWelcomeScreen, SIGNAL(userLoggedIn(QString)), SLOT(userChanged(QString)));
    connect (m_fancyWelcomeScreen, SIGNAL(dbState(QString)), statusBar(), SLOT(showMessage(QString)));
    connect (m_fancyWelcomeScreen, SIGNAL(logOff()), SLOT(logOff()));
    connect (m_fancyWelcomeScreen, SIGNAL(newPlugin(QMainWindow*)), SLOT(addNewTab(QMainWindow*)));
    m_fancyWelcomeScreen->findPlugins();
//    ui->fancyWidget->insertTab(m_fancyWelcomeScreen);
//    sectionWindows.insert(sectionWindows.count(), m_fancyWelcomeScreen);
//    tabs++;
}

void ERPMainWindow::addNewTab(QMainWindow *tab)
{
    tabs ++;
    tabWindows.insert(tabWindows.count(), tab);
    sectionWindows.insert(sectionWindows.count(), tab);
    ui->fancyWidget->insertTab(tab);
}

#include "userlogin.h"
void ERPMainWindow::logOff()
{
    //this->hide();
    UserLogin *log = new UserLogin(0, db);
    if (log->exec() == QDialog::Accepted) {
        ERPMainWindow *mW = new ERPMainWindow(0, "megvel", "cartons", log->userID, db);
        mW->userChanged(log->userName);
        mW->showMaximized();
        this->close();
    } else {
        DataPublics::showWarning("Log off cancelled.");
       // this->close();
        if (!db.isOpen()) {
            db.open();
        }
    }
}

void ERPMainWindow::userChanged(QString newUser)
{
    w_currentUserLabel->setText("Logged in as <b>" + newUser + "</b> <a href='#'>Log Off</a>");
}

void ERPMainWindow::tabChanged(int i)
{
    QString sectionName = sectionWindows.at(i)->windowTitle();
    DataPublics::logAuditTrail(sectionName, "Opened Section (" + sectionName + ")", db);
}

void ERPMainWindow::socketReadyRead()
{
}

void ERPMainWindow::socketConnected()
{
    updateSocket->write("HELLO:GIVE:LATEST_PLUGINS");
}

void ERPMainWindow::secondTimeOut()
{
    secondQU = db.exec("SELECT NOW()");
    QMessageBox::information(this, "MSG", secondQU.lastError().text());
    if (secondQU.lastError().isValid()) {
        w_dbStatusLabel->setText("Database connection lost. Reconnecting.");
        db.open();
    } else {
        w_dbStatusLabel->setText("Connected to " + db.userName() + "@" + db.hostName());
    }
}

void ERPMainWindow::closeEvent(QCloseEvent *evt)
{
    for (int i = 0; i < tabWindows.count(); i++) {
        QMainWindow *thisTab =  tabWindows[i];
        if (!thisTab->close())
            evt->ignore();
    }
    delete (ui->fancyWidget);
    db.close();
    evt->accept();
}
