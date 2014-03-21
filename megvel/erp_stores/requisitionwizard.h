#ifndef REQUISITIONWIZARD_H
#define REQUISITIONWIZARD_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QDateTime>
#include <QMainWindow>
#include <QDialog>
#include <QWizard>
namespace Ui {
class RequisitionWizard;
}

class RequisitionWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit RequisitionWizard(QWidget *parent = 0, bool isFilm = false);
    ~RequisitionWizard();

private slots:
    void on_RequisitionWizard_currentIdChanged(int id);
    void reloadDetails();
    void saveRequisition();
    void on_tblSelectedItems_cellChanged(int row, int column);

    void on_cboSupplier_currentIndexChanged(int index);

    void on_txtRequestedBy_textChanged(const QString &arg1);

    void on_txtDepartment_textChanged(const QString &arg1);

    void on_dtpDateRequested_dateTimeChanged(const QDateTime &dateTime);

    void on_dtpDateRequested_dateChanged(const QDate &date);

    void on_dtpDateRequired_dateChanged(const QDate &date);

    void on_cmdFinish_clicked();

    void on_RequisitionWizard_finished(int result);

    void on_cmdAddItemToRequisition_clicked();

    void on_RequisitionWizard_rejected();

private:
    Ui::RequisitionWizard *ui;
    bool m_isFilm;
    bool saved;
};

#endif // REQUISITIONWIZARD_H
