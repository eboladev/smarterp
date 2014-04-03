#ifndef WASTETABULAR_H
#define WASTETABULAR_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class WasteTabular;
}

class WasteTabular : public QMainWindow
{
	Q_OBJECT

public:
	explicit WasteTabular(QWidget *parent = 0);
	~WasteTabular();

private slots:
	void on_action_New_Entry_triggered();

private:
	Ui::WasteTabular *ui;
	void reloadList();
};

#endif // WASTETABULAR_H
