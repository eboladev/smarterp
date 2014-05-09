#ifndef CUSTOMEREDITOR_H
#define CUSTOMEREDITOR_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
#include <QDialog>
namespace Ui {
class CustomerEditor;
}

class CustomerEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit CustomerEditor(QWidget *parent = 0);
    ~CustomerEditor();
    void edit(QString customerID);
private slots:
    void on_SaveButton_clicked();

    void on_DeleteButton_clicked();
    void on_lblChange_linkActivated(const QString &link);

signals:
    void reload();
private:
    Ui::CustomerEditor *ui;
    QSqlDatabase db;
    QString currentID;

    bool isAdding;
};

#endif // CUSTOMEREDITOR_H
