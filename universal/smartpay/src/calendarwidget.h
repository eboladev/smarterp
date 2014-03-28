#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QItemDelegate>

class CalendarWidget : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CalendarWidget(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
signals:
    
public slots:
    
};

#endif // CALENDARWIDGET_H
