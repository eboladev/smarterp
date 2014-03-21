#ifndef ChatWindow_H
#define ChatWindow_H

#include <QMainWindow>
#include <QtSql>



namespace Ui {
class ChatWindow;
}

class QTimer;

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0, QSqlDatabase database =  QSqlDatabase());
    ~ChatWindow();
    QString recepient;
    QString sender;
private slots:
    void on_cmdSendMessage_clicked();
    void updateMessages();
    void on_txtMessage_returnPressed();

private:
    QTimer *messageTimer;
    Ui::ChatWindow *ui;
    QSqlDatabase db;
};

#endif // ChatWindow_H
