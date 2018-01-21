#pragma once

#include <stdint.h>
#include <vector>

#define MEM_SIZE 65536


class Memory
{
public:
    Memory();
    virtual ~Memory();

    uint8_t GetByteByAddress(uint16_t address);
    void SetByteByAddress(uint16_t address, uint8_t byte);
    uint16_t GetWordByAddress(uint16_t address);
    void SetWordByAddress(uint16_t address, uint16_t word);

private:
    uint8_t memory_[MEM_SIZE] = {};
};

