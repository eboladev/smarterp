#ifndef REPORTDATESELECTWIDGET_H
#define REPORTDATESELECTWIDGET_H

#include <QWidget>

namespace Ui {
class ReportDateSelectWidget;
}

class ReportDateSelectWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReportDateSelectWidget(QWidget *parent = 0);
    ~ReportDateSelectWidget();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::ReportDateSelectWidget *ui;
};

#endif // REPORTDATESELECTWIDGET_H
