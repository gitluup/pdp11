#include "memory.h"
#include <assert.h>


Memory::Memory()
{
    this->SetWordByAddress(0, 0012700);        //
    this->SetWordByAddress(2, 10);             //  mov #10, R0

    this->SetWordByAddress(4, 0012701);        //
    this->SetWordByAddress(6, 164);            //  mov #164, R1

    this->SetWordByAddress(8, 0111101);        //  mov [R1], R1

    this->SetWordByAddress(10, 005204);        //  inc R4

    this->SetWordByAddress(12, 0060001);       //  add R0, R1

    this->SetWordByAddress(164, 73);           //  number 73 is here in memory

    this->SetWordByAddress(14, 0020001);       //  cmp R0, R1
    this->SetWordByAddress(16, 1286);          //  blt  (if R0 < R1)
    this->SetWordByAddress(30, 005204);        //  inc R4
    this->SetWordByAddress(32, 005204);        //  inc R4

    // this->SetWordByAddress(34, 0070100);       //  mul R1, R0
    // this->SetWordByAddress(36, 0010102);       //  mov R1, R2
    // this->SetWordByAddress(38, 0070201);       //  mul R2, R1
    // this->SetWordByAddress(40, 0005003);       //  clr R3
    // this->SetWordByAddress(42, 0071204);       //  div R3, R4
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

    /*uint8_t lowByte = this->GetByteByAddress(address);
    uint8_t highByte = this->GetByteByAddress(address + 1);
    uint16_t word = (((uint16_t)lowByte) << 8) + highByte;
    return word;*/

    uint8_t lowByte = this->GetByteByAddress(address + 1);
    uint8_t highByte = this->GetByteByAddress(address);
    uint16_t word = (((uint16_t)highByte) << 8) + lowByte;
    return word;
}


void Memory::SetWordByAddress(uint16_t address, uint16_t word)
{
    assert(address < MEM_SIZE);
    assert(address % 2 == 0);

    /*uint8_t lowByte = (uint8_t)(word >> 8);
    uint8_t highByte = (uint8_t)(word & 0x00ff);
    this->SetByteByAddress(address, lowByte);
    this->SetByteByAddress(address + 1, highByte);*/

    uint8_t highByte = (uint8_t)(word >> 8);
    uint8_t lowByte = (uint8_t)(word & 0x00ff);
    this->SetByteByAddress(address, highByte);
    this->SetByteByAddress(address + 1, lowByte);
}

