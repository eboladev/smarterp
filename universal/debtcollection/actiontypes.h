#ifndef ACTIONTYPES_H
#define ACTIONTYPES_H

#include <QDialog>
#include <QtSql>


#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

namespace Ui {
class ActionTypes;
}

class ComboBoxDelegate : public QItemDelegate {
    Q_OBJECT
public:
    ComboBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const;
    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                      const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
};

class ActionTypes : public QDialog
{
    Q_OBJECT
    
public:
    explicit ActionTypes(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~ActionTypes();
    
private:
    Ui::ActionTypes *ui;
    QSqlDatabase db;
    QSqlTableModel *model;

private slots:
    void reload();
    void on_cmdAddNew_clicked();
    void on_cmdSave_clicked();
    void on_cmdClose_clicked();
};

#endif // ACTIONTYPES_H
