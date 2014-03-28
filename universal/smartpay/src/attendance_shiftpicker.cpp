#include "attendance_shiftpicker.h"
#include "ui_attendance_shiftpicker.h"

Attendance_ShiftPicker::Attendance_ShiftPicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Attendance_ShiftPicker)
{
    ui->setupUi(this);
}

Attendance_ShiftPicker::~Attendance_ShiftPicker()
{
    delete ui;
}
