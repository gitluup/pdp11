#include "memory.h"
#include <assert.h>


Memory::Memory()
{
    SetWordByAddress(0, 0012700);        //
    SetWordByAddress(2, 10);             //  mov #10, R0

    SetWordByAddress(4, 0012701);        //
    SetWordByAddress(6, 164);            //  mov #164, R1

    SetWordByAddress(8, 0111101);        //  mov [R1], R1

    SetWordByAddress(10, 005204);        //  inc R4

    SetWordByAddress(12, 0060001);       //  add R0, R1

    SetWordByAddress(164, 73);           //  number 73 is here in memory

    SetWordByAddress(14, 0020001);       //  cmp R0, R1
    SetWordByAddress(16, 1286);          //  blt  (if R0 < R1)
    SetWordByAddress(30, 005204);        //  inc R4
    SetWordByAddress(32, 005204);        //  inc R4

    // SetWordByAddress(34, 0070100);       //  mul R1, R0
    // SetWordByAddress(36, 0010102);       //  mov R1, R2
    // SetWordByAddress(38, 0070201);       //  mul R2, R1
    // SetWordByAddress(40, 0005003);       //  clr R3
    // SetWordByAddress(42, 0071204);       //  div R3, R4
}


Memory::~Memory()
{

}


uint8_t Memory::GetByteByAddress(uint16_t address)
{
    //assert(address < MEM_SIZE);

    return memory_[address];
}


void Memory::SetByteByAddress(uint16_t address, uint8_t byte)
{
    //assert(address < MEM_SIZE);

    memory_[address] = byte;
}


uint16_t Memory::GetWordByAddress(uint16_t address)
{
    //assert(address < MEM_SIZE);
    assert(address % 2 == 0);

    /*uint8_t lowByte = GetByteByAddress(address);
    uint8_t highByte = GetByteByAddress(address + 1);
    uint16_t word = (((uint16_t)lowByte) << 8) + highByte;
    return word;*/

    uint8_t lowByte = GetByteByAddress(address + 1);
    uint8_t highByte = GetByteByAddress(address);
    uint16_t word = (((uint16_t)highByte) << 8) + lowByte;
    return word;
}


void Memory::SetWordByAddress(uint16_t address, uint16_t word)
{
    //assert(address < MEM_SIZE);
    assert(address % 2 == 0);

    /*uint8_t lowByte = (uint8_t)(word >> 8);
    uint8_t highByte = (uint8_t)(word & 0x00ff);
    SetByteByAddress(address, lowByte);
    SetByteByAddress(address + 1, highByte);*/

    uint8_t highByte = (uint8_t)(word >> 8);
    uint8_t lowByte = (uint8_t)(word & 0x00ff);
    SetByteByAddress(address, highByte);
    SetByteByAddress(address + 1, lowByte);
}

