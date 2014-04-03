#ifndef TABULARCONTAINEREDITOR_H
#define TABULARCONTAINEREDITOR_H

#include <QDialog>

namespace Ui {
class TabularContainerEditor;
}

class TabularContainerEditor : public QDialog
{
	Q_OBJECT

public:
	explicit TabularContainerEditor(QWidget *parent = 0);
	~TabularContainerEditor();

private:
	Ui::TabularContainerEditor *ui;
};

#endif // TABULARCONTAINEREDITOR_H
