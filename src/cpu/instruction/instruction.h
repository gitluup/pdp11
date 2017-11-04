#pragma once

#include "../decoder/decoder.h"

class Cpu;
class SingleOperandInstr;
class DoubleOperandInstr;
class DoubleOperandRegInstr;
class ConditionalInstr;
typedef void (SingleOperandInstr::* SingleOperandInstrExecutor)();
typedef void (DoubleOperandInstr::* DoubleOperandInstrExecutor)();
typedef void (DoubleOperandRegInstr::* DoubleOperandRegInstrExecutor)();
typedef void (ConditionalInstr::* ConditionalInstrExecutor)();
typedef uint16_t opcode_t;



class Instr
{
public:
    Instr();
    virtual ~Instr();

    virtual void Update(InstrInfo newInfo) = 0;
    virtual void FetchArgs() = 0;
    virtual void Execute() = 0;

private:
    Cpu* cpu;
};


class SingleOperandInstr : public Instr
{
public:
    SingleOperandInstr();
    virtual ~SingleOperandInstr();

    virtual void Update(InstrInfo newInfo);
    virtual void FetchArgs();
    virtual void Execute();

private:
    uint16_t opcode;
    uint16_t mode;
    uint16_t arg;

    std::map<opcode_t, SingleOperandInstrExecutor> instrExecutors;

    // Instruction's executors
    // Single operand instructions
    void Swab();
    void Jsr();
    void Emt();
    void Clr();
    void Clrb();
    void Com();
    void Comb();
    void Inc();
    void Incb();
    void Dec();
    void Decb();
    void Neg();
    void Negb();
    void Adc();
    void Adcb();
    void Sbc();
    void Sbcb();
    // ...
};


class DoubleOperandInstr : public Instr
{
    typedef void (DoubleOperandInstr::* InstrExecutor)();

public:
    DoubleOperandInstr();
    virtual ~DoubleOperandInstr();

    virtual void Update(InstrInfo newInfo);
    virtual void FetchArgs();
    virtual void Execute();

private:
    uint16_t opcode;
    uint16_t mode1;
    uint16_t arg1;
    uint16_t mode2;
    uint16_t arg2;

    std::map<opcode_t, DoubleOperandInstrExecutor> instrExecutors;

    // Double operand instructions
    void Mov();
    void Movb();
    void Cmp();
    void Cmpb();
    /*void Bit();
    void Bitb();
    void Bic();
    void Bicb();
    void Bis();
    void Bisb();
    void Add();
    void Sub();*/
};



class DoubleOperandRegInstr : public Instr
{
    typedef void (DoubleOperandRegInstr::* InstrExecutor)();

public:
    DoubleOperandRegInstr();
    virtual ~DoubleOperandRegInstr();

    virtual void Update(InstrInfo newInfo);
    virtual void FetchArgs();
    virtual void Execute();

private:
    uint16_t opcode;
    uint16_t arg1;
    uint16_t mode2;
    uint16_t arg2;

    std::map<opcode_t, DoubleOperandRegInstrExecutor> instrExecutors;

    // Double operand instructions (register source operand)
    void Mul();
    void Div();
    //void Ash();
    //void Ashc();
    //void Xor();
    //void Sob();
};


class ConditionalInstr : public Instr
{
    typedef void (ConditionalInstr::* InstrExecutor)();

public:
    ConditionalInstr();
    virtual ~ConditionalInstr();

    virtual void Update(InstrInfo newInfo);
    virtual void FetchArgs();
    virtual void Execute();

private:
    uint16_t opcode;
    uint16_t offset;

    std::map<opcode_t, ConditionalInstrExecutor> instrExecutors;

    // Contiotional branch instructions
    void Br();
    void Bne();
    /*void Beq();
    void Bge();
    void Blt();
    void Bgt();
    void Ble();
    void Bpl();
    void Bmi();
    void Bhi();
    void Blos();
    void Bvc();
    void Bvs();
    void Bcc();
    void Bhis();
    void Bcs();
    void Blo();*/
};

