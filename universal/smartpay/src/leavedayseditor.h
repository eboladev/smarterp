#ifndef LEAVEDAYSEDITOR_H
#define LEAVEDAYSEDITOR_H

#include <QDialog>

namespace Ui {
class LeaveDaysEditor;
}

class LeaveDaysEditor : public QDialog
{
	Q_OBJECT

public:
	explicit LeaveDaysEditor(QWidget *parent = 0);
	~LeaveDaysEditor();

private:
	Ui::LeaveDaysEditor *ui;
};

#endif // LEAVEDAYSEDITOR_H
