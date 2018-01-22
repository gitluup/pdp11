#include <iostream>
#include "cpu.h"


Cpu::Cpu(Memory* memory)
    : decoder_(), memory_(memory), bios_(memory)
{
    registers_[R6] = RAM_SIZE - 1;  // init stack pointer
    registers_[R7] = INITIAL_PC;    // init program counter

    general_instr_[SINGLE_OPERAND_INSTR]     = new SingleOperandInstr(this);
    general_instr_[DOUBLE_OPERAND_INSTR]     = new DoubleOperandInstr(this);
    general_instr_[DOUBLE_OPERAND_REG_INSTR] = new DoubleOperandRegInstr(this);
    general_instr_[CONDITIONAL_INSTR]        = new ConditionalInstr(this);

    bios_.Run();

    is_ready_ = true;
}


Cpu::~Cpu()
{
    std::map<InstrType, Instr*>::iterator it = general_instr_.begin();
    for (; it != general_instr_.end(); ++it)
    {
        delete it->second;
    }
}


void Cpu::Dump()
{
    std::cout << "************* CPU DUMP *************\n";

    for (int i = 0; i < REGISTERS_NUM; i++)
    {
        std::cout << "R" << i << ": " << registers_[i] << "\n";
    }

    std::cout << "************************************" << std::endl;
}


uint16_t Cpu::PerformInstr()
{
    if (!is_ready_)
    {
        return 0;
    }

    // fetching instruction from memory
    uint16_t rawInstr = this->FetchInstr();
    if (!rawInstr)
    {
        return rawInstr;
    }

    // decoding fetched instruction
    InstrInfo info = DecodeInstr(rawInstr);
    Instr* currInstr = general_instr_[info.instrType];
    currInstr->Update(&info);
    if (info.instrType == UNKNOWN_INSTR)
    {
        HandleInvalidOpcode();
    }

    // fetching args of decoded instruction
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
    registers_[R7] += (uint16_t)WORD;

    return rawInstr;
}


InstrInfo Cpu::DecodeInstr(const uint16_t instr)
{
    assert(instr);

    InstrInfo info = decoder_.GetInstrInfo(instr);
    return info;
}


void Cpu::Terminate()
{
    is_ready_ = false;
}


void Cpu::HandleDivideError()
{
    std::cout << "Exception: Divide by zero (#DE)\n";
    Dump();
    is_ready_ = false;
}


void Cpu::HandleInvalidOpcode()
{
    std::cout << "Handling invalid opcode (#UD)\n";
    Dump();
    is_ready_ = false;
}


void Cpu::HandleUnknownError()
{
    std::cout << "Handling unknown error \n";
    Dump();
    is_ready_ = false;
}

