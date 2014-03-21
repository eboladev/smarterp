#ifndef SELECTDATERANGE_H
#define SELECTDATERANGE_H

#include <QDialog>

#include <QDate>


namespace Ui {
    class SelectDateRange;
}

class SelectDateRange : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDateRange(QWidget *parent = 0);
    ~SelectDateRange();
    QDate   startDate;
    QDate   endDate;
    bool    isRange;
private slots:
    void on_dtpStartDate_dateChanged(const QDate &date);
    void changed();
    void on_dtpEndDate_dateChanged(const QDate &date);

    void on_chkRange_toggled(bool checked);

private:
    Ui::SelectDateRange *ui;
};

#endif // SELECTDATERANGE_H
