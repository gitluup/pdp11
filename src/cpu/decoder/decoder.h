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
    InstrType instrType = UNKNOWN_INSTR;

    uint16_t opcode = 0;
    uint16_t mode1 = 0;
    uint16_t arg1 = 0;
    uint16_t mode2 = 0;
    uint16_t arg2 = 0;
};


class Decoder
{
public:
    Decoder();
    virtual ~Decoder();

    InstrInfo GetInstrInfo(const uint16_t rawInstr);

private:

};
