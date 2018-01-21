#include "emulatorwindow.h"
#include "ui_emulatorwindow.h"

EmulatorWindow::EmulatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmulatorWindow)
{
    ui->setupUi(this);
    this->emulator = new Emulator;

    this->startButton = ui->startButton;
    this->exitButton = ui->exitButton;

    connect(this->startButton, SIGNAL(clicked()), this, SLOT(startButtonSlot()));
    connect(this->exitButton, SIGNAL(clicked()), this, SLOT(exitButtonSlot()));
}

EmulatorWindow::~EmulatorWindow()
{
    delete ui;
}

void EmulatorWindow::startButtonSlot()
{
    emulator->Start();
    startButton->setText("Started!");
}

void EmulatorWindow::exitButtonSlot()
{
   this->close();
}
