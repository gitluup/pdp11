#include "decoder.h"



Decoder::Decoder()
{

}

Decoder::~Decoder()
{

}

InstrInfo Decoder::GetInstrInfo(const uint16_t rawInstr)
{
    assert(rawInstr);
    
    InstrInfo info = {};

    if ((rawInstr & 0x7800u) == 0x0800u)
    {
        info.instrType = SINGLE_OPERAND_INSTR;
        info.opcode = (rawInstr & 0xffc0u) >> 6;
        info.mode1 = (rawInstr & 0x0038u) >> 3;
        info.arg1 = (rawInstr & 0x0007u);
    }
    else if ((rawInstr & 0x7800u) == 0x0000u)
    {
        info.instrType = CONDITIONAL_INSTR;
        info.opcode = (rawInstr & 0xff00u) >> 8;
        info.arg1 = rawInstr & 0x00ffu;
    }
    else if ((rawInstr & 0xf000u) == 0x7000u)
    {
        info.instrType = DOUBLE_OPERAND_REG_INSTR;
        info.opcode = (rawInstr & 0xfe00u) >> 9;
        info.arg1 = (rawInstr & 0x01c0u) >> 6;
        info.mode2 = (rawInstr & 0x0038u) >> 3;
        info.arg2 = (rawInstr & 0x0007u);
    }
    else
    {
        info.instrType = DOUBLE_OPERAND_INSTR;
        info.opcode = (rawInstr & 0xf000u) >> 12;
        info.mode1 = (rawInstr & 0x0e00u) >> 9;
        info.arg1 = (rawInstr & 0x01c0u) >> 6;
        info.mode2 = (rawInstr & 0x0038u) >> 3;
        info.arg2 = (rawInstr & 0x0007u);
    }

    return info;
}

