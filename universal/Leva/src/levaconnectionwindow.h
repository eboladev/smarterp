#ifndef LEVACONNECTIONWINDOW_H
#define LEVACONNECTIONWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTreeWidget>
#include "tableeditor.h"

namespace Ui {
class LevaConnectionWindow;
}

class LevaConnectionWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LevaConnectionWindow(QWidget *parent = 0);
    ~LevaConnectionWindow();

    QString hostName;
    QString originalUserName;
    QString originalPassword;
    int originalPort;
    QString originalDb;

    void setOriginalVars();
private slots:
    void on_cmdConnect_clicked();
    void reloadDatabaseTree();
    void createDbFolders(QString dbName, QTreeWidgetItem *dbItem);
    void on_actionExecute_triggered();

    void on_treeWidget_itemExpanded(QTreeWidgetItem *item);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);


    void alterTable();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::LevaConnectionWindow *ui;
    QString currentType;
    QString currentName;
    QString currentDb;

    QSqlDatabase db;

    QMenu *popupMenu;

    QAction *act_alterTable;
    QAction *act_reload;
};

#endif // LEVACONNECTIONWINDOW_H
