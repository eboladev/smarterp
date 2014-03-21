/********************************************************************************
** Form generated from reading UI file 'mydock.ui'
**
** Created: Wed Feb 15 08:23:58 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDOCK_H
#define UI_MYDOCK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyDock
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *MyDock)
    {
        if (MyDock->objectName().isEmpty())
            MyDock->setObjectName(QString::fromUtf8("MyDock"));
        MyDock->resize(197, 457);
        verticalLayout = new QVBoxLayout(MyDock);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget = new QTreeWidget(MyDock);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        verticalLayout->addWidget(treeWidget);


        retranslateUi(MyDock);

        QMetaObject::connectSlotsByName(MyDock);
    } // setupUi

    void retranslateUi(QWidget *MyDock)
    {
        MyDock->setWindowTitle(QApplication::translate("MyDock", "Form", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MyDock", "Query Fields", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyDock: public Ui_MyDock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDOCK_H
