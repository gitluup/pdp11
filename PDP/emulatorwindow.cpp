#include "emulatorwindow.h"
#include "ui_emulatorwindow.h"

EmulatorWindow::EmulatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmulatorWindow)
{
    ui->setupUi(this);
}

EmulatorWindow::~EmulatorWindow()
{
    delete ui;
}
