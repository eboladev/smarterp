#ifndef ATTENDANCE_NEWDATERANGE_H
#define ATTENDANCE_NEWDATERANGE_H

#include <QDialog>
#include <QDate>
namespace Ui {
class Attendance_NewDateRange;
}

class Attendance_NewDateRange : public QDialog
{
    Q_OBJECT
    
public:
    explicit Attendance_NewDateRange(QWidget *parent = 0);
    ~Attendance_NewDateRange();
    QDate dateIn;
    QDate dateOut;
private slots:
    void DateChange();
private:
    Ui::Attendance_NewDateRange *ui;
};

#endif // ATTENDANCE_NEWDATERANGE_H
