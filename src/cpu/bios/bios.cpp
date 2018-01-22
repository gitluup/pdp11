#include "bios.h"
#include "../cpu.h"


Bios::Bios(Memory* memory)
{
    memory_ = memory;
}


Bios::~Bios()
{

}


void Bios::Run()
{
    // reading from ROM should be here

    memory_->SetWordByAddress(INITIAL_PC + 0, 0012700);        //
    memory_->SetWordByAddress(INITIAL_PC + 2, 10);             //  mov #10, R0

    memory_->SetWordByAddress(INITIAL_PC + 4, 0012701);        //
    memory_->SetWordByAddress(INITIAL_PC + 6, 164);            //  mov #164, R1

    memory_->SetWordByAddress(INITIAL_PC + 8, 0111101);        //  mov [R1], R1

    memory_->SetWordByAddress(INITIAL_PC + 10, 005204);        //  inc R4

    memory_->SetWordByAddress(INITIAL_PC + 12, 0060001);       //  add R0, R1

    memory_->SetWordByAddress(INITIAL_PC + 164, 73);           //  number 73 is here in memory

    memory_->SetWordByAddress(INITIAL_PC + 14, 0020001);       //  cmp R0, R1
    memory_->SetWordByAddress(INITIAL_PC + 16, 1286);          //  blt  (if R0 < R1)

    memory_->SetWordByAddress(INITIAL_PC + 18, 005204);        //  inc R4
    memory_->SetWordByAddress(INITIAL_PC + 20, 005204);        //  inc R4

    // memory_->SetWordByAddress(INITIAL_PC + 22, 0070100);       //  mul R1, R0
    // memory_->SetWordByAddress(INITIAL_PC + 24, 0010102);       //  mov R1, R2
    // memory_->SetWordByAddress(INITIAL_PC + 26, 0070201);       //  mul R2, R1
    // memory_->SetWordByAddress(INITIAL_PC + 28, 0005003);       //  clr R3
    // memory_->SetWordByAddress(INITIAL_PC + 30, 0071204);       //  div R3, R4

    // memory_->SetWordByAddress(INITIAL_PC + 22, 1);  // generating #UD exception
}

