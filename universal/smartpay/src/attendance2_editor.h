#ifndef ATTENDANCE2_EDITOR_H
#define ATTENDANCE2_EDITOR_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class attendance2_editor;
}

class attendance2_editor : public QDialog
{
    Q_OBJECT
    
public:
    explicit attendance2_editor(QWidget *parent = 0, QSqlDatabase d = QSqlDatabase());
    ~attendance2_editor();
    void setAttendance(QString id);
private slots:
    void on_cmdSave_clicked();

private:
    Ui::attendance2_editor *ui;
    QSqlDatabase db;
    QString currentID;
};

#endif // ATTENDANCE2_EDITOR_H
