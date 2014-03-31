#ifndef COMPANYINFORMATIONDIALOG_H
#define COMPANYINFORMATIONDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
namespace Ui {
class CompanyInformationDialog;
}

class CompanyInformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompanyInformationDialog(QWidget *parent = 0);
    ~CompanyInformationDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CompanyInformationDialog *ui;

    QSqlTableModel *model;
    QItemSelectionModel *selectionModel;
    QDataWidgetMapper *mapper;

    QSqlDatabase db;
};

#endif // COMPANYINFORMATIONDIALOG_H
