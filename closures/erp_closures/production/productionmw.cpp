#include "productionmw.h"
#include "ui_productionmw.h"

#include "schedulermw.h"
#include "productiondataentrymw.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#include "machines.h"
ProductionMW::ProductionMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductionMW)
{
    ui->setupUi(this);



    SchedulerMW *sched = new SchedulerMW(this);
    ui->widget->insertTab(sched);

    Machines *mach = new Machines(this);
    ui->widget->insertTab(mach);

    ProductionDataEntryMW *de = new ProductionDataEntryMW(this);
    ui->widget->insertTab(de);
}

ProductionMW::~ProductionMW()
{
    delete ui;
}
