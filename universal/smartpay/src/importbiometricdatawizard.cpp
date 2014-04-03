#include "importbiometricdatawizard.h"
#include "ui_importbiometricdatawizard.h"
#include "datapublics.h"
ImportBiometricDataWizard::ImportBiometricDataWizard(QWidget *parent) :
	QWizard(parent),
	ui(new Ui::ImportBiometricDataWizard)
{
	ui->setupUi(this);
	QList<QWizard::WizardButton> layout;
	layout << QWizard::Stretch << QWizard::BackButton << QWizard::CancelButton
	       << QWizard::NextButton << QWizard::FinishButton;
	setButtonLayout(layout);
}

ImportBiometricDataWizard::~ImportBiometricDataWizard()
{
	delete ui;
}

void ImportBiometricDataWizard::on_ImportBiometricDataWizard_customButtonClicked(int which)
{
	QMessageBox::information(this, "", QString::number(which));
}

void ImportBiometricDataWizard::on_ImportBiometricDataWizard_finished(int result)
{
	QMessageBox::information(this, "", QString::number(result));
}
