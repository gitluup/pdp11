#pragma once

#include <map>
#include <stdint.h>

#include "decoder/decoder.h"
#include "instruction/instruction.h"
#include "../memory/memory.h"
#include "bios/bios.h"

#define BYTE 1
#define WORD 2
#define INITIAL_PC 2048  //must be >= IVT_SIZE

#define REGISTERS_NUM        8
#define HIDDEN_REGISTERS_NUM 4


enum GeneralRegAdreessMode
{
    REG               = 0,
    REG_DEFERRED      = 1,
    AUTOINC           = 2,
    AUTOINC_DEFFERED  = 3,
    AUTODEC           = 4,
    AUTODEC_DEFERRED  = 5,
    INDEX             = 6,
    INDEX_DEFFERED    = 7
};

enum ProgCounterAddressMode
{
    IMMEDIATE         = 2,
    ABSOLUTE          = 3,
    RELATIVE          = 6,
    RELATIVE_DEFFERED = 7
};

enum Register
{
    R0 = 0,
    R1 = 1,
    R2 = 2,
    R3 = 3,
    R4 = 4,
    R5 = 5,
    R6 = 6,
    R7 = 7
};


class Cpu
{
    friend class Instr;
    friend class SingleOperandInstr;
    friend class DoubleOperandInstr;
    friend class DoubleOperandRegInstr;
    friend class ConditionalInstr;

public:
    explicit Cpu(Memory* memory);
    virtual ~Cpu();

    uint16_t PerformInstr();

    void Dump();


private:
    uint16_t FetchInstr();
    InstrInfo DecodeInstr(const uint16_t instr);
    void Terminate();

    Decoder decoder_;
    Memory* memory_;
    Bios bios_;

    uint16_t registers_[REGISTERS_NUM] = {};
    uint16_t hidden_registers_[HIDDEN_REGISTERS_NUM] = {};

    bool t_ = false;
    bool n_ = false;
    bool z_ = false;
    bool v_ = false;
    bool c_ = false;
    uint8_t ipl_ = 0;
    uint8_t fpsr_ = 0;
    bool is_ready_ = false;

    std::map<InstrType, Instr*> general_instr_;

    // Interrupt handlers
    void HandleDivideError();
    void HandleInvalidOpcode();
    void HandleUnknownError();
};


