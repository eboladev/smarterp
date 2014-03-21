#ifndef NEWARTWORKWIZARD_H
#define NEWARTWORKWIZARD_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif

namespace Ui {
class NewArtworkWizard;
}
#include <QMainWindow>
#include <QDialog>
#include <QWizard>
class NewArtworkWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit NewArtworkWizard(QWidget *parent = 0);
    ~NewArtworkWizard();
    
private slots:
    void on_lstCustomers_clicked(const QModelIndex &index);

    void on_cmdSave_clicked();

    void calculateFilmSize();
    void calculateEnteredFilmSize();
private:
    Ui::NewArtworkWizard *ui;
};

#endif // NEWARTWORKWIZARD_H
