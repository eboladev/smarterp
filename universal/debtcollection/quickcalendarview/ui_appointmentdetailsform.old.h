/********************************************************************************
** Form generated from reading UI file 'appointmentdetailsform.ui'
**
** Created: Thu 28. Jan 02:35:29 2010
**      by: Qt User Interface Compiler version 4.6.0
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
#include <QtGui/QFormLayout>
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
    QFormLayout *formLayout;
    QLabel *calendarLabel;
    QComboBox *calendarCombo;
    QLabel *startLabel;
    QHBoxLayout *startLayout;
    QDateEdit *startDateEdit;
    QLabel *startTimeLabel;
    QTimeEdit *startTimeEdit;
    QSpacerItem *startSpacer;
    QLabel *endLabel;
    QLabel *subjectLabel;
    QLabel *placeLabel;
    QLabel *descriptionLabel;
    QPlainTextEdit *descriptionEdit;
    QLineEdit *placeEdit;
    QLineEdit *subjectEdit;
    QHBoxLayout *endLayout;
    QDateEdit *endDateEdit;
    QLabel *endTimeLabel;
    QTimeEdit *endTimeEdit;
    QSpacerItem *endSpacer;
    QHBoxLayout *buttonsLayout;
    QSpacerItem *buttonsSpacer;
    QPushButton *deleteAppointmentButton;
    QPushButton *discardChangesButton;
    QPushButton *saveChangesButton;

    void setupUi(QWidget *AppointmentDetailsForm)
    {
        if (AppointmentDetailsForm->objectName().isEmpty())
            AppointmentDetailsForm->setObjectName(QString::fromUtf8("AppointmentDetailsForm"));
        AppointmentDetailsForm->resize(450, 228);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AppointmentDetailsForm->sizePolicy().hasHeightForWidth());
        AppointmentDetailsForm->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(AppointmentDetailsForm);
#ifndef Q_OS_MAC
        verticalLayout->setContentsMargins(9, 9, 9, 9);
#endif
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        calendarLabel = new QLabel(AppointmentDetailsForm);
        calendarLabel->setObjectName(QString::fromUtf8("calendarLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, calendarLabel);

        calendarCombo = new QComboBox(AppointmentDetailsForm);
        calendarCombo->setObjectName(QString::fromUtf8("calendarCombo"));

        formLayout->setWidget(0, QFormLayout::FieldRole, calendarCombo);

        startLabel = new QLabel(AppointmentDetailsForm);
        startLabel->setObjectName(QString::fromUtf8("startLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, startLabel);

        startLayout = new QHBoxLayout();
        startLayout->setObjectName(QString::fromUtf8("startLayout"));
        startDateEdit = new QDateEdit(AppointmentDetailsForm);
        startDateEdit->setObjectName(QString::fromUtf8("startDateEdit"));
        startDateEdit->setCalendarPopup(true);

        startLayout->addWidget(startDateEdit);

        startTimeLabel = new QLabel(AppointmentDetailsForm);
        startTimeLabel->setObjectName(QString::fromUtf8("startTimeLabel"));

        startLayout->addWidget(startTimeLabel);

        startTimeEdit = new QTimeEdit(AppointmentDetailsForm);
        startTimeEdit->setObjectName(QString::fromUtf8("startTimeEdit"));
        startTimeEdit->setCalendarPopup(false);

        startLayout->addWidget(startTimeEdit);

        startSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        startLayout->addItem(startSpacer);


        formLayout->setLayout(1, QFormLayout::FieldRole, startLayout);

        endLabel = new QLabel(AppointmentDetailsForm);
        endLabel->setObjectName(QString::fromUtf8("endLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, endLabel);

        subjectLabel = new QLabel(AppointmentDetailsForm);
        subjectLabel->setObjectName(QString::fromUtf8("subjectLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, subjectLabel);

        placeLabel = new QLabel(AppointmentDetailsForm);
        placeLabel->setObjectName(QString::fromUtf8("placeLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, placeLabel);

        descriptionLabel = new QLabel(AppointmentDetailsForm);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, descriptionLabel);

        descriptionEdit = new QPlainTextEdit(AppointmentDetailsForm);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
        descriptionEdit->setMaximumSize(QSize(16777215, 60));

        formLayout->setWidget(5, QFormLayout::FieldRole, descriptionEdit);

        placeEdit = new QLineEdit(AppointmentDetailsForm);
        placeEdit->setObjectName(QString::fromUtf8("placeEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, placeEdit);

        subjectEdit = new QLineEdit(AppointmentDetailsForm);
        subjectEdit->setObjectName(QString::fromUtf8("subjectEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, subjectEdit);

        endLayout = new QHBoxLayout();
        endLayout->setObjectName(QString::fromUtf8("endLayout"));
        endDateEdit = new QDateEdit(AppointmentDetailsForm);
        endDateEdit->setObjectName(QString::fromUtf8("endDateEdit"));
        endDateEdit->setCalendarPopup(true);

        endLayout->addWidget(endDateEdit);

        endTimeLabel = new QLabel(AppointmentDetailsForm);
        endTimeLabel->setObjectName(QString::fromUtf8("endTimeLabel"));

        endLayout->addWidget(endTimeLabel);

        endTimeEdit = new QTimeEdit(AppointmentDetailsForm);
        endTimeEdit->setObjectName(QString::fromUtf8("endTimeEdit"));
        endTimeEdit->setCalendarPopup(false);

        endLayout->addWidget(endTimeEdit);

        endSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        endLayout->addItem(endSpacer);


        formLayout->setLayout(2, QFormLayout::FieldRole, endLayout);


        verticalLayout->addLayout(formLayout);

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

        QWidget::setTabOrder(calendarCombo, startDateEdit);
        QWidget::setTabOrder(startDateEdit, startTimeEdit);
        QWidget::setTabOrder(startTimeEdit, endDateEdit);
        QWidget::setTabOrder(endDateEdit, endTimeEdit);
        QWidget::setTabOrder(endTimeEdit, subjectEdit);
        QWidget::setTabOrder(subjectEdit, placeEdit);
        QWidget::setTabOrder(placeEdit, descriptionEdit);
        QWidget::setTabOrder(descriptionEdit, saveChangesButton);
        QWidget::setTabOrder(saveChangesButton, discardChangesButton);
        QWidget::setTabOrder(discardChangesButton, deleteAppointmentButton);

        retranslateUi(AppointmentDetailsForm);

        QMetaObject::connectSlotsByName(AppointmentDetailsForm);
    } // setupUi

    void retranslateUi(QWidget *AppointmentDetailsForm)
    {
        AppointmentDetailsForm->setWindowTitle(QApplication::translate("AppointmentDetailsForm", "Appointment Details", 0, QApplication::UnicodeUTF8));
        calendarLabel->setText(QApplication::translate("AppointmentDetailsForm", "Calendar", 0, QApplication::UnicodeUTF8));
        startLabel->setText(QApplication::translate("AppointmentDetailsForm", "Start", 0, QApplication::UnicodeUTF8));
        startTimeLabel->setText(QApplication::translate("AppointmentDetailsForm", "Time", 0, QApplication::UnicodeUTF8));
        startTimeEdit->setDisplayFormat(QApplication::translate("AppointmentDetailsForm", "H:mm", 0, QApplication::UnicodeUTF8));
        endLabel->setText(QApplication::translate("AppointmentDetailsForm", "End", 0, QApplication::UnicodeUTF8));
        subjectLabel->setText(QApplication::translate("AppointmentDetailsForm", "Subject", 0, QApplication::UnicodeUTF8));
        placeLabel->setText(QApplication::translate("AppointmentDetailsForm", "Location", 0, QApplication::UnicodeUTF8));
        descriptionLabel->setText(QApplication::translate("AppointmentDetailsForm", "Description", 0, QApplication::UnicodeUTF8));
        endTimeLabel->setText(QApplication::translate("AppointmentDetailsForm", "Time", 0, QApplication::UnicodeUTF8));
        endTimeEdit->setDisplayFormat(QApplication::translate("AppointmentDetailsForm", "H:mm", 0, QApplication::UnicodeUTF8));
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
