#include "tabularcontainereditor.h"
#include "ui_tabularcontainereditor.h"

TabularContainerEditor::TabularContainerEditor(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TabularContainerEditor)
{
	ui->setupUi(this);
}

TabularContainerEditor::~TabularContainerEditor()
{
	delete ui;
}
