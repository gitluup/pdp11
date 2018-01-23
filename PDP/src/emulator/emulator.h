#pragma once

#include "../memory/memory.h"
#include "../cpu/cpu.h"


class Emulator
{
public:
    explicit Emulator();
    virtual ~Emulator();

    std::vector<uint16_t> * Start(std::vector<uint16_t> * regOutput);

    std::vector<uint16_t> * Next(std::vector<uint16_t> * regOutput);

    void GetRegistersState(std::vector<uint16_t> * regOutput);
    void GetMemoryBatch(std::vector<uint16_t> * memoryBatch,
                        size_t address,
                        size_t batchSize);

    void Dump();

private:
    Memory memory_;
    Cpu cpu_;
};
