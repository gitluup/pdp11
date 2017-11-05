#include <iostream>
#include "instruction.h"
#include "../cpu.h"


Instr::Instr()
{

}

Instr::~Instr()
{

}



SingleOperandInstr::SingleOperandInstr()
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
    // ...

}

SingleOperandInstr::~SingleOperandInstr()
{

}

void SingleOperandInstr::Update(InstrInfo newInfo)
{
    assert(newInfo.instrType == SINGLE_OPERAND_INSTR);
    assert(newInfo.opcode && !newInfo.mode2 && !newInfo.arg2);

    this->opcode = newInfo.opcode;
    this->mode = newInfo.mode1;
    this->arg = newInfo.arg1;
}

void SingleOperandInstr::FetchArgs()
{

}

void SingleOperandInstr::Execute()
{
    SingleOperandInstrExecutor executor = this->instrExecutors[this->opcode];
    assert(executor);
    (this->*executor)();
}



DoubleOperandInstr::DoubleOperandInstr()
{
    this->instrExecutors[001] = &DoubleOperandInstr::Mov;
    this->instrExecutors[011] = &DoubleOperandInstr::Movb;
    this->instrExecutors[002] = &DoubleOperandInstr::Cmp;
    this->instrExecutors[012] = &DoubleOperandInstr::Cmpb;
    // ...
}

DoubleOperandInstr::~DoubleOperandInstr()
{

}

void DoubleOperandInstr::Update(InstrInfo newInfo)
{
    assert(newInfo.instrType == DOUBLE_OPERAND_INSTR);
    assert(newInfo.opcode);

    this->opcode = newInfo.opcode;
    this->mode1 = newInfo.mode1;
    this->arg1 = newInfo.arg1;
    this->mode2 = newInfo.mode2;
    this->arg2 = newInfo.arg2;
}

void DoubleOperandInstr::FetchArgs()
{

}

void DoubleOperandInstr::Execute()
{
    DoubleOperandInstrExecutor executor = this->instrExecutors[this->opcode];
    assert(executor);
    (this->*executor)();
}



DoubleOperandRegInstr::DoubleOperandRegInstr()
{
    this->instrExecutors[0070] = &DoubleOperandRegInstr::Mul;
    this->instrExecutors[0071] = &DoubleOperandRegInstr::Div;
    // ...
}

DoubleOperandRegInstr::~DoubleOperandRegInstr()
{

}

void DoubleOperandRegInstr::Update(InstrInfo newInfo)
{
    assert(newInfo.instrType == DOUBLE_OPERAND_REG_INSTR);
    assert(newInfo.opcode && !newInfo.mode1);

    this->opcode = newInfo.opcode;
    this->arg1 = newInfo.arg1;
    this->mode2 = newInfo.mode2;
    this->arg2 = newInfo.arg2;
}

void DoubleOperandRegInstr::FetchArgs()
{

}

void DoubleOperandRegInstr::Execute()
{
    DoubleOperandRegInstrExecutor executor = this->instrExecutors[this->opcode];
    assert(executor);
    (this->*executor)();
}



ConditionalInstr::ConditionalInstr()
{
    this->instrExecutors[01] = &ConditionalInstr::Br;
    this->instrExecutors[02] = &ConditionalInstr::Bne;
    // ...
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

}

void ConditionalInstr::Execute()
{
    ConditionalInstrExecutor executor = this->instrExecutors[this->opcode];
    assert(executor);
    (this->*executor)();
}




// Implementation of single operand intructions
void SingleOperandInstr::Swab()
{
    //this->cpu->r0 = this->cpu->memory->GetWordByAddress()
}

void SingleOperandInstr::Jsr()
{

}

void SingleOperandInstr::Emt()
{

}

void SingleOperandInstr::Clr()
{

}

void SingleOperandInstr::Clrb()
{

}

void SingleOperandInstr::Com()
{

}

void SingleOperandInstr::Comb()
{

}

void SingleOperandInstr::Inc()
{
    printf("INC   opcode = %o  mode = %d  arg = %d\n", opcode, mode, arg);
}

void SingleOperandInstr::Incb()
{

}

void SingleOperandInstr::Dec()
{

}

void SingleOperandInstr::Decb()
{

}

void SingleOperandInstr::Neg()
{

}

void SingleOperandInstr::Negb()
{

}

void SingleOperandInstr::Adc()
{

}

void SingleOperandInstr::Adcb()
{

}

void SingleOperandInstr::Sbc()
{

}

void SingleOperandInstr::Sbcb()
{

}




// Implementation of double operand intructions
void DoubleOperandInstr::Mov()
{
    printf("MOV   opcode = %o  mode1 = %d  arg1 = %d  mode2 = %d  arg2 = %d\n", opcode, mode1, arg1, mode2, arg2);
}

void DoubleOperandInstr::Movb()
{

}

void DoubleOperandInstr::Cmp()
{

}

void DoubleOperandInstr::Cmpb()
{

}



// Implementation of double operand intructions (register source operand)
void DoubleOperandRegInstr::Mul()
{

}

void DoubleOperandRegInstr::Div()
{
    printf("DIV   opcode = %o  arg1 = %d  mode2 = %d  arg2 = %d\n", opcode, arg1, mode2, arg2);
}



// Implementation of conditional branch intructions
void ConditionalInstr::Br()
{
    printf("BR   opcode = %o  offset = %x\n", opcode, offset);
}

void ConditionalInstr::Bne()
{
    printf("BNE   opcode = %o  offset = %x\n", opcode, offset);
}

