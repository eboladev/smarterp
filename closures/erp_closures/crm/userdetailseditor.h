#ifndef USERDETAILSEDITOR_H
#define USERDETAILSEDITOR_H

#include <QDialog>

namespace Ui {
class UserDetailsEditor;
}

class UserDetailsEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit UserDetailsEditor(QWidget *parent = 0, bool IsAdding = false);
    ~UserDetailsEditor();
    
    bool isAdding() const;
    void setIsAdding(bool isAdding);

    QString currentID() const;
    void setCurrentID(const QString &currentID);

private slots:
    void on_cmdSave_clicked();

private:
    Ui::UserDetailsEditor *ui;
    bool m_isAdding;
    QString m_currentID;

    bool fromNew;
};

#endif // USERDETAILSEDITOR_H
