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
    uint16_t rawInstr = 1;
    while (rawInstr)
    {
        rawInstr = cpu_.PerformInstr();
    }

    // Dump();
}


void Emulator::Dump()
{
    cpu_.Dump();
}
