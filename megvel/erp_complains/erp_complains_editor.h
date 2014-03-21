#ifndef ERP_COMPLAINS_EDITOR_H
#define ERP_COMPLAINS_EDITOR_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
#include <QDialog>
namespace Ui {
class erp_complains_editor;
}

class erp_complains_editor : public QDialog
{
    Q_OBJECT
    
public:
    explicit erp_complains_editor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~erp_complains_editor();
    void AddNew();
    void Edit(QString ComplainID);
private slots:
    void on_cmdSave_clicked();

    void on_cboCustomer_currentIndexChanged(const QString &arg1);

private:
    Ui::erp_complains_editor *ui;
    QSqlDatabase db;
    bool isAdding;
    QString currentID;
};

#endif // ERP_COMPLAINS_EDITOR_H
