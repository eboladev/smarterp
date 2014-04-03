#ifndef NEWWASTEENTRY_H
#define NEWWASTEENTRY_H

#include <QDialog>

namespace Ui {
class NewWasteEntry;
}

class NewWasteEntry : public QDialog
{
	Q_OBJECT

public:
	explicit NewWasteEntry(QWidget *parent = 0);
	~NewWasteEntry();

private slots:
	void on_cmdSave_clicked();

private:
	Ui::NewWasteEntry *ui;
};

#endif // NEWWASTEENTRY_H
