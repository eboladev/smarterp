#ifndef ARTWORKLIST_H
#define ARTWORKLIST_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif

#include <QMainWindow>
#include <QDialog>

namespace Ui {
class ArtworkList;
}

class ArtworkList : public QDialog
{
    Q_OBJECT
    
public:
    explicit ArtworkList(QWidget *parent = 0);
    ~ArtworkList();
    
private:
    Ui::ArtworkList *ui;
};

#endif // ARTWORKLIST_H
