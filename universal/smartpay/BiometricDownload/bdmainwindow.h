#ifndef BDMAINWINDOW_H
#define BDMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class BDMainWindow;
}

class BDMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit BDMainWindow(QWidget *parent = 0);
	~BDMainWindow();

private slots:
	void on_actionAbout_Bd_triggered();

	void on_actionExit_triggered();

	void on_actionAbout_Qt_triggered();

	void on_actionPreferences_triggered();

	void on_cmdDownload_clicked();

private:
	Ui::BDMainWindow *ui;

	bool isDownloading;
};

#endif // BDMAINWINDOW_H
