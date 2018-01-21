#ifndef EMULATORWINDOW_H
#define EMULATORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "src/emulator/emulator.h"

namespace Ui {
class EmulatorWindow;
}

class EmulatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmulatorWindow(QWidget *parent = 0);
    ~EmulatorWindow();

private slots:
    void startButtonSlot();
    void exitButtonSlot();

private:
    Ui::EmulatorWindow *ui;
    QPushButton * startButton;
    QPushButton * exitButton;

    Emulator * emulator;
};

#endif // EMULATORWINDOW_H
