#include <assert.h>
#include "cpu.h"

extern const int byte;
extern const int word;

Cpu::Cpu(Memory* memory)
    : decoder_(), memory_(memory)
{
    //registers[4] = 6; memory->SetWordByAddress(6, 12345);

    //InstrInfo info = {};
    general_instr_[SINGLE_OPERAND_INSTR]     = new SingleOperandInstr(this);
    general_instr_[DOUBLE_OPERAND_INSTR]     = new DoubleOperandInstr(this);
    general_instr_[DOUBLE_OPERAND_REG_INSTR] = new DoubleOperandRegInstr(this);
    general_instr_[CONDITIONAL_INSTR]        = new ConditionalInstr(this);
}

Cpu::~Cpu()
{
    std::map<InstrType, Instr*>::iterator it = general_instr_.begin();
    for (; it != general_instr_.end(); ++it)
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
    Instr* currInstr = general_instr_[info.instrType];
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
    const uint16_t rawInstr = memory_->GetWordByAddress(registers_[R7]);
    registers_[R7] += word;

    return rawInstr;
}

InstrInfo Cpu::DecodeInstr(const uint16_t instr)
{
    assert(instr);

    InstrInfo info = decoder_.GetInstrInfo(instr);
    return info;
}
