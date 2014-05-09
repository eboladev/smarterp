#include "productiondataentrywizard.h"
#include "ui_productiondataentrywizard.h"

ProductionDataEntryWizard::ProductionDataEntryWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::ProductionDataEntryWizard)
{
    ui->setupUi(this);
}

ProductionDataEntryWizard::~ProductionDataEntryWizard()
{
    delete ui;
}
