#pragma once

#include <map>
#include <stdint.h>
#include "decoder/decoder.h"
#include "instruction/instruction.h"
#include "../memory/memory.h"



class Cpu
{
    friend class SingleOperandInstr;
    friend class DoubleOperandInstr;
    friend class DoubleOperandRegInstr;
    friend class CondidtionalInstr;

public:
    Cpu(Memory* memory);
    virtual ~Cpu();

    void PerformInstr();

private:
    uint16_t FetchInstr();
    InstrInfo DecodeInstr(uint16_t instr);

    Decoder decoder;
    Memory* memory;

    uint16_t r0;
    uint16_t r1;
    uint16_t r2;
    uint16_t r3;
    uint16_t r4;
    uint16_t r5;
    uint16_t r6;
    uint16_t r7;

    bool t, n, z, v, c;
    uint8_t ipl;
    uint8_t fpsr;

    // TODO: implement cache

    std::map<InstrType, Instr*> generalInstr;
};


