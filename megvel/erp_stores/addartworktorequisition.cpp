#include "addartworktorequisition.h"
#include "ui_addartworktorequisition.h"
#include <QtSql>

AddArtworkToRequisition::AddArtworkToRequisition(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddArtworkToRequisition)
{
	ui->setupUi(this);
	QSqlDatabase db = QSqlDatabase::database();
	ui->lstArtworks->setQuery(""
				  "SELECT EntryID, CompanyName as 'Client', Product, "
				  "ArtworkSize, NoOfColors, FilmLength, FilmWidth"
				  ", SingleFilmSqInch, TotalFilmSqInch"
				  " FROM vw_newart "
				  , db, "Artworks", true);
	ui->lstArtworks->setColumnHidden(0, true);
}

AddArtworkToRequisition::~AddArtworkToRequisition()
{
	delete ui;
}

void AddArtworkToRequisition::on_cmdAdd_clicked()
{
	QString artID = ui->lstArtworks->getCurrentID();
	if (artID.length() < 1)
		return;


	QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery qu = db.exec(""
			       "SELECT EntryID, CompanyName as 'Client', Product, "
			       "ArtworkSize, NoOfColors, FilmLength, FilmWidth"
			       ", SingleFilmSqInch, TotalFilmSqInch, UserArtSize as 'Size'"
			       " FROM vw_newart WHERE EntryID = '" + artID + "'");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}


	qu.first();

	customer = qu.record().value("Client").toString();
	product = qu.record().value("Product").toString();
	paperSize = qu.record().value("Size").toString();
	qty = qu.record().value("TotalFilmSqInch").toString();
	artworkID = artID;
	this->accept();

}
