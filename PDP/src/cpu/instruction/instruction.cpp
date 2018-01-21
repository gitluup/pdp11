#include <iostream>
#include "instruction.h"
#include "../cpu.h"

extern const uint16_t byte = 1;
extern const uint16_t word = 2;


Instr::Instr(Cpu* cpu)
    : cpu_(cpu)
{

}


Instr::~Instr()
{

}


uint16_t Instr::FetchOperandGeneralReg(const uint16_t mode, const uint16_t regNumber)
{
    assert(regNumber <= 5);

    Memory* const memory = cpu_->memory_;
    uint16_t* const registers = cpu_->registers_;

    const uint16_t argSize = (opcode_ & 0x0010) ? word : byte;
    uint16_t arg = 0;

    switch (mode)
    {
        case REG:
            arg = registers[regNumber];
            break;
        case REG_DEFERRED:
            arg = memory->GetWordByAddress(registers[regNumber]);
            break;
        case AUTOINC:
            arg = memory->GetWordByAddress(registers[regNumber]);
            cpu_->registers_[regNumber] += argSize;
            break;
        case AUTOINC_DEFFERED:
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[regNumber]));
            cpu_->registers_[regNumber] += word;
            break;
        case AUTODEC:
            registers[regNumber] -= argSize;
            arg = memory->GetWordByAddress(registers[regNumber]);
            break;
        case AUTODEC_DEFERRED:
            registers[regNumber] -= word;
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[regNumber]));
            break;
        case INDEX:
            registers[R7] += word;
            arg = memory->GetWordByAddress(registers[regNumber] + memory->GetWordByAddress(registers[R7]));
            break;
        case INDEX_DEFFERED:
            cpu_->registers_[R7] += word;
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[regNumber] + memory->GetWordByAddress(registers[R7])));
            break;

        default: assert(0); //incorrect mode
    }

    return arg;
}


uint16_t Instr::FetchOperandStackPointer(const uint16_t mode)
{
    Memory* const memory = cpu_->memory_;
    uint16_t* const registers = cpu_->registers_;

    uint16_t arg = 0;

    switch (mode)
    {
        case REG_DEFERRED:
            arg = memory->GetWordByAddress(registers[R6]);
            break;
        case AUTOINC:
            arg = memory->GetWordByAddress(registers[R6]);
            cpu_->registers_[R6] += word;
            break;
        case AUTOINC_DEFFERED:
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[R6]));
            cpu_->registers_[R6] += word;
            break;
        case AUTODEC:
            registers[R6] -= word;
            arg = memory->GetWordByAddress(registers[R6]);
            break;
        case INDEX:
            cpu_->registers_[R7] += word;
            arg = memory->GetWordByAddress(registers[R6] + memory->GetWordByAddress(registers[R7]));
            break;
        case INDEX_DEFFERED:
            cpu_->registers_[R7] += word;
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[R6] + memory->GetWordByAddress(registers[R7])));
            break;

        default: assert(0); //incorrect mode for stack pointer (R6)
    }

    return arg;
}


uint16_t Instr::FetchOperandProgramCounter(const uint16_t mode)
{
    Memory* const memory = cpu_->memory_;
    uint16_t* const registers = cpu_->registers_;

    const uint16_t wordPointedByR7 = memory->GetWordByAddress(registers[R7]);
    const uint16_t argAddress = registers[R7] + word + wordPointedByR7;
    uint16_t arg = 0;

    switch (mode)
    {
        case IMMEDIATE:
            arg = wordPointedByR7;
            break;
        case ABSOLUTE:
            arg = memory->GetWordByAddress(wordPointedByR7);
            break;
        case RELATIVE:
            arg = memory->GetWordByAddress(argAddress);
            break;
        case RELATIVE_DEFFERED:
            arg = memory->GetWordByAddress(memory->GetWordByAddress(argAddress));
            break;

        default: assert(0); //incorrect mode for process counter (R7)
    }

    cpu_->registers_[R7] += word;

    return arg;
}


void Instr::SaveResultGeneralReg(const uint16_t mode, const uint16_t regNumber, const uint16_t result)
{
    assert(regNumber <= 5);

    Memory* const memory = cpu_->memory_;
    uint16_t* const registers = cpu_->registers_;

    const uint16_t argSize = (opcode_ & 0x0010) ? word : byte;

    switch (mode)
    {
        case REG:
            registers[regNumber] = result;
            break;
        case REG_DEFERRED:
            memory->SetWordByAddress(registers[regNumber], result);
            break;
        case AUTOINC:
            memory->SetWordByAddress(registers[regNumber] - argSize, result);
            break;
        case AUTOINC_DEFFERED:
            memory->SetWordByAddress(memory->GetWordByAddress(registers[regNumber] - word), result);
            break;
        case AUTODEC:
            memory->SetWordByAddress(registers[regNumber] + argSize, result);
            break;
        case AUTODEC_DEFERRED:
            memory->SetWordByAddress(memory->GetWordByAddress(registers[regNumber] - word), result);
            break;
        case INDEX:
            memory->SetWordByAddress(registers[regNumber] + memory->GetWordByAddress(registers[R7] - word), result);
            break;
        case INDEX_DEFFERED:
            memory->SetWordByAddress(memory->GetWordByAddress(registers[regNumber] + memory->GetWordByAddress(registers[R7] - word)), result);
            break;

        default: assert(0); //incorrect mode
    }
}


void Instr::SaveResultStackPointer(const uint16_t mode, const uint16_t result)
{
    Memory* const memory = cpu_->memory_;
    uint16_t* const registers = cpu_->registers_;

    switch (mode)
    {
        case REG_DEFERRED:
            memory->SetWordByAddress(registers[R6], result);
            break;
        case AUTOINC:
            memory->SetWordByAddress(registers[R6] - word, result);
            break;
        case AUTOINC_DEFFERED:
            memory->SetWordByAddress(memory->GetWordByAddress(registers[R6] - word), result);
            break;
        case AUTODEC:
            memory->SetWordByAddress(registers[R6] - word, result);
            break;
        case INDEX:
            memory->SetWordByAddress(registers[R6] + memory->GetWordByAddress(registers[R7] - word), result);
            break;
        case INDEX_DEFFERED:
            memory->SetWordByAddress(memory->GetWordByAddress(registers[R6] + memory->GetWordByAddress(registers[R7] - word)), result);
            break;

        default: assert(0); //incorrect mode for stack pointer (R6)
    }
}


void Instr::SaveResultProgramCounter(const uint16_t mode, const uint16_t result)
{
    Memory* const memory = cpu_->memory_;
    uint16_t* const registers = cpu_->registers_;

    switch (mode)
    {
        case IMMEDIATE:
            memory->SetWordByAddress(registers[R7] - word, result);
            break;
        case ABSOLUTE:
            memory->SetWordByAddress(memory->GetWordByAddress(registers[R7] - word), result);
            break;
        case RELATIVE:
            memory->SetWordByAddress(registers[R7] + memory->GetWordByAddress(registers[R7] - word), result);
            break;
        case RELATIVE_DEFFERED:
            memory->SetWordByAddress(memory->GetWordByAddress(registers[R7] + memory->GetWordByAddress(registers[R7] - word)), result);
            break;

        default: assert(0); //incorrect mode for process counter (R7)
    }
}


SingleOperandInstr::SingleOperandInstr(Cpu* cpu) : Instr(cpu)
{
    instr_executors_[00003] = &SingleOperandInstr::Swab;
    instr_executors_[00040] = &SingleOperandInstr::Jsr;
    instr_executors_[01040] = &SingleOperandInstr::Emt;
    instr_executors_[00050] = &SingleOperandInstr::Clr;
    instr_executors_[01050] = &SingleOperandInstr::Clrb;
    instr_executors_[00051] = &SingleOperandInstr::Com;
    instr_executors_[01051] = &SingleOperandInstr::Comb;
    instr_executors_[00052] = &SingleOperandInstr::Inc;
    instr_executors_[01052] = &SingleOperandInstr::Incb;
    instr_executors_[00053] = &SingleOperandInstr::Dec;
    instr_executors_[01053] = &SingleOperandInstr::Decb;
    instr_executors_[00054] = &SingleOperandInstr::Neg;
    instr_executors_[01054] = &SingleOperandInstr::Negb;
    instr_executors_[00055] = &SingleOperandInstr::Adc;
    instr_executors_[01055] = &SingleOperandInstr::Adcb;
    instr_executors_[00056] = &SingleOperandInstr::Sbc;
    instr_executors_[01056] = &SingleOperandInstr::Sbcb;
    instr_executors_[00057] = &SingleOperandInstr::Tst;
    instr_executors_[01057] = &SingleOperandInstr::Tstb;
}


SingleOperandInstr::~SingleOperandInstr()
{

}


void SingleOperandInstr::Update(const InstrInfo newInfo)
{
    assert(newInfo.instrType == SINGLE_OPERAND_INSTR);
    assert(newInfo.opcode && !newInfo.mode2 && !newInfo.arg2);

    opcode_ = newInfo.opcode;
    mode_ = newInfo.mode1;
    reg_ = newInfo.arg1;
}


void SingleOperandInstr::FetchArgs()
{
    uint16_t arg = 0;

    if (reg_ == R7)
    {
        arg = FetchOperandProgramCounter(mode_);
    }
    else if (reg_ == R6)
    {
        arg = FetchOperandStackPointer(mode_);
    }
    else
    {
        arg = FetchOperandGeneralReg(mode_, reg_);
    }

    cpu_->hidden_registers_[0] = arg;
}


void SingleOperandInstr::Execute()
{
    SingleOperandInstrExecutor executor = instr_executors_[opcode_];
    assert(executor);
    (this->*executor)();
}


void SingleOperandInstr::Save()
{
    const uint16_t result = cpu_->hidden_registers_[0];

    if (reg_ == R7)
    {
        SaveResultProgramCounter(mode_, result);
    }
    else if (reg_ == R6)
    {
        SaveResultStackPointer(mode_, result);
    }
    else
    {
        SaveResultGeneralReg(mode_, reg_, result);
    }
}



DoubleOperandInstr::DoubleOperandInstr(Cpu* cpu) : Instr(cpu)
{
    instr_executors_[001] = &DoubleOperandInstr::Mov;
    instr_executors_[011] = &DoubleOperandInstr::Movb;
    instr_executors_[002] = &DoubleOperandInstr::Cmp;
    instr_executors_[012] = &DoubleOperandInstr::Cmpb;
    instr_executors_[006] = &DoubleOperandInstr::Add;
    instr_executors_[016] = &DoubleOperandInstr::Sub;
}


DoubleOperandInstr::~DoubleOperandInstr()
{

}


void DoubleOperandInstr::Update(InstrInfo newInfo)
{
    assert(newInfo.instrType == DOUBLE_OPERAND_INSTR);
    assert(newInfo.opcode);

    opcode_ = newInfo.opcode;
    src_mode_ = newInfo.mode1;
    src_ = newInfo.arg1;
    dest_mode_ = newInfo.mode2;
    dest_ = newInfo.arg2;
}


void DoubleOperandInstr::FetchArgs()
{
    uint16_t src = 0;
    uint16_t dest = 0;

    if (src_ == R7)
    {
        src = FetchOperandProgramCounter(src_mode_);
    }
    else if (src_ == R6)
    {
        src = FetchOperandStackPointer(src_mode_);
    }
    else
    {
        src = FetchOperandGeneralReg(src_mode_, src_);
    }

    if (dest_ == R7)
    {
        dest = FetchOperandProgramCounter(dest_mode_);
    }
    else if (dest_ == R6)
    {
        dest = FetchOperandStackPointer(dest_mode_);
    }
    else
    {
        dest = FetchOperandGeneralReg(dest_mode_, dest_);
    }

    cpu_->hidden_registers_[0] = src;
    cpu_->hidden_registers_[1] = dest;
}


void DoubleOperandInstr::Execute()
{
    DoubleOperandInstrExecutor executor = instr_executors_[opcode_];
    assert(executor);
    (this->*executor)();
}


void DoubleOperandInstr::Save()
{
    const uint16_t srcResult = cpu_->hidden_registers_[0];
    const uint16_t destResult = cpu_->hidden_registers_[1];

    if (src_ == R7)
    {
        SaveResultProgramCounter(src_mode_, srcResult);
    }
    else if (src_ == R6)
    {
        SaveResultStackPointer(src_mode_, srcResult);
    }
    else
    {
        SaveResultGeneralReg(src_mode_, src_, srcResult);
    }

    if (dest_ == R7)
    {
        SaveResultProgramCounter(dest_mode_, destResult);
    }
    else if (dest_ == R6)
    {
        SaveResultStackPointer(dest_mode_, destResult);
    }
    else
    {
        SaveResultGeneralReg(dest_mode_, dest_, destResult);
    }
}



DoubleOperandRegInstr::DoubleOperandRegInstr(Cpu* cpu) : Instr(cpu)
{
    instr_executors_[0070] = &DoubleOperandRegInstr::Mul;
    instr_executors_[0071] = &DoubleOperandRegInstr::Div;
    // other instructions ...
}


DoubleOperandRegInstr::~DoubleOperandRegInstr()
{

}


void DoubleOperandRegInstr::Update(const InstrInfo newInfo)
{
    assert(newInfo.instrType == DOUBLE_OPERAND_REG_INSTR);
    assert(newInfo.opcode && !newInfo.mode1);

    opcode_ = newInfo.opcode;
    reg_ = newInfo.arg1;
    arg_mode_ = newInfo.mode2;
    arg_ = newInfo.arg2;
}


void DoubleOperandRegInstr::FetchArgs()
{
    uint16_t arg = 0;

    if (arg_ == R7)
    {
        arg = FetchOperandProgramCounter(arg_mode_);
    }
    else if (arg_ == R6)
    {
        arg = FetchOperandStackPointer(arg_mode_);
    }
    else
    {
        arg = FetchOperandGeneralReg(arg_mode_, arg_);
    }

    //cpu_->hidden_registers_[0] = cpu_->registers[this->reg];
    cpu_->hidden_registers_[0] = arg;
}


void DoubleOperandRegInstr::Execute()
{
    DoubleOperandRegInstrExecutor executor = instr_executors_[opcode_];
    assert(executor);
    (this->*executor)();
}


void DoubleOperandRegInstr::Save()
{
    /*cpu_->registers[this->reg] = cpu_->hidden_registers_[0];
    const uint16_t result = cpu_->hidden_registers_[1];

    if (this->arg == R7)
    {
        this->SaveResultProgramCounter(this->argMode, result);
    }
    else if (this->arg == R6)
    {
        this->SaveResultStackPointer(this->argMode, result);
    }
    else
    {
        this->SaveResultGeneralReg(this->argMode, this->arg, result);
    }*/
}


ConditionalInstr::ConditionalInstr(Cpu* cpu) : Instr(cpu)
{
    instr_executors_[01] = &ConditionalInstr::Br;
    instr_executors_[02] = &ConditionalInstr::Bne;
    instr_executors_[03] = &ConditionalInstr::Beq;
    instr_executors_[04] = &ConditionalInstr::Bge;
    instr_executors_[05] = &ConditionalInstr::Blt;
    instr_executors_[06] = &ConditionalInstr::Bgt;
    instr_executors_[07] = &ConditionalInstr::Ble;

    instr_executors_[0200] = &ConditionalInstr::Bpl;
    instr_executors_[0201] = &ConditionalInstr::Bmi;
    instr_executors_[0202] = &ConditionalInstr::Bhi;
    instr_executors_[0203] = &ConditionalInstr::Blos;
    instr_executors_[0204] = &ConditionalInstr::Bvc;
    instr_executors_[0205] = &ConditionalInstr::Bvs;
    instr_executors_[0206] = &ConditionalInstr::Bcc;
    instr_executors_[0207] = &ConditionalInstr::Bcs;
}


ConditionalInstr::~ConditionalInstr()
{

}


void ConditionalInstr::Update(InstrInfo newInfo)
{
    assert(newInfo.instrType == CONDITIONAL_INSTR);
    assert(!newInfo.mode1 && !newInfo.mode2 && !newInfo.arg2);

    opcode_ = newInfo.opcode;
    offset_ = newInfo.arg1;
}


void ConditionalInstr::FetchArgs()
{
    cpu_->hidden_registers_[0] = offset_;
}


void ConditionalInstr::Execute()
{
    ConditionalInstrExecutor executor = instr_executors_[opcode_];
    assert(executor);
    (this->*executor)();
}


void ConditionalInstr::Save()
{
    // nothing should be done here
}




// Implementation of single operand intructions
void SingleOperandInstr::Swab()
{
    assert(0); //not implemented
}

void SingleOperandInstr::Jsr()
{
    assert(0); //not implemented
}

void SingleOperandInstr::Emt()
{
    assert(0); //not implemented
}

void SingleOperandInstr::Clr()
{
    cpu_->hidden_registers_[0] = 0;

    cpu_->n_ = false;
    cpu_->z_ = true;
    cpu_->v_ = false;
    cpu_->c_ = false;
}

void SingleOperandInstr::Clrb()
{
    cpu_->hidden_registers_[0] &= 0xff00u;

    cpu_->n_ = false;
    cpu_->z_ = true;
    cpu_->v_ = false;
    cpu_->c_ = false;
}

void SingleOperandInstr::Com()
{
    cpu_->hidden_registers_[0] = ~(cpu_->hidden_registers_[0]);

    cpu_->n_ = bool(cpu_->hidden_registers_[0] & 0x8000u);
    cpu_->z_ = bool(cpu_->hidden_registers_[0]);
}

void SingleOperandInstr::Comb()
{
    const uint16_t mask = 0xff00u + (0x00ffu & (~cpu_->hidden_registers_[0]));
    cpu_->hidden_registers_[0] &= mask;

    cpu_->n_ = bool(cpu_->hidden_registers_[0] & 0x0080u);
    cpu_->z_ = bool(cpu_->hidden_registers_[0] & 0x00ffu);
}

void SingleOperandInstr::Inc()
{
    cpu_->hidden_registers_[0] += 1u;

    cpu_->n_ = bool(cpu_->hidden_registers_[0] & 0x8000u);
    cpu_->z_ = bool(cpu_->hidden_registers_[0] == 0);
    cpu_->v_ = bool(cpu_->hidden_registers_[0] - 1u == 077777u);
}

void SingleOperandInstr::Incb()
{
    uint8_t lowByte = 0x00ffu & cpu_->hidden_registers_[0];
    lowByte += 1u;
    cpu_->hidden_registers_[0] &= 0xff00u;
    cpu_->hidden_registers_[0] += lowByte;

    cpu_->n_ = bool(lowByte & 0x80u);
    cpu_->z_ = bool(lowByte == 0);
    cpu_->v_ = bool((lowByte - 1u) == 127u);
}

void SingleOperandInstr::Dec()
{
    cpu_->hidden_registers_[0] -= 1u;

    cpu_->n_ = bool(cpu_->hidden_registers_[0] & 0x8000);
    cpu_->z_ = bool(cpu_->hidden_registers_[0] == 0);
    cpu_->v_ = bool(cpu_->hidden_registers_[0] + 1u == 0100000u);
}

void SingleOperandInstr::Decb()
{
    uint8_t lowByte = 0x00ffu & cpu_->hidden_registers_[0];
    lowByte -= 1u;
    cpu_->hidden_registers_[0] &= 0xff00u;
    cpu_->hidden_registers_[0] += lowByte;

    cpu_->n_ = bool(lowByte & 0x80u);
    cpu_->z_ = bool(lowByte == 0);
    cpu_->v_ = bool((lowByte + 1u) == 128u);
}

void SingleOperandInstr::Neg()
{
    cpu_->hidden_registers_[0] = ~(cpu_->hidden_registers_[0]) + 1u;

    cpu_->n_ = bool(cpu_->hidden_registers_[0] & 0x8000);
    cpu_->z_ = bool(cpu_->hidden_registers_[0] == 0);
    cpu_->v_ = bool(cpu_->hidden_registers_[0] == 0100000u);
    cpu_->c_ = !(cpu_->z_);
}

void SingleOperandInstr::Negb()
{
    uint8_t lowByte = 0x00ffu & cpu_->hidden_registers_[0];
    lowByte = ~lowByte + 1u;
    cpu_->hidden_registers_[0] &= 0xff00u;
    cpu_->hidden_registers_[0] += lowByte;

    cpu_->n_ = bool(lowByte & 0x80u);
    cpu_->z_ = bool(lowByte == 0);
    cpu_->v_ = bool(lowByte == 128u);
    cpu_->c_ = !(cpu_->z_);
}

void SingleOperandInstr::Adc()
{
    assert(0); //not implemented
}

void SingleOperandInstr::Adcb()
{
    assert(0); //not implemented
}

void SingleOperandInstr::Sbc()
{
    assert(0); //not implemented
}

void SingleOperandInstr::Sbcb()
{
    assert(0); //not implemented
}

void SingleOperandInstr::Tst()
{
    cpu_->n_ = bool(cpu_->hidden_registers_[0] & 0x8000u);
    cpu_->z_ = bool(cpu_->hidden_registers_[0] == 0);
    cpu_->v_ = false;
    cpu_->c_ = false;
}

void SingleOperandInstr::Tstb()
{
    cpu_->n_ = bool(cpu_->hidden_registers_[0] & 0x0080u);
    cpu_->z_ = bool((0x00ffu & cpu_->hidden_registers_[0]) == 0);
    cpu_->v_ = false;
    cpu_->c_ = false;
}




// Implementation of double operand intructions
void DoubleOperandInstr::Mov()
{
    //printf("MOV   opcode = %o  mode1 = %d  arg1 = %d  mode2 = %d  arg2 = %d\n", opcode, srcMode, src, destMode, dest);
    cpu_->hidden_registers_[1] = cpu_->hidden_registers_[0];

    cpu_->n_ = bool(cpu_->hidden_registers_[0] & 0x8000u);
    cpu_->z_ = bool(cpu_->hidden_registers_[0] == 0);
    cpu_->v_ = false;
}


void DoubleOperandInstr::Movb()
{
    const uint8_t lowByte = (cpu_->hidden_registers_[0] & 0x00ffu);
    cpu_->hidden_registers_[1] &= 0xff00u;
    cpu_->hidden_registers_[1] += lowByte;

    cpu_->n_ = bool(lowByte & 0x80u);
    cpu_->z_ = bool(lowByte == 0);
    cpu_->v_ = false;

    if (dest_mode_ == REG)
    {
        const bool sign = cpu_->hidden_registers_[1] & 0x0080u;
        if (sign)
        {
            cpu_->hidden_registers_[1] = 0xff00u + lowByte;
        }
        else
        {
            cpu_->hidden_registers_[1] &= 0x00ffu;
        }
    }

}


void DoubleOperandInstr::Cmp()
{
    const uint16_t src = cpu_->hidden_registers_[0];
    const uint16_t dest = cpu_->hidden_registers_[1];
    const uint32_t result = src + ~(dest) + 1u;

    cpu_->n_ = bool(result & 0x8000u);
    cpu_->z_ = bool((result & 0xffffu) == 0);
    cpu_->v_ = bool((((src & 0x8000u) ^ (dest & 0x8000u))) && ((dest & 0x8000u) == (result & 0x8000)));
    cpu_->c_ = bool(!(result & 0x10000));
}


void DoubleOperandInstr::Cmpb()
{
    const uint8_t src = 0x00ff & cpu_->hidden_registers_[0];
    const uint8_t dest = 0x00ff & cpu_->hidden_registers_[1];
    const uint16_t result = src + ~(dest) + 1u;

    cpu_->n_ = bool(result & 0x80u);
    cpu_->z_ = bool((result & 0xffu) == 0);
    cpu_->v_ = bool((((src & 0x80u) ^ (dest & 0x80u))) && ((dest & 0x80u) == (result & 0x80)));
    cpu_->c_ = bool(!(result & 0x100));
}


void DoubleOperandInstr::Add()
{
    const uint16_t src = cpu_->hidden_registers_[0];
    const uint16_t dest = cpu_->hidden_registers_[1];
    const uint32_t result = src + dest;
    cpu_->hidden_registers_[1] = result;

    cpu_->n_ = bool(result & 0x8000u);
    cpu_->z_ = bool((result & 0xffffu) == 0);
    cpu_->v_ = bool((!((src & 0x8000u) ^ (dest & 0x8000u))) && ((dest & 0x8000u) != (result & 0x8000)));
    cpu_->c_ = bool(result & 0x10000);
}


void DoubleOperandInstr::Sub()
{
    const uint16_t src = cpu_->hidden_registers_[0];
    const uint16_t dest = cpu_->hidden_registers_[1];
    const uint32_t result = src + ~(dest) + 1u;

    cpu_->n_ = bool(result & 0x8000u);
    cpu_->z_ = bool((result & 0xffffu) == 0);
    cpu_->v_ = bool((((src & 0x8000u) ^ (dest & 0x8000u))) && ((src & 0x8000u) == (result & 0x8000u)));
    cpu_->c_ = bool(!(result & 0x10000u));
}



// Implementation of double operand intructions (register source operand)
void DoubleOperandRegInstr::Mul()
{
    assert(reg_ <= R4); //can't use R6 and R7 for calculations

    uint32_t multiplier1 = cpu_->registers_[reg_];
    uint32_t multiplier2 = cpu_->hidden_registers_[0];
    uint32_t product = multiplier1 * multiplier2;

    if (reg_ % 2)
    {
        cpu_->registers_[reg_] = product & 0x0000ffffu;
    }
    else
    {
        cpu_->registers_[reg_] = product >> 16;
        cpu_->registers_[reg_ + 1] = product & 0x0000ffffu;
    }

    cpu_->n_ = bool(product & 0x80000000u);
    cpu_->z_ = bool(product == 0);
    cpu_->v_ = false;
    if (product & 0xffff0000u)
    {
        cpu_->c_ = true;
    }

    // TODO: work with negative numbers
}


void DoubleOperandRegInstr::Div()
{
    assert(reg_ % 2 == 0); //R must be even
    assert(reg_ <= R4); //can't use R6 and R7 for calculations

    const uint32_t divider = cpu_->hidden_registers_[0];
    const uint32_t dividend = ((uint32_t(cpu_->registers_[reg_])) << 16) + cpu_->registers_[reg_ + 1];

    if (divider == 0)
    {
        cpu_->v_ = true;
        cpu_->c_ = true;
        return;
    }

    const uint16_t quotient = dividend / divider;
    const uint16_t remainder = dividend % divider;

    cpu_->registers_[reg_] = quotient;
    cpu_->registers_[reg_ + 1] = remainder;

    cpu_->n_ = bool(quotient & 0x8000u);
    cpu_->z_ = bool(quotient == 0);
    cpu_->c_ = false;

    // TODO: check v flag, work with negative numbers
}



// Implementation of conditional branch instructions
void ConditionalInstr::Br()
{
    if (offset_ & 0x0080u)
    {
        const uint8_t backOffset = word * (~(uint8_t(offset_)) + 1u);
        assert(cpu_->registers_[R7] >= backOffset); //address can't become negative
        cpu_->registers_[R7] -= backOffset;
    }
    else
    {
        const uint16_t forwardOffset = word * offset_;
        assert(forwardOffset <= 254); //offset can't be greater than 254
        cpu_->registers_[R7] += word * offset_;
    }
}


void ConditionalInstr::Bne()
{
    if (!cpu_->z_)
    {
        Br();
    }
}


void ConditionalInstr::Beq()
{
    if (cpu_->z_)
    {
        Br();
    }
}


void ConditionalInstr::Bge()
{
    if (!(cpu_->n_ ^ cpu_->v_))
    {
        Br();
    }
}


void ConditionalInstr::Blt()
{
    if (cpu_->n_ ^ cpu_->v_)
    {
        Br();
    }
}


void ConditionalInstr::Bgt()
{
    if (!(cpu_->z_ || (cpu_->n_ ^ cpu_->v_)))
    {
        Br();
    }
}


void ConditionalInstr::Ble()
{
    if (cpu_->z_ || (cpu_->n_ ^ cpu_->v_))
    {
        Br();
    }
}


void ConditionalInstr::Bpl()
{
    if (!cpu_->n_)
    {
        Br();
    }
}


void ConditionalInstr::Bmi()
{
    if (cpu_->n_)
    {
        Br();
    }
}


void ConditionalInstr::Bhi()
{
    if (!(cpu_->c_ || cpu_->z_))
    {
        Br();
    }
}


void ConditionalInstr::Blos()
{
    if (cpu_->c_ || cpu_->z_)
    {
        Br();
    }
}


void ConditionalInstr::Bvc()
{
    if (!cpu_->v_)
    {
        Br();
    }
}


void ConditionalInstr::Bvs()
{
    if (cpu_->v_)
    {
        Br();
    }
}


void ConditionalInstr::Bcc()
{
    if (!cpu_->c_)
    {
        Br();
    }
}


void ConditionalInstr::Bcs()
{
    if (cpu_->c_)
    {
        Br();
    }
}



