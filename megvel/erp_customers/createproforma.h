#ifndef CREATEPROFORMA_H
#define CREATEPROFORMA_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif

#include <QDialog>

namespace Ui {
class CreateProforma;
}

class CreateProforma : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateProforma(QWidget *parent = 0);
    ~CreateProforma();
    
private:
    Ui::CreateProforma *ui;
};

#endif // CREATEPROFORMA_H
