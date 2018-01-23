#include "emulator.h"
#include <iostream>

Emulator::Emulator()
    : memory_(), cpu_(&memory_)
{

}


Emulator::~Emulator()
{

}


std::vector<uint16_t> * Emulator::Start(std::vector<uint16_t> * regOutput)
{
    assert(regOutput);

    uint16_t raw_instr = 1;
    while (raw_instr)
    {
        raw_instr = cpu_.PerformInstr();
    }

    return cpu_.RegistersTrace(regOutput);
}

std::vector<uint16_t> * Emulator::Next(std::vector<uint16_t> * regOutput)
{
    assert(regOutput);

    cpu_.PerformInstr();

    return cpu_.RegistersTrace(regOutput);
}

void Emulator::Dump()
{
    cpu_.Dump();
}
