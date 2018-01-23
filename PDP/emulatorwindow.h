#ifndef EMULATORWINDOW_H
#define EMULATORWINDOW_H

#include <vector>

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QString>

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
    void nextButtonSlot();
    void textEditSlot();
    void rewindButtonSlot();

private:
    Ui::EmulatorWindow *ui;
    QPushButton * startButton;
    QPushButton * exitButton;
    QPushButton * nextButton;
    QPushButton * rewindButton;

    std::vector<QLabel *> registerLabels;

    Emulator * emulator;

    void DrawRegistersState(std::vector<uint16_t> * registersData);
};

#endif // EMULATORWINDOW_H
