#include "calendarwidget.h"
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif

CalendarWidget::CalendarWidget(QObject *parent) :
	QItemDelegate(parent)
{
}

QWidget *CalendarWidget::createEditor(QWidget *parent,
				      const QStyleOptionViewItem &option,
				      const QModelIndex &index) const
{
	Q_UNUSED(option);
	QDateEdit *editor = new QDateEdit(parent);
	editor->setDate(index.data(Qt::DisplayRole).toDate());
	editor->setDisplayFormat("dd-MMM-yyyy");
	return editor;
}

void CalendarWidget::setEditorData(QWidget *editor,
				   const QModelIndex &index) const
{
	QString val = index.model()->data(index, Qt::DisplayRole).toString();

	QDateEdit *cal = static_cast<QDateEdit *>(editor);
	cal->setDate(QDate::fromString(val));
	cal->setDisplayFormat("dd-MMM-yyyy");
}

void CalendarWidget::updateEditorGeometry(QWidget *editor,
					  const QStyleOptionViewItem &option,
					  const QModelIndex &index) const
{
	Q_UNUSED(index);
	editor->setGeometry(option.rect);
}

void CalendarWidget::setModelData(QWidget *editor,
				  QAbstractItemModel *model,
				  const QModelIndex &index) const
{
	QDateEdit *cal = static_cast<QDateEdit *>(editor);
	QString value = cal->date().toString("yyyy-MM-dd");
	model->setData(index, value, Qt::EditRole);
	model->submit();
}
