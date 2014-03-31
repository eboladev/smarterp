#include "productionmainwindow.h"
#include "ui_productionmainwindow.h"

#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#include "datapublics.h"

#include "createschedule.h"
#include "corrugatoranalysis.h"
//#include "oc_reel_linking_b.h"
#include "wastemanagement.h"
//#include "reelallocation.h"
#include "production_reports.h"
#include "wastetabular.h"
#include "tabularoclinking.h"
ProductionMainWindow::ProductionMainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::ProductionMainWindow)
{
    ui->setupUi(this);
    Utils::StyleHelper::setBaseColor(QColor(128,128,128));
    db = database;

    //CorrugatorAnalysis *c_analysis = new CorrugatorAnalysis(this, db);

    //oc_reel_linking_b *ocReels = new oc_reel_linking_b(this, db);

    // ReelAllocation *allocation = new ReelAllocation(this, db);
    // production_reports *rep = new production_reports(this, db);



    if (DataPublics::getUserPermission("Create Production Schedule")) {
        CreateSchedule  *m_createSchedule = new CreateSchedule(this, db);
        WasteManagement *waste = new WasteManagement(this, db);
        WasteTabular *wt = new WasteTabular(this);
        ui->centralwidget->insertTab(m_createSchedule);
        ui->centralwidget->insertTab(waste);
        ui->centralwidget->insertTab(wt);
    }

    // ui->centralwidget->insertTab(c_analysis);
    //ui->centralwidget->insertTab(ocReels);

    //ui->centralwidget->insertTab(allocation);
    //ui->centralwidget->insertTab(rep);
    TabularOcLinking *tab = new TabularOcLinking(this, db);
    ui->centralwidget->insertTab(tab);


}

ProductionMainWindow::~ProductionMainWindow()
{
    delete ui;
}
