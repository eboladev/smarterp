#include "tlmmainwindow.h"
#include "ui_tlmmainwindow.h"
#include <QPluginLoader>
#include "interfaces.h"
#include "datapublics.h"
TLMMainWindow::TLMMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TLMMainWindow)
{
    ui->setupUi(this);


    //Create temp folder
    QString tempPath  = QDir::tempPath() + QDir::separator() + "smarttlm"  + QDir::separator() + "plugins";
    QDir tempDir(QDir::tempPath());
    tempDir.mkdir("smarttlm");
    tempDir.cd("smarttlm");
    tempDir.mkdir("plugins");
    tempDir.cd("plugins");

    if (!tempDir.exists()) {
        qDebug() << "Could not create temp dir.";
        DataPublics::showWarning("Could not create temporary update folder. Updates will not be possible.");
    }else {
        qDebug() << "Temporary folder created. Setting up updater.";
    }
    loadServerPlugins();
    QTimer *loaderTimer = new QTimer(this);
    connect (loaderTimer, SIGNAL(timeout()), SLOT(loadServerPlugins()));
    loaderTimer->start(100000);

    QTimer *secTimer = new QTimer(this);
    connect (secTimer, SIGNAL(timeout()), SLOT(updateClientList()));
    secTimer->start(1500);

    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 8000);

    connect (server, SIGNAL(newConnection()), SLOT(newTcpConnection()));
}

TLMMainWindow::~TLMMainWindow()
{
    delete ui;
}

void TLMMainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

#include "tlmpreferences.h"
void TLMMainWindow::on_actionPreferences_triggered()
{
    TLMPreferences p(this);
    p.exec();
}

void TLMMainWindow::loadServerPlugins()
{
    writeLog("Updating server plugins...");
    ui->trvServerPlugins->invisibleRootItem()->takeChildren();
    //QStringList loadedOnes;
    QString pluginPath = qApp->applicationDirPath() + QDir::separator() + "plugins";
    const QDir dir(pluginPath);
    writeLog("Looking for plugins in " + pluginPath);
    //Load dynamic plugins
    foreach (QString fName, dir.entryList(QDir::Files)) {
        writeLog("Checking " + fName);
        QPluginLoader loader(dir.absoluteFilePath(fName));
        loader.load();
        QObject *plugin = loader.instance();
        if (loader.isLoaded()) {
            //it->setText(0, tr("%1 (Dynamic Plugin)").arg(plugin->metaObject()->className()));
            MainWindowInterface *mW = qobject_cast<MainWindowInterface *>(plugin);
            writeLog("Plugin detected: " + mW->pluginName());
            if (mW->pluginName().length() > 0) {
                QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvServerPlugins);
                it->setText(0, mW->pluginName());
                it->setText(1, mW->pluginDescription());
                it->setText(2, mW->pluginVersion());
                it->setText(3, mW->releaseDate());
                it->setIcon(0, QIcon(":/images/Icon_94.ico"));
            }
        }
    }
}

void TLMMainWindow::writeLog(QString logAction)
{
    ui->textBrowser->append(logAction);
}

void TLMMainWindow::newTcpConnection()
{
    QTcpSocket *sock = server->nextPendingConnection();
    sock->write("|STX|HANDSHAKE|OK|Welcome|ETX|");
    connect (sock, SIGNAL(readyRead()), SLOT(readyRead()));
    connect (sock, SIGNAL(disconnected()), SLOT(clientDisconnected()));
    writeLog("New client connected: " + sock->peerAddress().toString() + ":" + QString::number(sock->peerPort()));
    clients.append(sock);

    ClientInformation *inf = new ClientInformation();
    inf->clientID = sock;
    inf->c_serverIP = sock->peerAddress().toString();
    inf->c_serverPort = sock->peerPort();

    clientInfos.insert(sock, inf);
}

void TLMMainWindow::readyRead()
{
    QTcpSocket *sock = qobject_cast<QTcpSocket *>(sender());
    QString receivedData = sock->readAll();
    writeLog("Data Received: " + receivedData + " (From " + sock->peerAddress().toString() + ")");
    if (receivedData.contains("STX") && receivedData.contains("ETX")) {
        QStringList lst = receivedData.split("|");
        if (lst.size() > 2) {
            QString command = lst.at(2);
            //QString text    = lst.at(3);
            if (command == "Plugin Version") {
                QString pluginName = lst.at(3);
                QString pluginVersion = lst.at(4);
                QString pluginReleaseDate = lst.at(5);
                ClientInformation *inf = clientInfos.value(sock);
                inf->c_pluginName = pluginName;
                inf->c_pluginVersion = pluginVersion;
                inf->c_pluginReleaseDate = pluginReleaseDate;
                for (int i = 0; i < ui->trvServerPlugins->invisibleRootItem()->childCount(); i++) {
                    QTreeWidgetItem *it = ui->trvServerPlugins->invisibleRootItem()->child(i);
                    if (it->text(0) == pluginName) {
                        //MATCH!!!
                        inf->p_version = it->text(2);
                        inf->p_releaseDate = it->text(3);
                    }
                }
            }
        }
    }
}

void TLMMainWindow::updateClientList()
{
    ui->trvClients->invisibleRootItem()->takeChildren();
    for (int i = 0; i < clients.count(); i++) {
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvClients);
        it->setText(0, clients.at(i)->peerAddress().toString());
        it->setIcon(0, QIcon(":/images/Icon_45.ico"));

        ClientInformation *inf = clientInfos.value(clients.at(i));
        it->setText(1,inf->c_pluginName);
        if (inf->c_hostName.length() > 0) {
            it->setText(0, inf->c_serverIP + "(" + inf->c_hostName + ")");
        }
        it->setText(2, inf->c_pluginVersion);
        it->setText(3, inf->c_pluginReleaseDate);
        it->setText(4, inf->p_version);
        it->setText(5, inf->p_releaseDate);
        if ((inf->c_pluginVersion != inf->p_version) || (inf->c_pluginReleaseDate != inf->p_releaseDate)) {
            //Mismatch
            it->setText(6, "Out dated. Needs updating");
            clients.at(i)->write("|STX|Version|Plugin outdated. New version available on server.|EXT|");
        } else {
            //Match
            it->setText(6, "Up to date");
            clients.at(i)->write("|STX|Version|Plugin OK, latest version loaded.|ETX|");
        }
    }
}

void TLMMainWindow::clientDisconnected()
{
    QTcpSocket *sock = qobject_cast<QTcpSocket *>(sender());
    writeLog("Client Disconnected: " + sock->peerAddress().toString());
    clients.removeOne(sock);
    clientInfos.remove(sock);
    updateClientList();
}

void TLMMainWindow::getHostNameFromIP(QString ipAddress, QTcpSocket *client)
{
    Q_UNUSED(ipAddress);
    Q_UNUSED(client);
    //QHostInfo::lookupHost(ipAddress, this, SLOT(lookedUp(QHostInfo), client));
}

void TLMMainWindow::lookedUp(const QHostInfo &host, QTcpSocket *client)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    QString addre = "";
    foreach (const QHostAddress &address, host.addresses())
        addre = addre = " " + address.toString();

    ClientInformation *inf = clientInfos.value(client);
    inf->c_hostName = addre;
}
