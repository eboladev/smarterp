#ifndef EMPLOYEEEDITOR_H
#define EMPLOYEEEDITOR_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class EmployeeEditor;
}

class EmployeeEditor : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeEditor(QWidget *parent = 0);
    ~EmployeeEditor();
    QSqlTableModel *model;
    QItemSelectionModel *selectionModel;
    QDataWidgetMapper *mapper;

    QSqlDatabase db;
private slots:
    void on_cmdAddNew_clicked();
    void mapperChanged(int row);
    void on_txtLastName_textChanged(const QString &arg1);

    void on_lstEmployees_activated(const QModelIndex &index);

    void on_lstEmployees_clicked(const QModelIndex &index);

    void setEmpName();
    void on_txtName_textChanged(const QString &arg1);

    void on_cmdSetDateOfBirth_clicked();

    void on_cmdSave_clicked();

private:
    Ui::EmployeeEditor *ui;
};

#endif // EMPLOYEEEDITOR_H
