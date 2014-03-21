#include "updateservermainwindow.h"
#include "ui_updateservermainwindow.h"
#include <QPluginLoader>
#include "interfaces.h"
#include "datapublics.h"
UpdateServerMainWindow::UpdateServerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateServerMainWindow)
{
    m_redColor = QColor(255,0,0);
    m_greenColor = QColor(0, 255, 0);
    m_blueColor = QColor(0, 0, 255);
    ui->setupUi(this);
    reloadPlugins();

    m_server = new QTcpServer(this);
    connect (m_server, SIGNAL(newConnection()), SLOT(newConnection()));
    if(!m_server->listen(QHostAddress::Any, 4317)) {
        DataPublics::showWarning("Could not listen on  port 4317. TCP Connections not possible.");
        writeLog("Could not listen on  port 4317. TCP Connections not possible.", true);
    } else {
        writeLog("Server started on port 4317.");
    }

    secondTimer = new QTimer(this);
    connect (secondTimer, SIGNAL(timeout(QPrivateSignal)), SLOT(secondTimerTick()));
    secondTimer->start(60000);
}

UpdateServerMainWindow::~UpdateServerMainWindow()
{
    delete ui;
}

void UpdateServerMainWindow::hideShow()
{
    if (this->isVisible()) {
        this->hide();
        showHideMenu->setText("Show");
    } else {
        this->show();
        showHideMenu->setText("Hide");
    }
}

void UpdateServerMainWindow::notifyClientsOfUpdate()
{
}

void UpdateServerMainWindow::reloadPlugins()
{
    writeLog("Updating server plugins...");
    ui->lstPlugins->invisibleRootItem()->takeChildren();
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
                QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstPlugins);
                it->setText(0, mW->pluginName());
                it->setText(1, mW->pluginDescription());
                it->setText(3, mW->pluginVersion());
                it->setText(2, mW->releaseDate());
                it->setIcon(0, QIcon(":/images/Icon_94.ico"));
            }
            loader.unload();
        }
    }
    ui->lstPlugins->resizeColumnToContents(0);
}

void UpdateServerMainWindow::exit()
{
}

void UpdateServerMainWindow::writeLog(QString log, bool error)
{
    QListWidgetItem *lst = new QListWidgetItem(ui->lstLog);
    lst->setText("[" + QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm")  + "]  " + log);
    if (error) {
        lst->setForeground(QBrush(m_redColor));
    } else {
        lst->setForeground(QBrush(m_blueColor));
    }
}

void UpdateServerMainWindow::secondTimerTick()
{
    reloadPlugins();
}

void UpdateServerMainWindow::newConnection()
{
    writeLog("Incoming connection...");
    QTcpSocket *sock = m_server->nextPendingConnection();
    connect (sock, SIGNAL(readyRead()), SLOT(readyRead()));
    connect (sock, SIGNAL(disconnected()), SLOT(clientDisconnected()));
    Client *newClient = new Client(this);
    newClient->setSocket(sock);
    newClient->m_hostName = sock->peerName();
    newClient->m_ipAddress = sock->peerAddress().toString();
    newClient->m_firstContact = QDateTime::currentDateTime();
    m_clientList.insert(m_clientList.count(), newClient);
    reloadClientList();
}

void UpdateServerMainWindow::readyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    Client *thisClient = getClientFromSocket(client);
    thisClient->m_lastContact = QDateTime::currentDateTime();
    QByteArray arr = client->readAll();
    QString receivedData = arr;
    writeLog("Data From " + client->peerAddress().toString() + " :" + receivedData);
}

void UpdateServerMainWindow::clientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    Client *thisClient = getClientFromSocket(socket);
    writeLog("Client " + socket->peerAddress().toString() + " has disconnected.");
    for (int i = 0; i < m_clientList.count(); i++) {
        Client *cl = m_clientList.value(i);
        if (cl == thisClient)
            m_clientList.remove(i);
    }
    reloadClientList();
}

void UpdateServerMainWindow::reloadClientList()
{
    ui->lstClients->invisibleRootItem()->takeChildren();
    for (int i = 0; i < m_clientList.count(); i++) {
        //host, ip, first, last, state
        Client *cl = m_clientList.value(i);
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstClients);
        it->setText(0, cl->m_hostName);
        it->setText(1, cl->m_ipAddress);
        it->setText(2, cl->m_firstContact.toString("dd-MMM-yyyy hh:mm:ss"));
        it->setText(3, cl->m_lastContact.toString("dd-MMM-yyyy hh:mm:ss"));
    }
}

Client *UpdateServerMainWindow::getClientFromSocket(QTcpSocket *sock)
{
    Client *cl = new Client(this);
    for (int i = 0; i < m_clientList.count(); i++) {
        cl = m_clientList.value(i);
        if (cl->clientSocket() == sock)
            return cl;
    }
    return cl;
}


/**
 * @brief Client::Client
 * @param parent
 */
Client::Client(QObject *parent) : QThread(parent)
{

}

/**
 * @brief PluginSender::PluginSender
 * @param parent
 *
 *\cPluginSender constructor
 */
PluginSender::PluginSender(QObject *parent)
{
}

/**
 * @brief PluginSender::~PluginSender
 *\cPluginSender Destructor
 */
PluginSender::~PluginSender()
{
}

void PluginSender::run()
{
}
