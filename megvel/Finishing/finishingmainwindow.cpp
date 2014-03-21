#include "finishingmainwindow.h"
#include "ui_finishingmainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#include "datapublics.h"

#include "finishing_peeling.h"
#include "finishing_gluing.h"
#include "finishing_stitching.h"
#include "finishing_report.h"

FinishingMainWindow::FinishingMainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::FinishingMainWindow)
{
    ui->setupUi(this);
    Utils::StyleHelper::setBaseColor(QColor(128,128,128));
    db = database;

    Finishing_Peeling *peeling = new Finishing_Peeling(this, db);
    ui->widget->insertTab(peeling);

    Finishing_Gluing *gluing = new Finishing_Gluing(this, db);
    ui->widget->insertTab(gluing);

    Finishing_Stitching *stitching = new Finishing_Stitching(this, db);
    ui->widget->insertTab(stitching);

    finishing_report *report = new finishing_report(this, db);
    ui->widget->insertTab(report);
}

FinishingMainWindow::~FinishingMainWindow()
{
    delete ui;
}
