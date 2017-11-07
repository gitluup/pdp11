#include <iostream>
#include "instruction.h"
#include "../cpu.h"

extern const int byte = 1;
extern const int word = 2;


Instr::Instr(Cpu* cpu)
    : cpu(cpu)
{

}


Instr::~Instr()
{

}


uint16_t Instr::FetchOperandGeneralReg(const uint16_t mode, const uint16_t regNumber)
{
    assert(0 <= regNumber && regNumber <= 5);

    Memory* const memory = this->cpu->memory;
    uint16_t* const registers = this->cpu->registers;

    const uint16_t argSize = (this->opcode & 0x0010) ? word : byte;
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
            this->cpu->registers[regNumber] += argSize;
            break;
        case AUTOINC_DEFFERED:
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[regNumber]));
            this->cpu->registers[regNumber] += word;
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
            this->cpu->registers[R7] += word;
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[regNumber] + memory->GetWordByAddress(registers[R7])));
            break;

        default: assert(("Incorrect mode", 0));
    }

    return arg;
}


uint16_t Instr::FetchOperandStackPointer(const uint16_t mode)
{
    Memory* const memory = this->cpu->memory;
    uint16_t* const registers = this->cpu->registers;

    uint16_t arg = 0;

    switch (mode)
    {
        case REG_DEFERRED:
            arg = memory->GetWordByAddress(registers[R6]);
            break;
        case AUTOINC:
            arg = memory->GetWordByAddress(registers[R6]);
            this->cpu->registers[R6] += word;
            break;
        case AUTOINC_DEFFERED:
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[R6]));
            this->cpu->registers[R6] += word;
            break;
        case AUTODEC:
            registers[R6] -= word;
            arg = memory->GetWordByAddress(registers[R6]);
            break;
        case INDEX:
            this->cpu->registers[R7] += word;
            arg = memory->GetWordByAddress(registers[R6] + memory->GetWordByAddress(registers[R7]));
            break;
        case INDEX_DEFFERED:
            this->cpu->registers[R7] += word;
            arg = memory->GetWordByAddress(memory->GetWordByAddress(registers[R6] + memory->GetWordByAddress(registers[R7])));
            break;

        default: assert(("Incorrect mode for stack pointer (R6)", 0));
    }

    return arg;
}


uint16_t Instr::FetchOperandProgramCounter(const uint16_t mode)
{
    Memory* const memory = this->cpu->memory;
    uint16_t* const registers = this->cpu->registers;

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

        default: assert(("Incorrect mode for process counter (R7)", 0));
    }

    this->cpu->registers[R7] += word;

    return arg;
}


void Instr::SaveResultGeneralReg(const uint16_t mode, const uint16_t regNumber, const uint16_t result)
{
    assert(0 <= regNumber && regNumber <= 5);

    Memory* const memory = this->cpu->memory;
    uint16_t* const registers = this->cpu->registers;

    const uint16_t argSize = (this->opcode & 0x0010) ? word : byte;

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

        default: assert(("Incorrect mode", 0));
    }
}


void Instr::SaveResultStackPointer(const uint16_t mode, const uint16_t result)
{
    Memory* const memory = this->cpu->memory;
    uint16_t* const registers = this->cpu->registers;

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

        default: assert(("Incorrect mode for stack pointer (R6)", 0));
    }
}


void Instr::SaveResultProgramCounter(const uint16_t mode, const uint16_t result)
{
    Memory* const memory = this->cpu->memory;
    uint16_t* const registers = this->cpu->registers;

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

        default: assert(("Incorrect mode for process counter (R7)", 0));
    }
}


SingleOperandInstr::SingleOperandInstr(Cpu* cpu) : Instr(cpu)
{
    this->instrExecutors[00003] = &SingleOperandInstr::Swab;
    this->instrExecutors[00040] = &SingleOperandInstr::Jsr;
    this->instrExecutors[01040] = &SingleOperandInstr::Emt;
    this->instrExecutors[00050] = &SingleOperandInstr::Clr;
    this->instrExecutors[01050] = &SingleOperandInstr::Clrb;
    this->instrExecutors[00051] = &SingleOperandInstr::Com;
    this->instrExecutors[01051] = &SingleOperandInstr::Comb;
    this->instrExecutors[00052] = &SingleOperandInstr::Inc;
    this->instrExecutors[01052] = &SingleOperandInstr::Incb;
    this->instrExecutors[00053] = &SingleOperandInstr::Dec;
    this->instrExecutors[01053] = &SingleOperandInstr::Decb;
    this->instrExecutors[00054] = &SingleOperandInstr::Neg;
    this->instrExecutors[01054] = &SingleOperandInstr::Negb;
    this->instrExecutors[00055] = &SingleOperandInstr::Adc;
    this->instrExecutors[01055] = &SingleOperandInstr::Adcb;
    this->instrExecutors[00056] = &SingleOperandInstr::Sbc;
    this->instrExecutors[01056] = &SingleOperandInstr::Sbcb;
    this->instrExecutors[00057] = &SingleOperandInstr::Tst;
    this->instrExecutors[01057] = &SingleOperandInstr::Tstb;
}


SingleOperandInstr::~SingleOperandInstr()
{

}


void SingleOperandInstr::Update(const InstrInfo newInfo)
{
    assert(newInfo.instrType == SINGLE_OPERAND_INSTR);
    assert(newInfo.opcode && !newInfo.mode2 && !newInfo.arg2);

    this->opcode = newInfo.opcode;
    this->mode = newInfo.mode1;
    this->reg = newInfo.arg1;
}


void SingleOperandInstr::FetchArgs()
{
    uint16_t arg = 0;

    if (this->reg == R7)
    {
        arg = this->FetchOperandProgramCounter(this->mode);
    }
    else if (this->reg == R6)
    {
        arg = this->FetchOperandStackPointer(this->mode);
    }
    else
    {
        arg = this->FetchOperandGeneralReg(this->mode, this->reg);
    }

    this->cpu->hiddenRegisters[0] = arg;
}


void SingleOperandInstr::Execute()
{
    SingleOperandInstrExecutor executor = this->instrExecutors[this->opcode];
    assert(executor);
    (this->*executor)();
}


void SingleOperandInstr::Save()
{
    const uint16_t result = this->cpu->hiddenRegisters[0];

    if (this->reg == R7)
    {
        this->SaveResultProgramCounter(this->mode, result);
    }
    else if (this->reg == R6)
    {
        this->SaveResultStackPointer(this->mode, result);
    }
    else
    {
        this->SaveResultGeneralReg(this->mode, this->reg, result);
    }
}



DoubleOperandInstr::DoubleOperandInstr(Cpu* cpu) : Instr(cpu)
{
    this->instrExecutors[001] = &DoubleOperandInstr::Mov;
    this->instrExecutors[011] = &DoubleOperandInstr::Movb;
    this->instrExecutors[002] = &DoubleOperandInstr::Cmp;
    this->instrExecutors[012] = &DoubleOperandInstr::Cmpb;
    this->instrExecutors[006] = &DoubleOperandInstr::Add;
    this->instrExecutors[016] = &DoubleOperandInstr::Sub;
}


DoubleOperandInstr::~DoubleOperandInstr()
{

}


void DoubleOperandInstr::Update(InstrInfo newInfo)
{
    assert(newInfo.instrType == DOUBLE_OPERAND_INSTR);
    assert(newInfo.opcode);

    this->opcode = newInfo.opcode;
    this->srcMode = newInfo.mode1;
    this->src = newInfo.arg1;
    this->destMode = newInfo.mode2;
    this->dest = newInfo.arg2;
}


void DoubleOperandInstr::FetchArgs()
{
    uint16_t src = 0;
    uint16_t dest = 0;

    if (this->src == R7)
    {
        src = this->FetchOperandProgramCounter(this->srcMode);
    }
    else if (this->src == R6)
    {
        src = this->FetchOperandStackPointer(this->srcMode);
    }
    else
    {
        src = this->FetchOperandGeneralReg(this->srcMode, this->src);
    }

    if (this->dest == R7)
    {
        dest = this->FetchOperandProgramCounter(this->destMode);
    }
    else if (this->dest == R6)
    {
        dest = this->FetchOperandStackPointer(this->destMode);
    }
    else
    {
        dest = this->FetchOperandGeneralReg(this->destMode, this->dest);
    }

    this->cpu->hiddenRegisters[0] = src;
    this->cpu->hiddenRegisters[1] = dest;
}


void DoubleOperandInstr::Execute()
{
    DoubleOperandInstrExecutor executor = this->instrExecutors[this->opcode];
    assert(executor);
    (this->*executor)();
}


void DoubleOperandInstr::Save()
{
    const uint16_t srcResult = this->cpu->hiddenRegisters[0];
    const uint16_t destResult = this->cpu->hiddenRegisters[1];

    if (this->src == R7)
    {
        this->SaveResultProgramCounter(this->srcMode, srcResult);
    }
    else if (this->src == R6)
    {
        this->SaveResultStackPointer(this->srcMode, srcResult);
    }
    else
    {
        this->SaveResultGeneralReg(this->srcMode, this->src, srcResult);
    }

    if (this->dest == R7)
    {
        this->SaveResultProgramCounter(this->destMode, destResult);
    }
    else if (this->dest == R6)
    {
        this->SaveResultStackPointer(this->destMode, destResult);
    }
    else
    {
        this->SaveResultGeneralReg(this->destMode, this->dest, destResult);
    }
}



DoubleOperandRegInstr::DoubleOperandRegInstr(Cpu* cpu) : Instr(cpu)
{
    this->instrExecutors[0070] = &DoubleOperandRegInstr::Mul;
    this->instrExecutors[0071] = &DoubleOperandRegInstr::Div;
    // ...
}


DoubleOperandRegInstr::~DoubleOperandRegInstr()
{

}


void DoubleOperandRegInstr::Update(const InstrInfo newInfo)
{
    assert(newInfo.instrType == DOUBLE_OPERAND_REG_INSTR);
    assert(newInfo.opcode && !newInfo.mode1);

    this->opcode = newInfo.opcode;
    this->reg = newInfo.arg1;
    this->argMode = newInfo.mode2;
    this->arg = newInfo.arg2;
}


void DoubleOperandRegInstr::FetchArgs()
{
    uint16_t arg = 0;

    if (this->arg == R7)
    {
        arg = this->FetchOperandProgramCounter(this->argMode);
    }
    else if (this->arg == R6)
    {
        arg = this->FetchOperandStackPointer(this->argMode);
    }
    else
    {
        arg = this->FetchOperandGeneralReg(this->argMode, this->arg);
    }

    //this->cpu->hiddenRegisters[0] = this->cpu->registers[this->reg];
    this->cpu->hiddenRegisters[0] = arg;
}


void DoubleOperandRegInstr::Execute()
{
    DoubleOperandRegInstrExecutor executor = this->instrExecutors[this->opcode];
    assert(executor);
    (this->*executor)();
}


void DoubleOperandRegInstr::Save()
{
    /*this->cpu->registers[this->reg] = this->cpu->hiddenRegisters[0];
    const uint16_t result = this->cpu->hiddenRegisters[1];

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
    this->instrExecutors[01] = &ConditionalInstr::Br;
    this->instrExecutors[02] = &ConditionalInstr::Bne;
    this->instrExecutors[03] = &ConditionalInstr::Beq;
    this->instrExecutors[04] = &ConditionalInstr::Bge;
    this->instrExecutors[05] = &ConditionalInstr::Blt;
    this->instrExecutors[06] = &ConditionalInstr::Bgt;
    this->instrExecutors[07] = &ConditionalInstr::Ble;

    this->instrExecutors[0200] = &ConditionalInstr::Bpl;
    this->instrExecutors[0201] = &ConditionalInstr::Bmi;
    this->instrExecutors[0202] = &ConditionalInstr::Bhi;
    this->instrExecutors[0203] = &ConditionalInstr::Blos;
    this->instrExecutors[0204] = &ConditionalInstr::Bvc;
    this->instrExecutors[0205] = &ConditionalInstr::Bvs;
    this->instrExecutors[0206] = &ConditionalInstr::Bcc;
    this->instrExecutors[0207] = &ConditionalInstr::Bcs;
}


ConditionalInstr::~ConditionalInstr()
{

}


void ConditionalInstr::Update(InstrInfo newInfo)
{
    assert(newInfo.instrType == CONDITIONAL_INSTR);
    assert(!newInfo.mode1 && !newInfo.mode2 && !newInfo.arg2);

    this->opcode = newInfo.opcode;
    this->offset = newInfo.arg1;
}


void ConditionalInstr::FetchArgs()
{
    this->cpu->hiddenRegisters[0] = this->offset;
}


void ConditionalInstr::Execute()
{
    ConditionalInstrExecutor executor = this->instrExecutors[this->opcode];
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
    assert(("Not implemented", 0));
}

void SingleOperandInstr::Jsr()
{
    assert(("Not implemented", 0));
}

void SingleOperandInstr::Emt()
{
    assert(("Not implemented", 0));
}

void SingleOperandInstr::Clr()
{
    this->cpu->hiddenRegisters[0] = 0;

    this->cpu->n = false;
    this->cpu->z = true;
    this->cpu->v = false;
    this->cpu->c = false;
}

void SingleOperandInstr::Clrb()
{
    this->cpu->hiddenRegisters[0] &= 0xff00u;

    this->cpu->n = false;
    this->cpu->z = true;
    this->cpu->v = false;
    this->cpu->c = false;
}

void SingleOperandInstr::Com()
{
    this->cpu->hiddenRegisters[0] = ~(this->cpu->hiddenRegisters[0]);

    this->cpu->n = bool(this->cpu->hiddenRegisters[0] & 0x8000u);
    this->cpu->z = bool(this->cpu->hiddenRegisters[0]);
}

void SingleOperandInstr::Comb()
{
    const uint16_t mask = 0xff00u + 0x00ffu & (~this->cpu->hiddenRegisters[0]);
    this->cpu->hiddenRegisters[0] &= mask;

    this->cpu->n = bool(this->cpu->hiddenRegisters[0] & 0x0080u);
    this->cpu->z = bool(this->cpu->hiddenRegisters[0] & 0x00ffu);
}

void SingleOperandInstr::Inc()
{
    this->cpu->hiddenRegisters[0] += 1u;

    this->cpu->n = bool(this->cpu->hiddenRegisters[0] & 0x8000u);
    this->cpu->z = bool(this->cpu->hiddenRegisters[0] == 0);
    this->cpu->v = bool(this->cpu->hiddenRegisters[0] - 1u == 077777u);
}

void SingleOperandInstr::Incb()
{
    uint8_t lowByte = 0x00ffu & this->cpu->hiddenRegisters[0];
    lowByte += 1u;
    this->cpu->hiddenRegisters[0] &= 0xff00u;
    this->cpu->hiddenRegisters[0] += lowByte;

    this->cpu->n = bool(lowByte & 0x80u);
    this->cpu->z = bool(lowByte == 0);
    this->cpu->v = bool((lowByte - 1u) == 127u);
}

void SingleOperandInstr::Dec()
{
    this->cpu->hiddenRegisters[0] -= 1u;

    this->cpu->n = bool(this->cpu->hiddenRegisters[0] & 0x8000);
    this->cpu->z = bool(this->cpu->hiddenRegisters[0] == 0);
    this->cpu->v = bool(this->cpu->hiddenRegisters[0] + 1u == 0100000u);
}

void SingleOperandInstr::Decb()
{
    uint8_t lowByte = 0x00ffu & this->cpu->hiddenRegisters[0];
    lowByte -= 1u;
    this->cpu->hiddenRegisters[0] &= 0xff00u;
    this->cpu->hiddenRegisters[0] += lowByte;

    this->cpu->n = bool(lowByte & 0x80u);
    this->cpu->z = bool(lowByte == 0);
    this->cpu->v = bool((lowByte + 1u) == 128u);
}

void SingleOperandInstr::Neg()
{
    this->cpu->hiddenRegisters[0] = ~(this->cpu->hiddenRegisters[0]) + 1u;

    this->cpu->n = bool(this->cpu->hiddenRegisters[0] & 0x8000);
    this->cpu->z = bool(this->cpu->hiddenRegisters[0] == 0);
    this->cpu->v = bool(this->cpu->hiddenRegisters[0] == 0100000u);
    this->cpu->c = !(this->cpu->z);
}

void SingleOperandInstr::Negb()
{
    uint8_t lowByte = 0x00ffu & this->cpu->hiddenRegisters[0];
    lowByte = ~lowByte + 1u;
    this->cpu->hiddenRegisters[0] &= 0xff00u;
    this->cpu->hiddenRegisters[0] += lowByte;

    this->cpu->n = bool(lowByte & 0x80u);
    this->cpu->z = bool(lowByte == 0);
    this->cpu->v = bool(lowByte == 128u);
    this->cpu->c = !(this->cpu->z);
}

void SingleOperandInstr::Adc()
{
    assert(("Not implemented", 0));
}

void SingleOperandInstr::Adcb()
{
    assert(("Not implemented", 0));
}

void SingleOperandInstr::Sbc()
{
    assert(("Not implemented", 0));
}

void SingleOperandInstr::Sbcb()
{
    assert(("Not implemented", 0));
}

void SingleOperandInstr::Tst()
{
    this->cpu->n = bool(this->cpu->hiddenRegisters[0] & 0x8000u);
    this->cpu->z = bool(this->cpu->hiddenRegisters[0] == 0);
    this->cpu->v = false;
    this->cpu->c = false;
}

void SingleOperandInstr::Tstb()
{
    this->cpu->n = bool(this->cpu->hiddenRegisters[0] & 0x0080u);
    this->cpu->z = bool((0x00ffu & this->cpu->hiddenRegisters[0]) == 0);
    this->cpu->v = false;
    this->cpu->c = false;
}




// Implementation of double operand intructions
void DoubleOperandInstr::Mov()
{
    //printf("MOV   opcode = %o  mode1 = %d  arg1 = %d  mode2 = %d  arg2 = %d\n", opcode, srcMode, src, destMode, dest);
    this->cpu->hiddenRegisters[1] = this->cpu->hiddenRegisters[0];

    this->cpu->n = bool(this->cpu->hiddenRegisters[0] & 0x8000u);
    this->cpu->z = bool(this->cpu->hiddenRegisters[0] == 0);
    this->cpu->v = false;
}


void DoubleOperandInstr::Movb()
{
    const uint8_t lowByte = (this->cpu->hiddenRegisters[0] & 0x00ffu);
    this->cpu->hiddenRegisters[1] &= 0xff00u;
    this->cpu->hiddenRegisters[1] += lowByte;

    this->cpu->n = bool(lowByte & 0x80u);
    this->cpu->z = bool(lowByte == 0);
    this->cpu->v = false;

    if (this->destMode == REG)
    {
        const bool sign = this->cpu->hiddenRegisters[1] & 0x0080u;
        if (sign)
        {
            this->cpu->hiddenRegisters[1] = 0xff00u + lowByte;
        }
        else
        {
            this->cpu->hiddenRegisters[1] &= 0x00ffu;
        }
    }

}


void DoubleOperandInstr::Cmp()
{
    const uint16_t src = this->cpu->hiddenRegisters[0];
    const uint16_t dest = this->cpu->hiddenRegisters[1];
    const uint32_t result = src + ~(dest) + 1u;

    this->cpu->n = bool(result & 0x8000u);
    this->cpu->z = bool((result & 0xffffu) == 0);
    this->cpu->v = bool(((src & 0x8000u ^ dest & 0x8000u)) && ((dest & 0x8000u) == (result & 0x8000)));
    this->cpu->c = bool(!(result & 0x10000));
}


void DoubleOperandInstr::Cmpb()
{
    const uint8_t src = 0x00ff & this->cpu->hiddenRegisters[0];
    const uint8_t dest = 0x00ff & this->cpu->hiddenRegisters[1];
    const uint16_t result = src + ~(dest) + 1u;

    this->cpu->n = bool(result & 0x80u);
    this->cpu->z = bool((result & 0xffu) == 0);
    this->cpu->v = bool(((src & 0x80u ^ dest & 0x80u)) && ((dest & 0x80u) == (result & 0x80)));
    this->cpu->c = bool(!(result & 0x100));
}


void DoubleOperandInstr::Add()
{
    const uint16_t src = this->cpu->hiddenRegisters[0];
    const uint16_t dest = this->cpu->hiddenRegisters[1];
    const uint32_t result = src + dest;
    this->cpu->hiddenRegisters[1] = result;

    this->cpu->n = bool(result & 0x8000u);
    this->cpu->z = bool((result & 0xffffu) == 0);
    this->cpu->v = bool((!(src & 0x8000u ^ dest & 0x8000u)) && ((dest & 0x8000u) != (result & 0x8000)));
    this->cpu->c = bool(result & 0x10000);
}


void DoubleOperandInstr::Sub()
{
    const uint16_t src = this->cpu->hiddenRegisters[0];
    const uint16_t dest = this->cpu->hiddenRegisters[1];
    const uint32_t result = src + ~(dest) + 1u;

    this->cpu->n = bool(result & 0x8000u);
    this->cpu->z = bool((result & 0xffffu) == 0);
    this->cpu->v = bool(((src & 0x8000u ^ dest & 0x8000u)) && ((src & 0x8000u) == (result & 0x8000u)));
    this->cpu->c = bool(!(result & 0x10000u));
}



// Implementation of double operand intructions (register source operand)
void DoubleOperandRegInstr::Mul()
{
    assert(("Can't use R6 and R7 for calculations", this->reg <= R4));

    uint32_t multiplier1 = this->cpu->registers[this->reg];
    uint32_t multiplier2 = this->cpu->hiddenRegisters[0];
    uint32_t product = multiplier1 * multiplier2;

    if (this->reg % 2)
    {
        this->cpu->registers[this->reg] = product & 0x0000ffffu;
    }
    else
    {
        this->cpu->registers[this->reg] = product >> 16;
        this->cpu->registers[this->reg + 1] = product & 0x0000ffffu;
    }

    this->cpu->n = bool(product & 0x80000000u);
    this->cpu->z = bool(product == 0);
    this->cpu->v = false;
    if (product & 0xffff0000u)
    {
        this->cpu->c = true;
    }

    // TODO: work with negative numbers
}


void DoubleOperandRegInstr::Div()
{
    assert(("R must be even", this->reg % 2 == 0));
    assert(("Can't use R6 and R7 for calculations", this->reg <= R4));

    const uint32_t divider = this->cpu->hiddenRegisters[0];
    const uint32_t dividend = ((uint32_t(this->cpu->registers[this->reg])) << 16) + this->cpu->registers[this->reg + 1];
    printf("!!! %u %u\n", dividend, divider);

    if (divider == 0)
    {
        this->cpu->v = true;
        this->cpu->c = true;
        return;
    }

    const uint16_t quotient = dividend / divider;
    const uint16_t remainder = dividend % divider;

    this->cpu->registers[this->reg] = quotient;
    this->cpu->registers[this->reg + 1] = remainder;
    printf("### %u %u\n", quotient, remainder);

    this->cpu->n = bool(quotient & 0x8000u);
    this->cpu->z = bool(quotient == 0);
    this->cpu->c = false;

    // TODO: check v flag, work with negative numbers
}



// Implementation of conditional branch instructions
void ConditionalInstr::Br()
{
    if (this->offset & 0x0080u)
    {
        const uint8_t backOffset = word * (~(uint8_t(this->offset)) + 1u);
        assert(("address can't become negative", this->cpu->registers[R7] >= backOffset));
        this->cpu->registers[R7] -= backOffset;
    }
    else
    {
        const uint16_t forwardOffset = word * this->offset;
        assert(("offset can't be greater than 254", forwardOffset <= 254));
        this->cpu->registers[R7] += word * this->offset;
    }
}


void ConditionalInstr::Bne()
{
    if (!this->cpu->z)
    {
        this->Br();
    }
}


void ConditionalInstr::Beq()
{
    if (this->cpu->z)
    {
        this->Br();
    }
}


void ConditionalInstr::Bge()
{
    if (!(this->cpu->n ^ this->cpu->v))
    {
        this->Br();
    }
}


void ConditionalInstr::Blt()
{
    if (this->cpu->n ^ this->cpu->v)
    {
        this->Br();
    }
}


void ConditionalInstr::Bgt()
{
    if (!(this->cpu->z || (this->cpu->n ^ this->cpu->v)))
    {
        this->Br();
    }
}


void ConditionalInstr::Ble()
{
    if (this->cpu->z || (this->cpu->n ^ this->cpu->v))
    {
        this->Br();
    }
}


void ConditionalInstr::Bpl()
{
    if (!this->cpu->n)
    {
        this->Br();
    }
}


void ConditionalInstr::Bmi()
{
    if (this->cpu->n)
    {
        this->Br();
    }
}


void ConditionalInstr::Bhi()
{
    if (!(this->cpu->c || this->cpu->z))
    {
        this->Br();
    }
}


void ConditionalInstr::Blos()
{
    if (this->cpu->c || this->cpu->z)
    {
        this->Br();
    }
}


void ConditionalInstr::Bvc()
{
    if (!this->cpu->v)
    {
        this->Br();
    }
}


void ConditionalInstr::Bvs()
{
    if (this->cpu->v)
    {
        this->Br();
    }
}


void ConditionalInstr::Bcc()
{
    if (!this->cpu->c)
    {
        this->Br();
    }
}


void ConditionalInstr::Bcs()
{
    if (this->cpu->c)
    {
        this->Br();
    }
}



