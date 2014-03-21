#ifndef USEREDITOR_H
#define USEREDITOR_H

#include <QtGui>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
namespace Ui {
class UserEditor;
}

class UserEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit UserEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~UserEditor();
    QString currentID;
    bool isEditing;
    void edit();
    void addNew();
private slots:
    void on_cmdLoadAuditTrail_clicked();

    void on_cmdSetPassword_clicked();

    void on_lstRights_doubleClicked(const QModelIndex &index);

    void on_lstRights_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_cmdSave_clicked();

    void on_cmdDelete_clicked();

    void on_cmdClose_clicked();

    void loadPlugins();
    void savePlugins();
private:
    Ui::UserEditor *ui;
    void saveRights();
    QSqlDatabase db;
    void loadAuditTrail();
    void loadRoles();
    void loadRoleChildren(QTreeWidgetItem *groupItem);
};

#endif // USEREDITOR_H
