#ifndef OC_REEL_LINKING_B_H
#define OC_REEL_LINKING_B_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class oc_reel_linking_b;
}

class oc_reel_linking_b : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit oc_reel_linking_b(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~oc_reel_linking_b();
    
private slots:
    void on_dtpProductionDate_dateChanged(const QDate &date);

    void on_lstAllOCs_doubleClicked(const QModelIndex &index);
    void reloadSelectedOcs();

    void on_txtReelNo_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::oc_reel_linking_b *ui;
    QSqlDatabase db;
};

#endif // OC_REEL_LINKING_B_H
