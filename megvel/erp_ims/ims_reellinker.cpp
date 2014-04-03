#include "ims_reellinker.h"
#include "ui_ims_reellinker.h"

ims_reellinker::ims_reellinker(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::ims_reellinker)
{
    ui->setupUi(this);
    db = database;
    reloadReels();
}

ims_reellinker::~ims_reellinker()
{
    delete ui;
}

void ims_reellinker::reloadReels()
{
    ui->lstReels->setQuery("SELECT * FROM ims.vw_extendedreels", db, "Imported Reels", true);
    ui->lstReels->setColumnHidden(0, true);
}

#include "ims_reels.h"
void ims_reellinker::on_lstReels_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString rID = ui->lstReels->getCurrentID();
    if (rID.length() > 0) {
        IMS_Reels *rl  = new IMS_Reels(this, db);
        //rl->containerID = currentID;
        rl->reelID = rID;
        rl->Edit();
        if (rl->exec() == QDialog::Accepted)
            reloadReels();
    }
}
