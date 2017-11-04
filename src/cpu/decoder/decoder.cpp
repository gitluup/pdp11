#include "decoder.h"



Decoder::Decoder()
{

}

Decoder::~Decoder()
{

}

InstrInfo Decoder::GetInstrInfo(uint16_t rawInstr)
{
    assert(rawInstr);
    
    InstrInfo info = {};

    if ((rawInstr & 0x7800) == 0x0800)
    {
        info.instrType = SINGLE_OPERAND_INSTR;
        info.opcode = (rawInstr & 0xffc0) >> 6;
        info.mode1 = (rawInstr & 0x0038) >> 3;
        info.arg1 = (rawInstr & 0x0007);
    }
    else if ((rawInstr & 0x7800) == 0x0000)
    {
        info.instrType = CONDITIONAL_INSTR;
        info.opcode = (rawInstr & 0xff00) >> 8;
        info.arg1 = rawInstr & 0x00ff;
    }
    else if ((rawInstr & 0xf000) == 0x7000)
    {
        info.instrType = DOUBLE_OPERAND_REG_INSTR;
        info.opcode = (rawInstr & 0xfe00) >> 9;
        info.arg1 = (rawInstr & 0x01c0) >> 6;
        info.mode2 = (rawInstr & 0x0038) >> 3;
        info.arg2 = (rawInstr & 0x0007);
    }
    else
    {
        info.instrType = DOUBLE_OPERAND_INSTR;
        info.opcode = (rawInstr & 0xf000) >> 12;
        info.mode1 = (rawInstr & 0x0e00) >> 9;
        info.arg1 = (rawInstr & 0x01c0) >> 6;
        info.mode2 = (rawInstr & 0x0038) >> 3;
        info.arg2 = (rawInstr & 0x0007);
    }

    return info;
}

