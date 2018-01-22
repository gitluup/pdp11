#pragma once

#include <stdint.h>
#include <vector>

#define IVT_SIZE  1024
#define RAM_SIZE  16384
#define VRAM_SIZE 16384
#define ROM_SIZE  16384
#define IO_SIZE   16384
#define MEMORY_SIZE (RAM_SIZE + VRAM_SIZE + ROM_SIZE + IO_SIZE)

class Cpu;


class Memory
{
public:
    explicit Memory();
    virtual ~Memory();

    uint8_t GetByteByAddress(uint16_t address);
    void SetByteByAddress(uint16_t address, uint8_t byte);
    uint16_t GetWordByAddress(uint16_t address);
    void SetWordByAddress(uint16_t address, uint16_t word);

private:
    uint8_t ram_[RAM_SIZE] = {};
    uint8_t vram_[VRAM_SIZE] = {};
    uint8_t rom_[ROM_SIZE] = {};
    uint8_t io_[IO_SIZE] = {};
};

