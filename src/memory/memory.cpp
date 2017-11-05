#include "memory.h"
#include <assert.h>


Memory::Memory()
{
    memory[2] = 22;
    memory[3] = 33;
}


Memory::~Memory()
{

}


uint8_t Memory::GetByteByAddress(uint16_t address)
{
    assert(address < MEM_SIZE);

    return this->memory[address];
}


void Memory::SetByteByAddress(uint16_t address, uint8_t byte)
{
    assert(address < MEM_SIZE);

    this->memory[address] = byte;
}


uint16_t Memory::GetWordByAddress(uint16_t address)
{
    assert(address < MEM_SIZE);
    assert(address % 2 == 0);

    uint8_t lowByte = this->GetByteByAddress(address);
    uint8_t highByte = this->GetByteByAddress(address + 1);
    uint16_t word = (((uint16_t)lowByte) << 8) + highByte;
    return word;
}


void Memory::SetWordByAddress(uint16_t address, uint16_t word)
{
    assert(address < MEM_SIZE);
    assert(address % 2 == 0);

    uint8_t lowByte = (uint8_t)(word >> 8);
    uint8_t highByte = (uint8_t)(word & 0x00ff);
    this->SetByteByAddress(address, lowByte);
    this->SetByteByAddress(address + 1, highByte);
}

