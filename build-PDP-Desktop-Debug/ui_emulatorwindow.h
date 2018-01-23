/********************************************************************************
** Form generated from reading UI file 'emulatorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMULATORWINDOW_H
#define UI_EMULATORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmulatorWindow
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *startButton;
    QPushButton *nextButton;
    QPushButton *rewindButton;
    QPushButton *exitButton;
    QFrame *horLine;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *regValueLayout;
    QLabel *r0_value;
    QLabel *r1_value;
    QLabel *r2_value;
    QLabel *r3_value;
    QLabel *r4_value;
    QLabel *r5_value;
    QLabel *r6_value;
    QLabel *r7_value;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *regNameLayout;
    QLabel *r0_label;
    QLabel *r1_label;
    QLabel *r2_label;
    QLabel *r3_label;
    QLabel *r4_label;
    QLabel *r5_label;
    QLabel *r6_label;
    QLabel *r7_label;
    QFrame *vertLine;
    QLabel *label;
    QPlainTextEdit *ramEdit;
    QLabel *label_2;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *EmulatorWindow)
    {
        if (EmulatorWindow->objectName().isEmpty())
            EmulatorWindow->setObjectName(QStringLiteral("EmulatorWindow"));
        EmulatorWindow->resize(628, 453);
        centralWidget = new QWidget(EmulatorWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 390, 531, 32));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        startButton = new QPushButton(horizontalLayoutWidget);
        startButton->setObjectName(QStringLiteral("startButton"));

        horizontalLayout->addWidget(startButton);

        nextButton = new QPushButton(horizontalLayoutWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));

        horizontalLayout->addWidget(nextButton);

        rewindButton = new QPushButton(horizontalLayoutWidget);
        rewindButton->setObjectName(QStringLiteral("rewindButton"));

        horizontalLayout->addWidget(rewindButton);

        exitButton = new QPushButton(horizontalLayoutWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        horizontalLayout->addWidget(exitButton);

        horLine = new QFrame(centralWidget);
        horLine->setObjectName(QStringLiteral("horLine"));
        horLine->setGeometry(QRect(0, 350, 661, 41));
        horLine->setFrameShape(QFrame::HLine);
        horLine->setFrameShadow(QFrame::Sunken);
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(550, 30, 51, 321));
        regValueLayout = new QVBoxLayout(verticalLayoutWidget_2);
        regValueLayout->setSpacing(6);
        regValueLayout->setContentsMargins(11, 11, 11, 11);
        regValueLayout->setObjectName(QStringLiteral("regValueLayout"));
        regValueLayout->setContentsMargins(0, 0, 0, 0);
        r0_value = new QLabel(verticalLayoutWidget_2);
        r0_value->setObjectName(QStringLiteral("r0_value"));
        r0_value->setLayoutDirection(Qt::RightToLeft);

        regValueLayout->addWidget(r0_value);

        r1_value = new QLabel(verticalLayoutWidget_2);
        r1_value->setObjectName(QStringLiteral("r1_value"));
        r1_value->setLayoutDirection(Qt::RightToLeft);

        regValueLayout->addWidget(r1_value);

        r2_value = new QLabel(verticalLayoutWidget_2);
        r2_value->setObjectName(QStringLiteral("r2_value"));
        r2_value->setLayoutDirection(Qt::RightToLeft);

        regValueLayout->addWidget(r2_value);

        r3_value = new QLabel(verticalLayoutWidget_2);
        r3_value->setObjectName(QStringLiteral("r3_value"));
        r3_value->setLayoutDirection(Qt::RightToLeft);

        regValueLayout->addWidget(r3_value);

        r4_value = new QLabel(verticalLayoutWidget_2);
        r4_value->setObjectName(QStringLiteral("r4_value"));
        r4_value->setLayoutDirection(Qt::RightToLeft);

        regValueLayout->addWidget(r4_value);

        r5_value = new QLabel(verticalLayoutWidget_2);
        r5_value->setObjectName(QStringLiteral("r5_value"));
        r5_value->setLayoutDirection(Qt::RightToLeft);

        regValueLayout->addWidget(r5_value);

        r6_value = new QLabel(verticalLayoutWidget_2);
        r6_value->setObjectName(QStringLiteral("r6_value"));
        r6_value->setLayoutDirection(Qt::RightToLeft);

        regValueLayout->addWidget(r6_value);

        r7_value = new QLabel(verticalLayoutWidget_2);
        r7_value->setObjectName(QStringLiteral("r7_value"));
        r7_value->setLayoutDirection(Qt::RightToLeft);

        regValueLayout->addWidget(r7_value);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(500, 30, 41, 321));
        regNameLayout = new QVBoxLayout(verticalLayoutWidget);
        regNameLayout->setSpacing(6);
        regNameLayout->setContentsMargins(11, 11, 11, 11);
        regNameLayout->setObjectName(QStringLiteral("regNameLayout"));
        regNameLayout->setContentsMargins(0, 0, 0, 0);
        r0_label = new QLabel(verticalLayoutWidget);
        r0_label->setObjectName(QStringLiteral("r0_label"));

        regNameLayout->addWidget(r0_label);

        r1_label = new QLabel(verticalLayoutWidget);
        r1_label->setObjectName(QStringLiteral("r1_label"));

        regNameLayout->addWidget(r1_label);

        r2_label = new QLabel(verticalLayoutWidget);
        r2_label->setObjectName(QStringLiteral("r2_label"));

        regNameLayout->addWidget(r2_label);

        r3_label = new QLabel(verticalLayoutWidget);
        r3_label->setObjectName(QStringLiteral("r3_label"));

        regNameLayout->addWidget(r3_label);

        r4_label = new QLabel(verticalLayoutWidget);
        r4_label->setObjectName(QStringLiteral("r4_label"));

        regNameLayout->addWidget(r4_label);

        r5_label = new QLabel(verticalLayoutWidget);
        r5_label->setObjectName(QStringLiteral("r5_label"));

        regNameLayout->addWidget(r5_label);

        r6_label = new QLabel(verticalLayoutWidget);
        r6_label->setObjectName(QStringLiteral("r6_label"));

        regNameLayout->addWidget(r6_label);

        r7_label = new QLabel(verticalLayoutWidget);
        r7_label->setObjectName(QStringLiteral("r7_label"));

        regNameLayout->addWidget(r7_label);

        vertLine = new QFrame(centralWidget);
        vertLine->setObjectName(QStringLiteral("vertLine"));
        vertLine->setGeometry(QRect(473, 0, 16, 371));
        vertLine->setFrameShape(QFrame::VLine);
        vertLine->setFrameShadow(QFrame::Sunken);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(500, 10, 101, 16));
        ramEdit = new QPlainTextEdit(centralWidget);
        ramEdit->setObjectName(QStringLiteral("ramEdit"));
        ramEdit->setGeometry(QRect(10, 30, 451, 321));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 60, 16));
        EmulatorWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(EmulatorWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EmulatorWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(EmulatorWindow);

        QMetaObject::connectSlotsByName(EmulatorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EmulatorWindow)
    {
        EmulatorWindow->setWindowTitle(QApplication::translate("EmulatorWindow", "EmulatorWindow", 0));
        startButton->setText(QApplication::translate("EmulatorWindow", "Start", 0));
        nextButton->setText(QApplication::translate("EmulatorWindow", "Next step", 0));
        rewindButton->setText(QApplication::translate("EmulatorWindow", "Rewind", 0));
        exitButton->setText(QApplication::translate("EmulatorWindow", "Exit", 0));
        r0_value->setText(QApplication::translate("EmulatorWindow", "0", 0));
        r1_value->setText(QApplication::translate("EmulatorWindow", "0", 0));
        r2_value->setText(QApplication::translate("EmulatorWindow", "0", 0));
        r3_value->setText(QApplication::translate("EmulatorWindow", "0", 0));
        r4_value->setText(QApplication::translate("EmulatorWindow", "0", 0));
        r5_value->setText(QApplication::translate("EmulatorWindow", "0", 0));
        r6_value->setText(QApplication::translate("EmulatorWindow", "0", 0));
        r7_value->setText(QApplication::translate("EmulatorWindow", "0", 0));
        r0_label->setText(QApplication::translate("EmulatorWindow", "R0:", 0));
        r1_label->setText(QApplication::translate("EmulatorWindow", "R1:", 0));
        r2_label->setText(QApplication::translate("EmulatorWindow", "R2:", 0));
        r3_label->setText(QApplication::translate("EmulatorWindow", "R3:", 0));
        r4_label->setText(QApplication::translate("EmulatorWindow", "R4:", 0));
        r5_label->setText(QApplication::translate("EmulatorWindow", "R5:", 0));
        r6_label->setText(QApplication::translate("EmulatorWindow", "R6:", 0));
        r7_label->setText(QApplication::translate("EmulatorWindow", "R7:", 0));
        label->setText(QApplication::translate("EmulatorWindow", "Register Trace:", 0));
        label_2->setText(QApplication::translate("EmulatorWindow", "RAM:", 0));
    } // retranslateUi

};

namespace Ui {
    class EmulatorWindow: public Ui_EmulatorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMULATORWINDOW_H
