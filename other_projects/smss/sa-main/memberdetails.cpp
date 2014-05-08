#include "memberdetails.h"
#include "ui_memberdetails.h"

#include "datapublics.h"
MemberDetails::MemberDetails(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MemberDetails)
{
	ui->setupUi(this);

	db = QSqlDatabase::database("sacco");

}

MemberDetails::~MemberDetails()
{
	delete ui;
}
