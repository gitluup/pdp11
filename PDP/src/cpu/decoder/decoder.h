#pragma once

#include <map>
#include <cstdint>
#include <cassert>


enum InstrType
{
    INSTRTYPE_SINGLE_OPERAND      = 0,
    INSTRTYPE_DOUBLE_OPERAND      = 1,
    INSTRTYPE_DOUBLE_OPERAND_REG  = 2,
    INSTRTYPE_CONDITIONAL         = 3,
    INSTRTYPE_UNKNOWN             = 4
};

struct InstrInfo
{
    InstrType instr_type = INSTRTYPE_UNKNOWN;

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

    InstrInfo GetInstrInfo(const uint16_t raw_instr);

private:

};
