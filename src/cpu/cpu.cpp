#include <assert.h>
#include "cpu.h"


Cpu::Cpu(Memory* memory)
    : decoder()
{
    this->memory = memory;

    InstrInfo info = {};
    this->generalInstr[SINGLE_OPERAND_INSTR]     = new SingleOperandInstr();
    this->generalInstr[DOUBLE_OPERAND_INSTR]     = new DoubleOperandInstr();
    this->generalInstr[DOUBLE_OPERAND_REG_INSTR] = new DoubleOperandRegInstr();
    this->generalInstr[CONDITIONAL_INSTR]        = new ConditionalInstr();
}

Cpu::~Cpu()
{
    std::map<InstrType, Instr*>::iterator it = this->generalInstr.begin();
    for (; it != this->generalInstr.end(); ++it)
    {
        delete it->second;
    }
}


void Cpu::PerformInstr()
{
    // fetching instruction from memory
    uint16_t rawInstr = this->FetchInstr();

    // decoding fetched instruction
    InstrInfo info = this->DecodeInstr(rawInstr);
    Instr* currInstr = this->generalInstr[info.instrType];
    currInstr->Update(info);

    // fetching args of decoded instriction
    currInstr->FetchArgs();
    // execute instruction
    currInstr->Execute();
}

uint16_t Cpu::FetchInstr()
{
    // TODO: fetching from memory
    return 0x0aaf; //inc
    //return 0x1fe9; //mov
    //return 0x73c5; //div
    //return 0x02fe; //bne
}

InstrInfo Cpu::DecodeInstr(uint16_t instr)
{
    assert(instr);

    InstrInfo info = this->decoder.GetInstrInfo(instr);
    return info;
}


