#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class MemberManager;
}

class MemberManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MemberManager(QWidget *parent = 0);
    ~MemberManager();

private slots:
    void on_cmdNewMember_clicked();
    void reloadMemberList();
private:
    Ui::MemberManager *ui;
    QSqlDatabase db;
    QSqlQueryModel *members_model;
};

#endif // MEMBERMANAGER_H
