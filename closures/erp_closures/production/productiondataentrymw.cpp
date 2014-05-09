#include "productiondataentrymw.h"
#include "ui_productiondataentrymw.h"
#include <QDate>
#include <QSqlDatabase>
//#include "../gui-commons/reportshower.h"
ProductionDataEntryMW::ProductionDataEntryMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductionDataEntryMW)
{
    ui->setupUi(this);
    ui->dtpScheduleDate->setDate(QDate::currentDate());
    reloadSchedule();
}

ProductionDataEntryMW::~ProductionDataEntryMW()
{
    delete ui;
}

void ProductionDataEntryMW::reloadSchedule()
{
    model = new QSqlRelationalTableModel(this, QSqlDatabase::database("closures"));
    model->setTable("production_schedule");
    model->setFilter(" schedule_date = '" + ui->dtpScheduleDate->date().toString("yyyy-MM-dd") +  "'");
    model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);

    model->setHeaderData(1, Qt::Horizontal, "Order No.", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Date Scheduled", Qt::DisplayRole);

    model->setHeaderData(3, Qt::Horizontal, "Material", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal, "Master Batch", Qt::DisplayRole);

    model->setHeaderData(5, Qt::Horizontal, "Regrind", Qt::DisplayRole);
    model->setHeaderData(6, Qt::Horizontal, "Initial Machine Reading", Qt::DisplayRole);

    model->setHeaderData(7, Qt::Horizontal, "Final Machine Reading", Qt::DisplayRole);
    model->setHeaderData(8, Qt::Horizontal, "Caps Produced", Qt::DisplayRole);

    model->setHeaderData(9, Qt::Horizontal, "Remarks", Qt::DisplayRole);
    model->setHeaderData(10, Qt::Horizontal, "Machine", Qt::DisplayRole);

    model->setRelation(10, QSqlRelation("machines", "machine_id", "machine_name"));

    model->select();
    ui->tblSchedule->setModel(model);
    ui->tblSchedule->setItemDelegate(new QSqlRelationalDelegate(ui->tblSchedule));

    LockedEditDelegate *del = new LockedEditDelegate(ui->tblSchedule);
    ui->tblSchedule->setItemDelegateForColumn(1, del);
    ui->tblSchedule->setItemDelegateForColumn(2, del);
    ui->tblSchedule->setColumnHidden(0, true);
}

void ProductionDataEntryMW::on_dtpScheduleDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    reloadSchedule();
}


LockedEditDelegate::LockedEditDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

#include <QLineEdit>
QWidget *LockedEditDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    editor->setText("");
    editor->setReadOnly(true);
    return editor;
}

void LockedEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lbl = qobject_cast<QLineEdit *>(editor);
    lbl->setText(index.model()->data(index, Qt::EditRole).toString());
}

void LockedEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lbl = qobject_cast<QLineEdit *>(editor);
    model->setData(index, lbl->text());
}

void LockedEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    Q_UNUSED(index);
}


void ProductionDataEntryMW::on_actionPrint_Report_triggered()
{
    //ReportShower *rpt = new ReportShower(this, true);
    //rpt->addDateParam("Select Date", true);
    //rpt->prepareReport("ProductionRecords", false, true, " WHERE `Schedule Date` = '" + ui->dtpScheduleDate->date().toString("yyyy-MM-dd") + "'");
}
