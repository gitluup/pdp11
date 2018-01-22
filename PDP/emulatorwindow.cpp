#include "emulatorwindow.h"
#include "ui_emulatorwindow.h"

EmulatorWindow::EmulatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmulatorWindow)
{
    ui->setupUi(this);
    this->emulator = new Emulator;

    /* Get pointers to elements from UI layout */
    this->startButton = ui->startButton;
    this->exitButton = ui->exitButton;
    this->nextButton = ui->nextButton;

    connect(this->startButton, SIGNAL(clicked()), this, SLOT(startButtonSlot()));
    connect(this->exitButton, SIGNAL(clicked()), this, SLOT(exitButtonSlot()));
    connect(this->nextButton, SIGNAL(clicked()), this, SLOT(nextButtonSlot()));
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

void EmulatorWindow::nextButtonSlot()
{
    emulator->Next();
}
