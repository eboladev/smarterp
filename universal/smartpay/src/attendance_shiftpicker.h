#ifndef ATTENDANCE_SHIFTPICKER_H
#define ATTENDANCE_SHIFTPICKER_H

#include <QDialog>

namespace Ui {
class Attendance_ShiftPicker;
}

class Attendance_ShiftPicker : public QDialog
{
    Q_OBJECT
    
public:
    explicit Attendance_ShiftPicker(QWidget *parent = 0);
    ~Attendance_ShiftPicker();
    
private:
    Ui::Attendance_ShiftPicker *ui;
};

#endif // ATTENDANCE_SHIFTPICKER_H
