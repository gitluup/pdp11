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
    //uint16_t ram[8 * 1024];
    //uint16_t vram[8 * 1024];
    //uint16_t rom[8 * 1024];
    //uint16_t io[1 * 1024];
    uint8_t memory[MEM_SIZE];
};

