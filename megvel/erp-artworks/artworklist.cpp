#include "artworklist.h"
#include "ui_artworklist.h"
#include <QtSql>

ArtworkList::ArtworkList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArtworkList)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();
    ui->lstArt->setQuery(""
                         "SELECT EntryID, CompanyName as 'Client', Product, "
                         "ArtworkSize, NoOfColors, FilmLength, FilmWidth"
                         ", SingleFilmSqInch, TotalFilmSqInch"
                         " FROM vw_newart "
                         , db, "Artworks", true);
    ui->lstArt->setColumnHidden(0, true);
}

ArtworkList::~ArtworkList()
{
    delete ui;
}
