#pragma once

#include "../memory/memory.h"
#include "../cpu/cpu.h"


class Emulator
{
public:
    Emulator();
    virtual ~Emulator();

    void Start();

    void Dump();

private:
    Memory memory;
    Cpu cpu;
};

