#ifndef SACCOMAINWINDOW_H
#define SACCOMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SaccoMainWindow;
}

class SaccoMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SaccoMainWindow(QWidget *parent = 0);
	~SaccoMainWindow();

private:
	Ui::SaccoMainWindow *ui;
};

#endif // SACCOMAINWINDOW_H
