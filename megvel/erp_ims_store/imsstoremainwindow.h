#ifndef IMSSTOREMAINWINDOW_H
#define IMSSTOREMAINWINDOW_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
#include <QMainWindow>
#include <QDialog>

namespace Ui {
class ImsStoreMainWindow;
}

class ImsStoreMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ImsStoreMainWindow(QWidget *parent = 0,
                                QSqlDatabase database = QSqlDatabase()
                                );
    ~ImsStoreMainWindow();
private slots:
    void reloadContainers();
    void showReels();
    void on_trvContainers_clicked(const QModelIndex &index);

    void on_cmdSave_clicked();

private:
    Ui::ImsStoreMainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *reelsModel;
};

#endif // IMSSTOREMAINWINDOW_H
