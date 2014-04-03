#include "actiontypes.h"
#include "ui_actiontypes.h"
#include "publics.h"
ActionTypes::ActionTypes(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::ActionTypes)
{
	ui->setupUi(this);
	db = database;
	reload();
}

ActionTypes::~ActionTypes()
{
	delete ui;
}

void ActionTypes::reload()
{
	model = new QSqlTableModel(this, db);
	model->setTable("appointment_types");
	model->setHeaderData(1, Qt::Horizontal, "Appointment Type");
	model->setHeaderData(2, Qt::Horizontal, "Description");
	model->setHeaderData(3, Qt::Horizontal, "Color");
	model->select();
	model->setEditStrategy(QSqlTableModel::OnRowChange);
	if (model->lastError().isValid()) {
		Publics::showError(model->lastError().text());
		this->close();
	} else {
		ui->tblActionTypes->setModel(model);
		ui->tblActionTypes->setColumnHidden(0, true);
		ComboBoxDelegate *del = new ComboBoxDelegate(ui->tblActionTypes);
		ui->tblActionTypes->setItemDelegateForColumn(3, del);
	}
}

void ActionTypes::on_cmdAddNew_clicked()
{
	model->insertRow(model->rowCount());
}

void ActionTypes::on_cmdSave_clicked()
{
	model->submitAll();
}

void ActionTypes::on_cmdClose_clicked()
{
	this->close();
}

//
ComboBoxDelegate::ComboBoxDelegate(QObject *parent) {

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
					const QStyleOptionViewItem &/*option*/,
					const QModelIndex &/*index*/) const {
	QComboBox *editor = new QComboBox(parent);
	editor->setEditable(true);
	const QStringList colorNames = QColor::colorNames();
	int index = 0;
	foreach (const QString &colorName, colorNames) {
		const QColor color(colorName);
		editor->addItem(colorName, color);
		const QModelIndex idx = editor->model()->index(index++, 0);
		editor->model()->setData(idx, color, Qt::BackgroundColorRole);
	}

	return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
				     const QModelIndex &index) const {
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QComboBox *cbo = static_cast<QComboBox *>(editor);
	for (int i = 0; i < cbo->count(); i++) {
		if (cbo->itemText(i) == value)
			cbo->setCurrentIndex(i);
	}
}

void ComboBoxDelegate::setModelData(QWidget *editor,
				    QAbstractItemModel *model,
				    const QModelIndex &index) const {
	QComboBox *cbo = static_cast<QComboBox *>(editor);
	QString dat = cbo->currentText();
	model->setData(index, dat, Qt::EditRole);
	const QColor color(dat);
	model->setData(index, color, Qt::BackgroundColorRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
					    const QStyleOptionViewItem &option,
					    const QModelIndex &/*index*/) const {
	editor->setGeometry(option.rect);
}

