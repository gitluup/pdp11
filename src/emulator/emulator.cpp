#include "emulator.h"


Emulator::Emulator()
    : memory(), cpu(&memory)
{

}

Emulator::~Emulator()
{

}

void Emulator::Work()
{
    // TODO: fetch instructions from RAM

    this->cpu.PerformInstr();
}
