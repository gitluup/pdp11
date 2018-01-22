#include "emulator.h"


Emulator::Emulator()
    : memory_(), cpu_(&memory_)
{

}


Emulator::~Emulator()
{

}


void Emulator::Start()
{
    uint16_t raw_instr = 1;
    while (raw_instr)
    {
        raw_instr = cpu_.PerformInstr();
    }

    // Dump();
}


void Emulator::Dump()
{
    cpu_.Dump();
}
