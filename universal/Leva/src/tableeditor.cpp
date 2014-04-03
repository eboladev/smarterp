#include "tableeditor.h"
#include "ui_tableeditor.h"

TableEditor::TableEditor(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::TableEditor)
{
	ui->setupUi(this);
	db = database;
}

TableEditor::~TableEditor()
{
	delete ui;
}

void TableEditor::setTable(QString tableName, QString dbName)
{
	_tableName = tableName;
	_dbName = dbName;

	ui->txtTableName->setText(tableName);
	ui->txtDbName->setText(dbName);

	loadOriginalColumns();
}

void TableEditor::on_cmdCancel_clicked()
{
	this->reject();
}

void TableEditor::loadOriginalColumns()
{
	QSqlQuery qu = db.exec("DESCRIBE `" + _dbName + "`.`" + _tableName  + "`");
	if (!qu.lastError().isValid()) {
		while (qu.next()) {
			QSqlRecord rec = qu.record();
			QString _colName = rec.value("Field").toString();
			QString _type = rec.value("Type").toString();
			QString _null = rec.value("Null").toString();
			QString _key = rec.value("Key").toString();
			QString _default = rec.value("Default").toString();
			QString _extra = rec.value("Extra").toString();

			QTableWidgetItem *it0 = new QTableWidgetItem(1);
			it0->setText(_colName);
			QTableWidgetItem *it1 = new QTableWidgetItem(1);
			it1->setText(_type);
			QTableWidgetItem *it2 = new QTableWidgetItem(1);
			it2->setText("");
			QTableWidgetItem *it3 = new QTableWidgetItem(1);
			it3->setText(_default);
			QTableWidgetItem *it4 = new QTableWidgetItem(1);
			it4->setText(_null);
			QTableWidgetItem *it5 = new QTableWidgetItem(1);
			it5->setText(_extra);
			QTableWidgetItem *it6 = new QTableWidgetItem(1);
			it6->setText(_key);

			int row = ui->tblTables->rowCount();
			ui->tblTables->insertRow(row);
			ui->tblTables->setItem(row, 0, it0);
			ui->tblTables->setItem(row, 1, it1);
			ui->tblTables->setItem(row, 2, it2);
			ui->tblTables->setItem(row, 3, it3);
			ui->tblTables->setItem(row, 4, it4);
			ui->tblTables->setItem(row, 5, it5);
			ui->tblTables->setItem(row, 6, it6);
		}
	}
}
