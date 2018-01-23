#ifndef EMULATORWINDOW_H
#define EMULATORWINDOW_H

#include <vector>

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QString>

#include "src/emulator/emulator.h"

#define DEFAULT_BATCH_SIZE 16

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
    QPlainTextEdit * ramOutput;
    std::vector<QLabel *> registerLabels;

    Emulator * emulator;

    void DrawRegistersState(std::vector<uint16_t> * registersData);
    void DrawMemoryState(uint16_t address, size_t batchSize);
};

#endif // EMULATORWINDOW_H
