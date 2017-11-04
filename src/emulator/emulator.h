#pragma once

#include "../memory/memory.h"
#include "../cpu/cpu.h"


class Emulator
{
public:
    Emulator();
    virtual ~Emulator();

    void Work();

private:
    Memory memory;
    Cpu cpu;
};

