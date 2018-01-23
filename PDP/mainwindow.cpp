#include <QApplication>
#include "emulatorwindow.h"
#include "src/emulator/emulator.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmulatorWindow w;
    w.show();

    return a.exec();
}
