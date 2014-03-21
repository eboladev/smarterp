#ifndef TLMPREFERENCES_H
#define TLMPREFERENCES_H

#include <QDialog>

namespace Ui {
class TLMPreferences;
}

class TLMPreferences : public QDialog
{
    Q_OBJECT
    
public:
    explicit TLMPreferences(QWidget *parent = 0);
    ~TLMPreferences();
    
private slots:
    void on_cmdSave_clicked();

private:
    Ui::TLMPreferences *ui;
};

#endif // TLMPREFERENCES_H
