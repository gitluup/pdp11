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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmulatorWindow
{
public:
    QWidget *centralWidget;
    QPushButton *startButton;
    QMenuBar *menuBar;
    QMenu *menuPDP11_Emulator;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EmulatorWindow)
    {
        if (EmulatorWindow->objectName().isEmpty())
            EmulatorWindow->setObjectName(QStringLiteral("EmulatorWindow"));
        EmulatorWindow->resize(400, 300);
        centralWidget = new QWidget(EmulatorWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(170, 200, 81, 32));
        EmulatorWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EmulatorWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 22));
        menuPDP11_Emulator = new QMenu(menuBar);
        menuPDP11_Emulator->setObjectName(QStringLiteral("menuPDP11_Emulator"));
        EmulatorWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EmulatorWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EmulatorWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EmulatorWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EmulatorWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPDP11_Emulator->menuAction());

        retranslateUi(EmulatorWindow);

        QMetaObject::connectSlotsByName(EmulatorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EmulatorWindow)
    {
        EmulatorWindow->setWindowTitle(QApplication::translate("EmulatorWindow", "EmulatorWindow", 0));
        startButton->setText(QApplication::translate("EmulatorWindow", "Start", 0));
        menuPDP11_Emulator->setTitle(QApplication::translate("EmulatorWindow", "PDP11 Emulator", 0));
    } // retranslateUi

};

namespace Ui {
    class EmulatorWindow: public Ui_EmulatorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMULATORWINDOW_H
