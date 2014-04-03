#include "newartworkwizard.h"
#include "ui_newartworkwizard.h"
#include "datapublics.h"
NewArtworkWizard::NewArtworkWizard(QWidget *parent) :
	QWizard(parent),
	ui(new Ui::NewArtworkWizard)
{
	ui->setupUi(this);

	QSqlDatabase db = QSqlDatabase::database();
	ui->lstCustomers->setQuery("SELECT CustomerID, CompanyName as  'Customer' FROM customers ORDER BY CompanyName", db, "Customers", true);
	ui->lstCustomers->setColumnHidden(0, true);

	connect (ui->txtArtworkSize, SIGNAL(textChanged(QString)), SLOT(calculateFilmSize()));
	connect (ui->spinNoOfColors, SIGNAL(valueChanged(int)), SLOT(calculateFilmSize()));

	connect (ui->txtFilmLengthEntered, SIGNAL(textChanged(QString)), SLOT(calculateEnteredFilmSize()));
	connect (ui->txtFilmWidthEntered, SIGNAL(textChanged(QString)), SLOT(calculateEnteredFilmSize()));
}

NewArtworkWizard::~NewArtworkWizard()
{
	delete ui;
}

void NewArtworkWizard::on_lstCustomers_clicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QSqlDatabase db = QSqlDatabase::database();
	QString customerID = ui->lstCustomers->getCurrentID();
	if (customerID.length() > 0) {
		ui->lstProducts->setQuery("SELECT `Product ID`, Product FROM products WHERE customer = '" + customerID + "' ORDER BY Product", db, "Products", true);
		ui->lstProducts->setColumnHidden(0, true);
	}
}

void NewArtworkWizard::on_cmdSave_clicked()
{
	QSqlDatabase db = QSqlDatabase::database();
	QString customerID = ui->lstCustomers->getCurrentID();;
	QString productID = ui->lstProducts->getCurrentID();
	if (customerID.length() < 1 || productID.length() < 1) {
		DataPublics::showWarning("Ensure that you have selected a customer and a product.");
		return;
	}

	QSqlQuery qu(db);
	qu.prepare("INSERT INTO newartworks (CustomerID, ProductID, ArtworkSize, NoOfColors, "
		   " DetectedArtSize, DetectedArtSizeID, UserArtSize, UserArtSizeID, FilmLength, "
		   " FilmWidth, SingleFilmSqInch, TotalFilmSqInch, Chargeable) VALUES ("
		   " :custID, :prodID, :artSize, :noOfColors, :detectedSize, :detectedSizeID, "
		   " :userSize, :userSizeID, :fileLength, :filmWidth, :singleSq, :totalSq, :charge)");
	qu.bindValue(":custID", customerID);
	qu.bindValue(":prodID", productID);
	qu.bindValue(":artSize", ui->txtArtworkSize->text());
	qu.bindValue(":noOfColors", ui->spinNoOfColors->value());
	qu.bindValue(":detectedSize", ui->txtDetectedPaperSize->text());
	qu.bindValue(":detectedSizeID", "");
	qu.bindValue(":userSize", ui->cboUserPaperSize->currentText());
	qu.bindValue(":userSizeID", "");
	qu.bindValue(":filmLength", ui->txtFilmLength->text());
	qu.bindValue(":filmWidth", ui->txtFilmWidth->text());
	qu.bindValue(":singleSq", ui->txtFilmSingleSqInch->text());
	qu.bindValue(":totalSq", ui->txtFilmTotalSqInchEntered->text());
	qu.bindValue(":charge", ui->chklChargeable->isChecked());

	qu.exec();
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}

	this->accept();
}


void NewArtworkWizard::calculateFilmSize()
{


	QString txt = ui->txtArtworkSize->text();
	if (txt.split("x").count() > 1) {
		QString mm_l = txt.split("x").at(0);
		QString mm_w = txt.split("x").at(1);

		double d_mm_l = mm_l.toDouble();
		double d_mm_w = mm_w.toDouble();

		double d_in_l = round((d_mm_l / 25.1));
		double d_in_w = round((d_mm_w / 25.1));

		ui->txtFilmLength->setText(QString::number(d_in_l));
		ui->txtFilmWidth->setText(QString::number(d_in_w));

		double d_singleFilmSq = d_in_l * d_in_w;
		double d_allFilmsSq = d_singleFilmSq * ui->spinNoOfColors->value();

		ui->txtFilmSingleSqInch->setText(QString::number(round(d_singleFilmSq)));
		ui->txtFilmTotalSqInch->setText(QString::number(round(d_allFilmsSq)));
	}
}

void NewArtworkWizard::calculateEnteredFilmSize()
{
	double d_in_l = round(ui->txtFilmLengthEntered->text().toDouble());
	double d_in_w = round(ui->txtFilmWidthEntered->text().toDouble());

	double d_singleFilmSq = d_in_l * d_in_w;
	double d_allFilmsSq = d_singleFilmSq * ui->spinNoOfColors->value();

	ui->txtFilmSingleSqInchEntered->setText(QString::number(round(d_singleFilmSq)));
	ui->txtFilmTotalSqInchEntered->setText(QString::number(round(d_allFilmsSq)));
}
