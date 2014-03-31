#include "mainwindow.h"                     //The report MainWindow
#include "ui_mainwindow.h"

#include "../wrtembed/reporthandler.h"       // The Report Window Child

// common
#include <dbtools.h>
#include <xsqlquery.h>
#include <data.h>

// qt
#include <QSqlDatabase>
#include <QMdiArea>
#include <QMenuBar>
#include <QAction>
#include <QEvent>
#include <QStatusBar>
#include <QPixmap>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QTimerEvent>
#include <QTranslator>
#include <QApplication>
#include <QTreeWidgetItem>
#include <QMessageBox>
// images
#include "../images/OpenReportsIcon.xpm"
#include "builtinSqlFunctions.h"

#include "autoreport.h"
#include "datapublics.h"
MainWindow::MainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Generator");
    setWindowIcon(QPixmap(OpenReportsIcon_xpm));

    //fieldDb = DataPublics::getDatabase("ReportGenerator-FieldConnection", "reports");
    //fieldDb.open();
    fieldDb = database;
    db = fieldDb;
    //Workspace
    ws = new QMdiArea(this);
    //ws->setScrollBarsEnabled(true);

    ws->setViewMode(QMdiArea::TabbedView);

    setCentralWidget(ws);
    //    // setup the menubar
    fileExitAction = new QAction(tr("E&xit"), this);
    fileExitAction->setObjectName("file exit");
    fileExitAction->setShortcut(Qt::ALT+Qt::Key_F4);
    connect(fileExitAction, SIGNAL(triggered()), this, SLOT(appExit()));

    handler = new ReportHandler(this, "report handler");
    //handler->_
    handler->_db = db;
    handler->_dbName = fieldDb.databaseName();
    handler->_userName = fieldDb.userName();
    handler->_password = fieldDb.password();
    handler->_serverName = fieldDb.hostName();
    handler->dbConnect();
    connect (handler, SIGNAL(dbOpenClosed()), SLOT(dbConnected()));
    //connect (handler, SIGNAL(childChanged(QString)), SLOT(reportChanged()));
#ifdef NODBSUPPORT
    handler->setNoDatabase(true);
#endif

    QAction * sepid = handler->populateMenuBar(ui->menuBar, fileExitAction);

    windowMenu = new QMenu(tr("&Windows"));
    //windowMenu->setCheckable(true);
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(sPrepareWindowMenu()));
    menuBar()->insertMenu(sepid, windowMenu);

    //    // setup the toolbar
    handler->docToolBars(this);

    setCaption();

    dbTimerId = startTimer(60000);

    handler->setParentWindow(ws);
    //ui->ws->addSubWindow(handler);


    ws->addSubWindow(qobject_cast<QMainWindow *>(handler));

    connect(handler, SIGNAL(dbOpenClosed()), this, SLOT(setCaption()));
    connect(handler, SIGNAL(messageChanged(const QString &)),
            statusBar(), SLOT(message(const QString &)));
    connect(handler, SIGNAL(messageCleared()),
            statusBar(), SLOT(clear()));
    //handler->onWinChanged(NULL);



    connect (ws, SIGNAL(subWindowActivated(QMdiSubWindow*)), handler, SLOT(onWinChangedEx(QMdiSubWindow*)));
    //connect (ws, SIGNAL(windowActivated(QWidget*)), handler, SLOT(onWinChanged(QWidget*)));
    connect (ws, SIGNAL(windowActivated(QWidget*)), SLOT(reportChanged()));
    //connect (handler, SIGNAL(childChanged(QString)), SLOT(reportChanged(QString)));

    rName = "";

    secondTimer = new QTimer(this);
    connect (secondTimer, SIGNAL(timeout()), SLOT(timeOut()));

    secondTimer->start(10000);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//
// slot implementations
//
void MainWindow::appExit() {
    //close();
}


QWidget * MainWindow::currentSubWindow() {
    //int cnt = 0;
    QList<QMdiSubWindow *> windows = ws->subWindowList();
    for (int intCursor = 0; intCursor < windows.count(); intCursor++)
    {
        QWidget *thisWindow = qobject_cast<QWidget *>(windows.at(intCursor));
        if(thisWindow->isActiveWindow()) {
            reportChanged(thisWindow->windowTitle());
            if (qobject_cast<DocumentWindow *>(windows.at(intCursor))) {
                DocumentWindow *dW = qobject_cast<DocumentWindow *>(windows.at(intCursor));
            }
            return windows.at(intCursor);
        }
    }
    return 0;
}

//
// event handler methods
//

void MainWindow::timerEvent(QTimerEvent * e) {
    if(e->timerId() == dbTimerId) {
        //QSqlDatabase db = QSqlDatabase::database("GeneratorConnection",false);
        if(db.isValid()) {
            QSqlQuery qry(getSqlFromTag("fmt07", db.driverName()));		// MANU

#if 0
            if(qry.first() == true) {
                // Nothing to do.  We were just creating a little traffic
                qDebug("Keep alive succeeded");
            } else {
                // I really don't care
                qDebug("Keep alive failed");
            }
#endif
        }
    }
}

void MainWindow::closeEvent(QCloseEvent * e) {
    ws->closeAllSubWindows();
    //    QWidgetList wl = ws->windowList();
    //    QWidget * w = 0;
    //    for(int i = 0; i < wl.size(); i++)
    //    {
    //        w = wl.at(i);
    //        if(w && !w->close())
    //        {
    //            e->ignore();
    //            return;
    //        }
    //    }
    e->accept();
}

void MainWindow::setCaption() {
    QString caption = QString("%1")
            .arg(handler->name());

    //QSqlDatabase db = //QSqlDatabase::database("GeneratorConnectino", false);
    if(db.isValid()) {
        XSqlQuery dbname;
        dbname.prepare( getSqlFromTag("fmt08", db.driverName()));		// MANU

        if ((dbname.isActive()) && (dbname.size())) {
            QString protocol;
            QString server;
            QString database;
            QString port;

            dbname.next();
            // OpenRPT::databaseURL = "mysql://localhost/reports:3306";
            parseDatabaseURL((const QString &)OpenRPT::databaseURL,
                             protocol, server, database, port);

            caption = QString( tr("%1 - %2 on %3/%4 AS %5") )
                    .arg(caption)
                    .arg(dbname.value("metric_value").toString())
                    .arg(server)
                    .arg(database)
                    .arg(dbname.value("username").toString());
        }
    }

    QMainWindow::setWindowTitle("Generator");
}

void MainWindow::sPrepareWindowMenu()
{
    windowMenu->clear();

    QAction * intCascadeid = windowMenu->addAction(tr("&Cascade"), ws, SLOT(cascade()));
    QAction * intTileid = windowMenu->addAction(tr("&Tile"),ws, SLOT(tile()));

    windowMenu->addSeparator();

    int cnt = 0;
    //QWidgetList windows = ws->windowList();
    QList<QMdiSubWindow *> windows = ws->subWindowList();
    for (int intCursor = 0; intCursor < windows.count(); intCursor++)
    {
        QWidget *wid = qobject_cast<QWidget *>(windows.at(intCursor));
        if(wid->isVisible())
        {
            QAction * intMenuid = windowMenu->addAction(wid->windowTitle(), wid, SLOT(setFocus()));
            intMenuid->setChecked((ws->activeSubWindow() == wid));
            cnt++;
        }
    }

    if (cnt < 1)
    {
        intCascadeid->setEnabled(false);
        intTileid->setEnabled(false);
    }
}

void MainWindow::openReportFile(const QString &fileName)
{
    handler->fileOpen(fileName);
}

void MainWindow::dbConnected()
{
    _dbName = handler->_dbName;
    _userName = handler->_userName;
    _serverName = handler->_serverName;
    _password = handler->_password;
}

void MainWindow::reportChanged(QString newReportName)
{
    Q_UNUSED(newReportName);
    rName = handler->_reportName;
    ui->treeWidget->invisibleRootItem()->takeChildren();

    _dbName = handler->_dbName;
    _userName = handler->_userName;
    _serverName = handler->_serverName;
    _password = handler->_password;
    _reportName = handler->_reportName;

    if (!fieldDb.isOpen()) {
        fieldDb.open();
    }
    fieldDb.setHostName(_serverName);
    fieldDb.setUserName(_userName);
    fieldDb.setPassword(_password);
    fieldDb.setDatabaseName(_dbName);

    if (!ws->activeSubWindow())
        return;

    if (ws->activeSubWindow()->windowTitle().length() < 1)
        return;


    qDebug() << _reportName;
    if (fieldDb.open()) {
        QSqlQuery qu = fieldDb.exec("SELECT report_query FROM report WHERE report_name = '" + _reportName + "'");
        if (!qu.lastError().isValid()) {
            while (qu.next()) {
                QString query = qu.value(0).toString();
                QSqlQuery field_qu = fieldDb.exec(query);
                if (!field_qu.lastError().isValid()) {
                    while (field_qu.next()) {
                        for (int x = 0; x < field_qu.record().count(); x++) {
                            QTreeWidgetItem *it = new QTreeWidgetItem(ui->treeWidget);
                            it->setText(0, field_qu.record().fieldName(x));
                        }
                        return;
                    }
                } else {
                    QMessageBox::critical(this, "Error", field_qu.lastError().text());
                }
            }
        } else {
            QMessageBox::critical(this, "Error", qu.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Could not load field list", fieldDb.lastError().text());
    }
}

void MainWindow::timeOut()
{
    if (!db.isOpen())
        db.open();
    db.exec("SELECT NOW()");
}


void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    QString fName = item->text(0);
    handler->insertFieldFromList(fName);
}

void MainWindow::on_actionAuto_Report_triggered()
{
    AutoReport *qu = new AutoReport(this, fieldDb);
    if (qu->exec()) {

    }
}

void MainWindow::on_pushButton_clicked()
{
    reportChanged("");
}
