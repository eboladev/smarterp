#include "selectfile.h"
#include "ui_selectfile.h"

SelectFile::SelectFile(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::SelectFile)
{
	ui->setupUi(this);
	db = database;

	// DataPublics::loadQueryToComboBox("SELECT * FROM files", "FileNo", db, ui->cboFiles);
	ui->lstFiles->setQuery("SELECT EntryID, FileNo FROM ims.files ORDER BY ProformaInvoiceDate DESC", db, "File List", true);
	ui->lstFiles->setColumnHidden(0, true);
}

SelectFile::~SelectFile()
{
	delete ui;
}

void SelectFile::on_cmdOk_clicked()
{
	selectedFileId = ui->lstFiles->getCurrentID();
	if (selectedFileId.length() > 0) {
		this->accept();
	}
}
