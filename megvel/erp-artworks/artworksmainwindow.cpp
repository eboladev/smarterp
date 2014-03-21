#include "artworksmainwindow.h"
#include "ui_artworksmainwindow.h"
#include "newartworkwizard.h"
#include "artworklist.h"
ArtworksMainWindow::ArtworksMainWindow(QWidget *parent, QSqlDatabase) :
    QMainWindow(parent),
    ui(new Ui::ArtworksMainWindow)
{
    ui->setupUi(this);
}

ArtworksMainWindow::~ArtworksMainWindow()
{
    delete ui;
}

void ArtworksMainWindow::on_cmdNewArtwork_clicked()
{
    NewArtworkWizard *newA = new NewArtworkWizard(this);
    if (newA->exec()) {

    }
}

void ArtworksMainWindow::on_commandLinkButton_2_clicked()
{
    ArtworkList *lst = new ArtworkList(this);
    lst->exec();
}
