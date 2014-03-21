#ifndef ERPWELCOMESCREEN_H
#define ERPWELCOMESCREEN_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class ERPWelcomeScreen;
}

class ERPWelcomeScreen : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ERPWelcomeScreen(QWidget *parent = 0);
    ~ERPWelcomeScreen();
private:
    Ui::ERPWelcomeScreen *ui;
};

#endif // ERPWELCOMESCREEN_H
