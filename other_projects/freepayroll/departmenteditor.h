#ifndef DEPARTMENTEDITOR_H
#define DEPARTMENTEDITOR_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class DepartmentEditor;
}

class DepartmentEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DepartmentEditor(QWidget *parent = 0);
    ~DepartmentEditor();
    QSqlTableModel *model;
    QItemSelectionModel *selectionModel;
    QDataWidgetMapper *mapper;

    QSqlDatabase db;
private slots:
    void on_cmdNewDepartment_clicked();
    void mapperChanged(int row);
    void on_lstDepartments_clicked(const QModelIndex &index);

    void on_cmdSave_clicked();

    void on_cmdDeleteDepartment_clicked();

private:
    Ui::DepartmentEditor *ui;

};

#endif // DEPARTMENTEDITOR_H
