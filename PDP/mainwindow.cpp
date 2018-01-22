#include "emulatorwindow.h"
#include <iostream>
#include <QApplication>

#include "src/emulator/emulator.h"

int main(int argc, char *argv[]) {
    Emulator emulator;
    emulator.Start();

    QApplication a(argc, argv);
    EmulatorWindow w;
    w.show();

    return a.exec();
}
