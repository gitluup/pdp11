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
    this->rewindButton = ui->rewindButton;

    this->ramOutput = ui->ramEdit;

    /* Set up labels */
    registerLabels.push_back(ui->r0_value);
    registerLabels.push_back(ui->r1_value);
    registerLabels.push_back(ui->r2_value);
    registerLabels.push_back(ui->r3_value);
    registerLabels.push_back(ui->r4_value);
    registerLabels.push_back(ui->r5_value);
    registerLabels.push_back(ui->r6_value);
    registerLabels.push_back(ui->r7_value);

    connect(this->startButton, SIGNAL(clicked()), this, SLOT(startButtonSlot()));
    connect(this->exitButton, SIGNAL(clicked()), this, SLOT(exitButtonSlot()));
    connect(this->nextButton, SIGNAL(clicked()), this, SLOT(nextButtonSlot()));
    connect(this->rewindButton, SIGNAL(clicked()), this, SLOT(rewindButtonSlot()));
    // connect(this->terminalTextEdit, SIGNAL(readyReadStandardOutput()), this, SLOT(textEditSlot()));
}

EmulatorWindow::~EmulatorWindow()
{
    delete ui;
    delete emulator;
}

void EmulatorWindow::startButtonSlot()
{
    std::vector<uint16_t> registerOutput;
    emulator->Start(&registerOutput);
    startButton->setText("Started!");

    DrawRegistersState(&registerOutput);

    DrawMemoryState(registerOutput[R7], DEFAULT_BATCH_SIZE);
}

void EmulatorWindow::rewindButtonSlot()
{
    if (emulator) {
        delete emulator;
    }

    emulator = new Emulator();

    startButton->setText("Start");

    std::vector<uint16_t> startRegistersValues;
    emulator->GetRegistersState(&startRegistersValues);
    DrawRegistersState(&startRegistersValues);

    ramOutput->clear();
}

void EmulatorWindow::DrawRegistersState(std::vector<uint16_t> * registersData)
{
    assert(registersData);
    assert(registersData->size() == REGISTERS_NUM);

    for (size_t i = 0; i < registersData->size(); i++) {
        QString resultString = QString::number((*registersData)[i]);
        registerLabels[i]->setText(resultString);
    }
}

void EmulatorWindow::DrawMemoryState(uint16_t address, size_t batchSize)
{
    std::vector<uint16_t> memoryBatch;

    emulator->GetMemoryBatch(&memoryBatch, address, batchSize);

    ramOutput->clear();
    for (size_t i = 0; i < memoryBatch.size(); i++) {
        QString val = QString::number(memoryBatch[i], 16).toUpper();
        ramOutput->appendPlainText(val);
    }
}

void EmulatorWindow::exitButtonSlot()
{
    this->close();
}

void EmulatorWindow::nextButtonSlot()
{
    std::vector<uint16_t> registerOutput;
    emulator->Next(&registerOutput);
    DrawRegistersState(&registerOutput);

    DrawMemoryState(registerOutput[R7], DEFAULT_BATCH_SIZE);
}

void EmulatorWindow::textEditSlot()
{
}
