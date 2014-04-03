#ifndef NEWSTUDENTWIZARD_H
#define NEWSTUDENTWIZARD_H

#include <QtGui>
#include <QtSql>
#include <QWizard>

namespace Ui {
class NewStudentWizard;
}

class NewStudentWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit NewStudentWizard(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~NewStudentWizard();
    
private:
    Ui::NewStudentWizard *ui;
    QSqlDatabase db;
};

#endif // NEWSTUDENTWIZARD_H
