#include <assert.h>
#include "cpu.h"

extern const int byte;
extern const int word;


Cpu::Cpu(Memory* memory)
    : decoder(), memory(memory)
{
    //registers[4] = 6; memory->SetWordByAddress(6, 12345);

    InstrInfo info = {};
    this->generalInstr[SINGLE_OPERAND_INSTR]     = new SingleOperandInstr(this);
    this->generalInstr[DOUBLE_OPERAND_INSTR]     = new DoubleOperandInstr(this);
    this->generalInstr[DOUBLE_OPERAND_REG_INSTR] = new DoubleOperandRegInstr(this);
    this->generalInstr[CONDITIONAL_INSTR]        = new ConditionalInstr(this);
}

Cpu::~Cpu()
{
    std::map<InstrType, Instr*>::iterator it = this->generalInstr.begin();
    for (; it != this->generalInstr.end(); ++it)
    {
        delete it->second;
    }
}


uint16_t Cpu::PerformInstr()
{
    // fetching instruction from memory
    uint16_t rawInstr = this->FetchInstr();
    if (!rawInstr)
    {
        return rawInstr;
    }

    // decoding fetched instruction
    InstrInfo info = this->DecodeInstr(rawInstr);
    Instr* currInstr = this->generalInstr[info.instrType];
    currInstr->Update(info);

    // fetching args of decoded instriction
    currInstr->FetchArgs();
    // execute instruction
    currInstr->Execute();
    // save results
    currInstr->Save();

    return rawInstr;
}

uint16_t Cpu::FetchInstr()
{
    const uint16_t rawInstr = this->memory->GetWordByAddress(this->registers[R7]);
    this->registers[R7] += word;

    return rawInstr;
}

InstrInfo Cpu::DecodeInstr(const uint16_t instr)
{
    assert(instr);

    InstrInfo info = this->decoder.GetInstrInfo(instr);
    return info;
}


