#include "levaconnectionwindow.h"
#include "ui_levaconnectionwindow.h"
#include "datapublics.h"
LevaConnectionWindow::LevaConnectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevaConnectionWindow)
{
    ui->setupUi(this);
    ui->splitter->restoreState(DataPublics::getSettingValue("LevaSQL/ConnectionManager/MainSplitter").toByteArray());
    ui->splitter_2->restoreState(DataPublics::getSettingValue("LevaSQL/ConnectionManager/QuerySplitter").toByteArray());
}

LevaConnectionWindow::~LevaConnectionWindow()
{
    DataPublics::setSettingValue("LevaSQL/ConnectionManager/MainSplitter", ui->splitter->saveState());
    DataPublics::setSettingValue("LevaSQL/ConnectionManager/QuerySplitter", ui->splitter_2->saveState());
    delete ui;
}

void LevaConnectionWindow::setOriginalVars()
{
    ui->txtServerName->setText(hostName);
    ui->txtUserName->setText(originalUserName);
    ui->txtPassword->setText(originalPassword);
    //ui->spinBox->setValue(originalPort);

    this->setWindowTitle(ui->txtUserName->text() + "@" + ui->txtServerName->text());
}

void LevaConnectionWindow::on_cmdConnect_clicked()
{
    ui->splitter->setEnabled(false);
    db = QSqlDatabase::addDatabase("QMYSQL", "levaDb" + QDateTime::currentDateTime().toString());
    db.setHostName(ui->txtServerName->text());
    db.setUserName(ui->txtUserName->text());
    db.setPassword(ui->txtPassword->text());
    db.setPort(ui->spinBox->value());


    if (db.open()) {
        DataPublics::showInformation("Database Open", "Success");
    } else {
        DataPublics::showWarning("Connection Error\n\n" + db.lastError().text());
    }

    ui->splitter->setEnabled(true);

    reloadDatabaseTree();
}

void LevaConnectionWindow::reloadDatabaseTree()
{
    QSqlQuery qu = db.exec("SHOW databases");
    if (!db.lastError().isValid()) {
        ui->treeWidget->invisibleRootItem()->takeChildren();
        while (qu.next()) {
            QTreeWidgetItem *dbItem = new QTreeWidgetItem(ui->treeWidget);
            dbItem->setText(0, qu.value(0).toString());
            dbItem->setText(99, "Database");
            dbItem->setText(100, qu.value(0).toString());
            dbItem->setIcon(0, QIcon(":/images/Icon_44.ico"));

            createDbFolders(qu.value(0).toString(), dbItem);
        }
    } else {
        DataPublics::showWarning("Connection Error\n\n" + db.lastError().text());
    }
}

void LevaConnectionWindow::createDbFolders(QString dbName, QTreeWidgetItem *dbItem)
{
    QTreeWidgetItem *tablesFolder = new QTreeWidgetItem(dbItem);
    tablesFolder->setText(0, "Tables");
    tablesFolder->setText(98, "hasDummy");
    tablesFolder->setText(99, "TablesFolder");
    tablesFolder->setText(100, dbName);
    tablesFolder->setIcon(0,  QIcon(":/images/Icon_7.ico"));

    QTreeWidgetItem *dummyTable = new QTreeWidgetItem(tablesFolder);
    dummyTable->setText(99, "dummytable");

    QTreeWidgetItem *viewsFolder = new QTreeWidgetItem(dbItem);
    viewsFolder->setText(0, "Views");
    viewsFolder->setText(99, "ViewsFolder");
    viewsFolder->setText(100, dbName);
    viewsFolder->setText(98, "hasDummy");
    viewsFolder->setIcon(0,  QIcon(":/images/Icon_7.ico"));

    QTreeWidgetItem *dummyView = new QTreeWidgetItem(viewsFolder);
    dummyView->setText(99, "dummytable");
}

void LevaConnectionWindow::on_actionExecute_triggered()
{
    if (!db.isOpen()) {
        DataPublics::showWarning("Database Not Open. Cannot execute query.");
        return;
    }


    ui->trvData->setQuery(ui->txtQuery->toPlainText(), db, "Query Results", false);
}

void LevaConnectionWindow::on_treeWidget_itemExpanded(QTreeWidgetItem *item)
{
    QString itemType = item->text(99);
    QString dbName = item->text(100);
    if (itemType == "TablesFolder") {
        //A tables folder has been expanded
        //Check if a dummy table is present.
        if (item->text(98) == "hasDummy") {
            //Dummy Available
            item->setText(98, ""); //remove dummy and reset dummy flag
            item->takeChildren();
            QSqlQuery qu = db.exec("SHOW FULL TABLES in "+ dbName + " WHERE Table_Type = 'BASE TABLE'");
            while (qu.next()) {
                QTreeWidgetItem *tableItem = new QTreeWidgetItem(item);
                tableItem->setText(0, qu.value(0).toString());
                tableItem->setText(99, "table");
                tableItem->setText(100, dbName);
                tableItem->setIcon(0, QIcon(":/images/Icon_43.ico"));
            }
        }
    }

    if (itemType == "ViewsFolder") {
        //A tables folder has been expanded
        //Check if a dummy table is present.
        if (item->text(98) == "hasDummy") {
            //Dummy Available
            item->setText(98, ""); //remove dummy and reset dummy flag
            item->takeChildren();
            QSqlQuery qu = db.exec("SHOW FULL TABLES in "+ dbName + " WHERE Table_Type = 'VIEW'");
            while (qu.next()) {
                QTreeWidgetItem *tableItem = new QTreeWidgetItem(item);
                tableItem->setText(0, qu.value(0).toString());
                tableItem->setText(99, "view");
                tableItem->setText(100, dbName);
                tableItem->setIcon(0, QIcon(":/images/Icon_90.ico"));
            }
        }
    }
}

void LevaConnectionWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    QString itemType = item->text(99);
    QString dbName = item->text(100);

    if (itemType == "table" || itemType == "view") {
        ui->txtQuery->setPlainText("SELECT * FROM `" + dbName + "`.`" + item->text(0) + "`;" );
        on_actionExecute_triggered();
    }
}

void LevaConnectionWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    popupMenu = new QMenu(this);
    if (currentType == "table") {
        act_alterTable = new QAction(this);
        act_alterTable->setText("Alter Table");
        connect (act_alterTable, SIGNAL(triggered()), SLOT(alterTable()));
        popupMenu->addAction(act_alterTable);
        popupMenu->popup(QCursor::pos());
        return;
    }
}


void LevaConnectionWindow::alterTable()
{
    TableEditor *ed = new TableEditor(this, db);
    ed->setTable(currentName, currentDb);
    if (ed->exec()) {

    }
}


void LevaConnectionWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    currentType = item->text(99);
    currentDb = item->text(100);
    currentName = item->text(0);
}
