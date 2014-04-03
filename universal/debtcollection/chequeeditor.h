#ifndef CHEQUEEDITOR_H
#define CHEQUEEDITOR_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ChequeEditor;
}

class ChequeEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChequeEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~ChequeEditor();
    void AddNew();
    void Edit(QString chequeID);
private slots:
    void on_cmdSave_clicked();

private:
    Ui::ChequeEditor *ui;
    QSqlDatabase db;
    bool isAdding;
    QString currentID;
};

#endif // CHEQUEEDITOR_H
