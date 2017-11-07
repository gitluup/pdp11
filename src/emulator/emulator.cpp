#include "emulator.h"


Emulator::Emulator()
    : memory(), cpu(&memory)
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
        rawInstr = this->cpu.PerformInstr();
    }

    this->Dump();
}


void Emulator::Dump()
{
    printf("\n------------------------------------------------\n\nRegisters:\n");
    for (int i = 0; i < 8; i++) printf("R[%d] = %6d\n", i, this->cpu.registers[i]);
    //printf("\nMemory:\n");
    //for (int i = 0; i < 40; i+=2) printf("[0x%04x]: 0x%04x\n", i, this->cpu.memory->GetWordByAddress(i));
    printf("\n------------------------------------------------\n");
}
