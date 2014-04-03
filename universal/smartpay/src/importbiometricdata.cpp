#include "importbiometricdata.h"
#include "ui_importbiometricdata.h"


#include "xlsxdocument.h"
#include "datapublics.h"
ImportBiometricData::ImportBiometricData(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ImportBiometricData)
{
	ui->setupUi(this);
}

ImportBiometricData::~ImportBiometricData()
{
	delete ui;
}

void ImportBiometricData::on_cmdSelectDataFile_clicked()
{

	QString fileName = QFileDialog::getOpenFileName(this, "Select an Excel File", QDir::homePath(), "Excel Files (*.xlsx)");
	if (fileName.length() > 0) {
		if (QMessageBox::question(this, "Warning", "This will clear all unsaved data. Proceed?",
					  QMessageBox::Yes, QMessageBox::No
					  ) == QMessageBox::No) {
			return;
		}
		//ui->tblPreviewData->clear();
		QXlsx::Document excel(fileName);
		bool blanks;
		blanks = false;
		int start = 1;
		if (ui->chkFirstRow->isChecked())
			start = 2;

		for (int r = start; r < 1000; r++) {
			if (!blanks) {
				QString staff_no = excel.read(r, 1).toString();
				QString date = excel.read(r, 2).toString();
				QString time = excel.read(r, 3).toString();
				QString in_out = excel.read(r, 4).toString();
				if (staff_no == "")
					blanks = true;

				QTableWidgetItem *it_staff_no = new QTableWidgetItem(staff_no);
				QTableWidgetItem *it_date = new QTableWidgetItem(date);
				QTableWidgetItem *it_time = new QTableWidgetItem(time);
				QTableWidgetItem *it_in_out = new QTableWidgetItem(in_out);

				int r = ui->tblPreviewData->rowCount();

				ui->tblPreviewData->insertRow(r);
				ui->tblPreviewData->setItem(r, 0, it_staff_no);
				ui->tblPreviewData->setItem(r, 1, it_date);
				ui->tblPreviewData->setItem(r, 2, it_time);
				ui->tblPreviewData->setItem(r, 3, it_in_out);

			} else {
				break;
			}
		}
	}
}
