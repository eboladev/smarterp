#ifndef CORRUGATORANALYSIS_H
#define CORRUGATORANALYSIS_H

#include "datapublics.h"
#include <QMainWindow>

namespace Ui {
class CorrugatorAnalysis;
}

class CorrugatorAnalysis : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CorrugatorAnalysis(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CorrugatorAnalysis();
    
private slots:
    void on_cmdView_clicked();

private:
    Ui::CorrugatorAnalysis *ui;
    QSqlDatabase db;
};

#endif // CORRUGATORANALYSIS_H
