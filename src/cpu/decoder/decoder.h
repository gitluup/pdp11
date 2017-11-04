#pragma once

#include <map>
#include <stdint.h>
#include <assert.h>


enum InstrType
{
    SINGLE_OPERAND_INSTR,
    DOUBLE_OPERAND_INSTR,
    DOUBLE_OPERAND_REG_INSTR,
    CONDITIONAL_INSTR,
    UNKNOWN_INSTR
};

class InstrInfo
{
public:
    InstrType instrType;

    uint16_t opcode;
    uint16_t mode1;
    uint16_t arg1;
    uint16_t mode2;
    uint16_t arg2;
};


class Decoder
{
public:
    Decoder();
    virtual ~Decoder();

    InstrInfo GetInstrInfo(uint16_t rawInstr);

private:

};
