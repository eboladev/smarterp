#include "startnewemployee.h"
#include "ui_startnewemployee.h"

StartNewEmployee::StartNewEmployee(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::StartNewEmployee)
{
	ui->setupUi(this);
}

StartNewEmployee::~StartNewEmployee()
{
	delete ui;
}
QString StartNewEmployee::fName() const
{
	return m_fName;
}

void StartNewEmployee::setFName(const QString &fName)
{
	m_fName = fName;
}
QString StartNewEmployee::lName() const
{
	return m_lName;
}

void StartNewEmployee::setLName(const QString &lName)
{
	m_lName = lName;
}
QString StartNewEmployee::idNo() const
{
	return m_idNo;
}

void StartNewEmployee::setIdNo(const QString &idNo)
{
	m_idNo = idNo;
}
QString StartNewEmployee::nssfNo() const
{
	return m_nssfNo;
}

void StartNewEmployee::setNssfNo(const QString &nssfNo)
{
	m_nssfNo = nssfNo;
}
QString StartNewEmployee::nhifNo() const
{
	return m_nhifNo;
}

void StartNewEmployee::setNhifNo(const QString &nhifNo)
{
	m_nhifNo = nhifNo;
}
QString StartNewEmployee::pinNo() const
{
	return m_pinNo;
}

void StartNewEmployee::setPinNo(const QString &pinNo)
{
	m_pinNo = pinNo;
}







void StartNewEmployee::on_cmdSaveEmployee_clicked()
{
	setFName(ui->txtFName->text());
	setLName(ui->txtOtherNames->text());
	setPinNo(ui->txtPINNo->text());
	setIdNo(ui->txtIDNo->text());
	setNssfNo(ui->txtNSSFNo->text());
	setNhifNo(ui->txtNHIFNo->text());

	this->accept();
}
