#ifndef BONUSEDITOR_H
#define BONUSEDITOR_H

#include <QtSql>
#include <QDialog>

namespace Ui {
class BonusEditor;
}

class BonusEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit BonusEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~BonusEditor();
    bool isAdding;
    QString currentID;
    void Edit(QString bonusID);
    void AddNew(QString employeeID);
private slots:
    void on_cmdSave_clicked();

private:
    Ui::BonusEditor *ui;
    QSqlDatabase db;
};

#endif // BONUSEDITOR_H
