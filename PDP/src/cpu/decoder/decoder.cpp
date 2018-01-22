#include "decoder.h"



Decoder::Decoder()
{

}

Decoder::~Decoder()
{

}

InstrInfo Decoder::GetInstrInfo(const uint16_t raw_instr)
{
    assert(raw_instr);
    
    InstrInfo info = {};

    if ((raw_instr & 0x7800u) == 0x0800u)
    {
        info.instr_type = INSTRTYPE_SINGLE_OPERAND;
        info.opcode = (raw_instr & 0xffc0u) >> 6;
        info.mode1 = (raw_instr & 0x0038u) >> 3;
        info.arg1 = (raw_instr & 0x0007u);
    }
    else if ((raw_instr & 0x7800u) == 0x0000u)
    {
        info.instr_type = INSTRTYPE_CONDITIONAL;
        info.opcode = (raw_instr & 0xff00u) >> 8;
        info.arg1 = raw_instr & 0x00ffu;
    }
    else if ((raw_instr & 0xf000u) == 0x7000u)
    {
        info.instr_type = INSTRTYPE_DOUBLE_OPERAND_REG;
        info.opcode = (raw_instr & 0xfe00u) >> 9;
        info.arg1 = (raw_instr & 0x01c0u) >> 6;
        info.mode2 = (raw_instr & 0x0038u) >> 3;
        info.arg2 = (raw_instr & 0x0007u);
    }
    else
    {
        info.instr_type = INSTRTYPE_DOUBLE_OPERAND;
        info.opcode = (raw_instr & 0xf000u) >> 12;
        info.mode1 = (raw_instr & 0x0e00u) >> 9;
        info.arg1 = (raw_instr & 0x01c0u) >> 6;
        info.mode2 = (raw_instr & 0x0038u) >> 3;
        info.arg2 = (raw_instr & 0x0007u);
    }

    return info;
}

