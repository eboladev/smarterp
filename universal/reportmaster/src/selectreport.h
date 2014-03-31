#ifndef SELECTREPORT_H
#define SELECTREPORT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
    class SelectReport;
}

class SelectReport : public QDialog
{
    Q_OBJECT

public:
    explicit SelectReport(QWidget *parent = 0);
    ~SelectReport();
    QSqlDatabase db;
    QString selectedReport;
    void loadReports();
private slots:
    void on_lstReports_currentTextChanged(const QString &currentText);

private:
    Ui::SelectReport *ui;
};

#endif // SELECTREPORT_H
