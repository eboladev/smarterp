/********************************************************************************
** Form generated from reading UI file 'appointmentdetailsform.ui'
**
** Created: Tue Feb 12 10:31:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPOINTMENTDETAILSFORM_H
#define UI_APPOINTMENTDETAILSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppointmentDetailsForm
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *calendarLabel;
    QComboBox *calendarCombo;
    QLabel *label;
    QComboBox *cboCustomer;
    QGridLayout *gridLayout;
    QLabel *startLabel;
    QLabel *startTimeLabel;
    QTimeEdit *startTimeEdit;
    QLabel *label_3;
    QDateEdit *endDateEdit;
    QLabel *label_2;
    QDateEdit *startDateEdit;
    QTimeEdit *endTimeEdit;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_3;
    QLabel *placeLabel;
    QLabel *descriptionLabel;
    QLabel *subjectLabel;
    QLineEdit *subjectEdit;
    QLineEdit *placeEdit;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *descriptionEdit;
    QHBoxLayout *buttonsLayout;
    QSpacerItem *buttonsSpacer;
    QPushButton *deleteAppointmentButton;
    QPushButton *discardChangesButton;
    QPushButton *saveChangesButton;

    void setupUi(QWidget *AppointmentDetailsForm)
    {
        if (AppointmentDetailsForm->objectName().isEmpty())
            AppointmentDetailsForm->setObjectName(QString::fromUtf8("AppointmentDetailsForm"));
        AppointmentDetailsForm->resize(420, 422);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AppointmentDetailsForm->sizePolicy().hasHeightForWidth());
        AppointmentDetailsForm->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(AppointmentDetailsForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        calendarLabel = new QLabel(AppointmentDetailsForm);
        calendarLabel->setObjectName(QString::fromUtf8("calendarLabel"));

        gridLayout_2->addWidget(calendarLabel, 0, 0, 1, 1);

        calendarCombo = new QComboBox(AppointmentDetailsForm);
        calendarCombo->setObjectName(QString::fromUtf8("calendarCombo"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(calendarCombo->sizePolicy().hasHeightForWidth());
        calendarCombo->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(calendarCombo, 0, 1, 1, 1);

        label = new QLabel(AppointmentDetailsForm);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        cboCustomer = new QComboBox(AppointmentDetailsForm);
        cboCustomer->setObjectName(QString::fromUtf8("cboCustomer"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(2);
        sizePolicy2.setHeightForWidth(cboCustomer->sizePolicy().hasHeightForWidth());
        cboCustomer->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(cboCustomer, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        startLabel = new QLabel(AppointmentDetailsForm);
        startLabel->setObjectName(QString::fromUtf8("startLabel"));

        gridLayout->addWidget(startLabel, 1, 0, 1, 1);

        startTimeLabel = new QLabel(AppointmentDetailsForm);
        startTimeLabel->setObjectName(QString::fromUtf8("startTimeLabel"));

        gridLayout->addWidget(startTimeLabel, 2, 0, 1, 1);

        startTimeEdit = new QTimeEdit(AppointmentDetailsForm);
        startTimeEdit->setObjectName(QString::fromUtf8("startTimeEdit"));
        startTimeEdit->setCalendarPopup(false);

        gridLayout->addWidget(startTimeEdit, 2, 1, 1, 1);

        label_3 = new QLabel(AppointmentDetailsForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        endDateEdit = new QDateEdit(AppointmentDetailsForm);
        endDateEdit->setObjectName(QString::fromUtf8("endDateEdit"));
        endDateEdit->setCalendarPopup(true);

        gridLayout->addWidget(endDateEdit, 1, 2, 1, 1);

        label_2 = new QLabel(AppointmentDetailsForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        startDateEdit = new QDateEdit(AppointmentDetailsForm);
        startDateEdit->setObjectName(QString::fromUtf8("startDateEdit"));
        startDateEdit->setCalendarPopup(true);

        gridLayout->addWidget(startDateEdit, 1, 1, 1, 1);

        endTimeEdit = new QTimeEdit(AppointmentDetailsForm);
        endTimeEdit->setObjectName(QString::fromUtf8("endTimeEdit"));
        endTimeEdit->setCalendarPopup(false);

        gridLayout->addWidget(endTimeEdit, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        placeLabel = new QLabel(AppointmentDetailsForm);
        placeLabel->setObjectName(QString::fromUtf8("placeLabel"));

        gridLayout_3->addWidget(placeLabel, 1, 0, 1, 1);

        descriptionLabel = new QLabel(AppointmentDetailsForm);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));

        gridLayout_3->addWidget(descriptionLabel, 2, 0, 1, 1);

        subjectLabel = new QLabel(AppointmentDetailsForm);
        subjectLabel->setObjectName(QString::fromUtf8("subjectLabel"));

        gridLayout_3->addWidget(subjectLabel, 0, 0, 1, 1);

        subjectEdit = new QLineEdit(AppointmentDetailsForm);
        subjectEdit->setObjectName(QString::fromUtf8("subjectEdit"));

        gridLayout_3->addWidget(subjectEdit, 0, 1, 1, 1);

        placeEdit = new QLineEdit(AppointmentDetailsForm);
        placeEdit->setObjectName(QString::fromUtf8("placeEdit"));

        gridLayout_3->addWidget(placeEdit, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 0, 1, 1);

        descriptionEdit = new QPlainTextEdit(AppointmentDetailsForm);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
        descriptionEdit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(descriptionEdit, 2, 1, 2, 1);


        verticalLayout->addLayout(gridLayout_3);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName(QString::fromUtf8("buttonsLayout"));
        buttonsSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonsLayout->addItem(buttonsSpacer);

        deleteAppointmentButton = new QPushButton(AppointmentDetailsForm);
        deleteAppointmentButton->setObjectName(QString::fromUtf8("deleteAppointmentButton"));

        buttonsLayout->addWidget(deleteAppointmentButton);

        discardChangesButton = new QPushButton(AppointmentDetailsForm);
        discardChangesButton->setObjectName(QString::fromUtf8("discardChangesButton"));

        buttonsLayout->addWidget(discardChangesButton);

        saveChangesButton = new QPushButton(AppointmentDetailsForm);
        saveChangesButton->setObjectName(QString::fromUtf8("saveChangesButton"));

        buttonsLayout->addWidget(saveChangesButton);


        verticalLayout->addLayout(buttonsLayout);

        QWidget::setTabOrder(calendarCombo, cboCustomer);
        QWidget::setTabOrder(cboCustomer, startDateEdit);
        QWidget::setTabOrder(startDateEdit, endDateEdit);
        QWidget::setTabOrder(endDateEdit, startTimeEdit);
        QWidget::setTabOrder(startTimeEdit, endTimeEdit);
        QWidget::setTabOrder(endTimeEdit, subjectEdit);
        QWidget::setTabOrder(subjectEdit, placeEdit);
        QWidget::setTabOrder(placeEdit, descriptionEdit);
        QWidget::setTabOrder(descriptionEdit, deleteAppointmentButton);
        QWidget::setTabOrder(deleteAppointmentButton, discardChangesButton);
        QWidget::setTabOrder(discardChangesButton, saveChangesButton);

        retranslateUi(AppointmentDetailsForm);

        QMetaObject::connectSlotsByName(AppointmentDetailsForm);
    } // setupUi

    void retranslateUi(QWidget *AppointmentDetailsForm)
    {
        AppointmentDetailsForm->setWindowTitle(QApplication::translate("AppointmentDetailsForm", "Appointment Details", 0, QApplication::UnicodeUTF8));
        calendarLabel->setText(QApplication::translate("AppointmentDetailsForm", "Appointment Type:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AppointmentDetailsForm", "Customer:", 0, QApplication::UnicodeUTF8));
        startLabel->setText(QApplication::translate("AppointmentDetailsForm", "Date", 0, QApplication::UnicodeUTF8));
        startTimeLabel->setText(QApplication::translate("AppointmentDetailsForm", "Time", 0, QApplication::UnicodeUTF8));
        startTimeEdit->setDisplayFormat(QApplication::translate("AppointmentDetailsForm", "H:mm", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AppointmentDetailsForm", "End", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AppointmentDetailsForm", "Start", 0, QApplication::UnicodeUTF8));
        endTimeEdit->setDisplayFormat(QApplication::translate("AppointmentDetailsForm", "H:mm", 0, QApplication::UnicodeUTF8));
        placeLabel->setText(QApplication::translate("AppointmentDetailsForm", "Location", 0, QApplication::UnicodeUTF8));
        descriptionLabel->setText(QApplication::translate("AppointmentDetailsForm", "Description", 0, QApplication::UnicodeUTF8));
        subjectLabel->setText(QApplication::translate("AppointmentDetailsForm", "Subject", 0, QApplication::UnicodeUTF8));
        deleteAppointmentButton->setText(QApplication::translate("AppointmentDetailsForm", "Delete Appointment", 0, QApplication::UnicodeUTF8));
        discardChangesButton->setText(QApplication::translate("AppointmentDetailsForm", "Discard Changes", 0, QApplication::UnicodeUTF8));
        saveChangesButton->setText(QApplication::translate("AppointmentDetailsForm", "Save Changes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AppointmentDetailsForm: public Ui_AppointmentDetailsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPOINTMENTDETAILSFORM_H
