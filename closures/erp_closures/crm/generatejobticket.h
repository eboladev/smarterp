#ifndef GENERATEJOBTICKET_H
#define GENERATEJOBTICKET_H

#include <QDialog>

class JobTicket;

namespace Ui {
class GenerateJobTicket;
}

class GenerateJobTicket : public QDialog
{
    Q_OBJECT
    
public:
    explicit GenerateJobTicket(QWidget *parent = 0, QString ProductID = QString());
    ~GenerateJobTicket();
    
    QString productID() const;
    void setProductID(const QString &productID);

    JobTicket *jobTicket() const;
    void setJobTicket(JobTicket *jobTicket);

    QString lpoID() const;
    void setLpoID(const QString &lpoID);

private:
    Ui::GenerateJobTicket *ui;
    QString m_productID;
    JobTicket *m_jobTicket;
    QString m_lpoID;
    QString orderId;
private slots:
    void refreshGui();
    void on_spinOrderQty_editingFinished();
    void on_cmdGenerateJobTicket_clicked();
};

#endif // GENERATEJOBTICKET_H
