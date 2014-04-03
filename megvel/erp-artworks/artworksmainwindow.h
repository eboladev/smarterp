#ifndef ARTWORKSMAINWINDOW_H
#define ARTWORKSMAINWINDOW_H
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
namespace Ui {
class ArtworksMainWindow;
}

#include <QMainWindow>
#include <QDialog>


class ArtworksMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ArtworksMainWindow(QWidget *parent = 0, QSqlDatabase = QSqlDatabase());
    ~ArtworksMainWindow();
    
private slots:
    void on_cmdNewArtwork_clicked();

    void on_commandLinkButton_2_clicked();

private:
    Ui::ArtworksMainWindow *ui;
    QSqlDatabase db;
};

#endif // ARTWORKSMAINWINDOW_H
