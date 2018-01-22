#include <assert.h>
#include "memory.h"


Memory::Memory()
{

}


Memory::~Memory()
{

}


uint8_t Memory::GetByteByAddress(uint16_t address)
{
    assert(address < MEMORY_SIZE);

    if (address < RAM_SIZE)
    {
        return ram_[address];
    }
    else if (RAM_SIZE <= address && address < RAM_SIZE + VRAM_SIZE)
    {
        return vram_[address - RAM_SIZE];
    }
    else if (RAM_SIZE + VRAM_SIZE <= address && address < RAM_SIZE + VRAM_SIZE + ROM_SIZE)
    {
        return rom_[address - RAM_SIZE - VRAM_SIZE];
    }
    else
    {
        return io_[address - RAM_SIZE - VRAM_SIZE - ROM_SIZE];
    }
}


void Memory::SetByteByAddress(uint16_t address, uint8_t byte)
{
    assert(address < MEMORY_SIZE);

    if (address < RAM_SIZE)
    {
        ram_[address] = byte;
    }
    else if (RAM_SIZE <= address && address < RAM_SIZE + VRAM_SIZE)
    {
        vram_[address - RAM_SIZE] = byte;
    }
    else if (RAM_SIZE + VRAM_SIZE <= address && address < RAM_SIZE + VRAM_SIZE + ROM_SIZE)
    {
        rom_[address - RAM_SIZE - VRAM_SIZE] = byte;
    }
    else
    {
        io_[address - RAM_SIZE - VRAM_SIZE - ROM_SIZE] = byte;
    }
}


uint16_t Memory::GetWordByAddress(uint16_t address)
{
    assert(address < MEMORY_SIZE);
    assert(address % 2 == 0);

    /*uint8_t lowByte = GetByteByAddress(address);
    uint8_t highByte = GetByteByAddress(address + 1);
    uint16_t word = (((uint16_t)lowByte) << 8) + highByte;
    return word;*/

    uint8_t lowByte = GetByteByAddress(address + (uint16_t)1);
    uint8_t highByte = GetByteByAddress(address);
    uint16_t word = (((uint16_t)highByte) << 8) + lowByte;
    return word;
}


void Memory::SetWordByAddress(uint16_t address, uint16_t word)
{
    assert(address < MEMORY_SIZE);
    assert(address % 2 == 0);

    /*uint8_t lowByte = (uint8_t)(word >> 8);
    uint8_t highByte = (uint8_t)(word & 0x00ff);
    SetByteByAddress(address, lowByte);
    SetByteByAddress(address + 1, highByte);*/

    uint8_t highByte = (uint8_t)(word >> 8);
    uint8_t lowByte = (uint8_t)(word & 0x00ff);
    SetByteByAddress(address, highByte);
    SetByteByAddress(address + (uint16_t)1, lowByte);
}

