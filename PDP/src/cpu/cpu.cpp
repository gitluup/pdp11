#include "cpu.h"


Cpu::Cpu(Memory* memory)
    : decoder_(), memory_(memory), bios_(memory)
{
    registers_[R6] = RAM_SIZE - 1;  // init stack pointer
    registers_[R7] = INITIAL_PC;    // init program counter

    general_instr_[INSTRTYPE_SINGLE_OPERAND]     = new SingleOperandInstr(this);
    general_instr_[INSTRTYPE_DOUBLE_OPERAND]     = new DoubleOperandInstr(this);
    general_instr_[INSTRTYPE_DOUBLE_OPERAND_REG] = new DoubleOperandRegInstr(this);
    general_instr_[INSTRTYPE_CONDITIONAL]        = new ConditionalInstr(this);

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
    uint16_t raw_instr = FetchInstr();
    if (!raw_instr)
    {
        return raw_instr;
    }

    // decoding fetched instruction
    InstrInfo info = DecodeInstr(raw_instr);
    Instr* curr_instr = general_instr_[info.instr_type];
    curr_instr->Update(&info);
    if (info.instr_type == INSTRTYPE_UNKNOWN)
    {
        HandleInvalidOpcode();
    }

    // fetching args of decoded instruction
    curr_instr->FetchArgs();

    // execute instruction
    curr_instr->Execute();

    // save results
    curr_instr->Save();

    return raw_instr;
}


uint16_t Cpu::FetchInstr()
{
    const uint16_t raw_instr = memory_->GetWordByAddress(registers_[R7]);
    registers_[R7] += (uint16_t)WORD;

    return raw_instr;
}


InstrInfo Cpu::DecodeInstr(const uint16_t instr)
{
    assert(instr);

    InstrInfo info = decoder_.GetInstrInfo(instr);
    return info;
}

std::vector<uint16_t> * Cpu::RegistersTrace(std::vector<uint16_t> * regOutput)
{
    assert(regOutput);

    if (regOutput->size() > 0) {
        regOutput->clear();
    }

    for (size_t i = 0; i < REGISTERS_NUM; i++) {
        regOutput->push_back(registers_[i]);
    }
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
    std::cout << "Exception: Invalid opcode (#UD)\n";
    Dump();
    is_ready_ = false;
}


void Cpu::HandleUnknownError()
{
    std::cout << "??? Handling unknown error ???\n";
    Dump();
    is_ready_ = false;
}

