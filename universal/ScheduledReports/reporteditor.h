#ifndef REPORTEDITOR_H
#define REPORTEDITOR_H

#include <QDialog>
#include <QtGui>
#include <QtSql>

namespace Ui {
class ReportEditor;
}

class ReportEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit ReportEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~ReportEditor();
    void addNew();
    void edit(QString id);
private slots:
    void on_cmdSave_clicked();

    void on_txtSQL_textChanged();
    void loadColumns(QString sql);

private:
    Ui::ReportEditor *ui;
    QSqlDatabase db;
    bool isAdding;
    QString currentID;
};

#endif // REPORTEDITOR_H
