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
    explicit Instr(Cpu* cpu);
    virtual ~Instr();

    virtual void Update(const InstrInfo newInfo) = 0;
    virtual void FetchArgs() = 0;
    virtual void Execute() = 0;
    virtual void Save() = 0;

protected:
    uint16_t FetchOperandGeneralReg(const uint16_t mode, const uint16_t regNumber);
    uint16_t FetchOperandStackPointer(const uint16_t mode);
    uint16_t FetchOperandProgramCounter(const uint16_t mode);
    void SaveResultGeneralReg(const uint16_t mode, const uint16_t regNumber, const uint16_t result);
    void SaveResultStackPointer(const uint16_t mode, const uint16_t result);
    void SaveResultProgramCounter(const uint16_t mode, const uint16_t result);

    uint16_t opcode_ = 0;
    Cpu* cpu_ = nullptr;
};


class SingleOperandInstr : public Instr
{
public:
    explicit SingleOperandInstr(Cpu* cpu);
    virtual ~SingleOperandInstr();

    virtual void Update(const InstrInfo newInfo);
    virtual void FetchArgs();
    virtual void Execute();
    virtual void Save();

private:
    uint16_t mode_ = 0;
    uint16_t reg_ = 0;

    std::map<opcode_t, SingleOperandInstrExecutor> instr_executors_;

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
    void Tst();
    void Tstb();
};


class DoubleOperandInstr : public Instr
{
    typedef void (DoubleOperandInstr::* InstrExecutor)();

public:
    explicit DoubleOperandInstr(Cpu* cpu);
    virtual ~DoubleOperandInstr();

    virtual void Update(const InstrInfo newInfo);
    virtual void FetchArgs();
    virtual void Execute();
    virtual void Save();

private:
    uint16_t src_mode_ = 0;
    uint16_t src_ = 0;
    uint16_t dest_mode_ = 0;
    uint16_t dest_ = 0;

    std::map<opcode_t, DoubleOperandInstrExecutor> instr_executors_;

    // Double operand instructions
    void Mov();
    void Movb();
    void Cmp();
    void Cmpb();
    void Add();
    void Sub();
};



class DoubleOperandRegInstr : public Instr
{
    typedef void (DoubleOperandRegInstr::* InstrExecutor)();

public:
    explicit DoubleOperandRegInstr(Cpu* cpu);
    virtual ~DoubleOperandRegInstr();

    virtual void Update(const InstrInfo newInfo);
    virtual void FetchArgs();
    virtual void Execute();
    virtual void Save();

private:
    uint16_t reg_ = 0;
    uint16_t arg_mode_ = 0;
    uint16_t arg_ = 0;

    std::map<opcode_t, DoubleOperandRegInstrExecutor> instr_executors_;

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
    explicit ConditionalInstr(Cpu* cpu);
    virtual ~ConditionalInstr();

    virtual void Update(const InstrInfo newInfo);
    virtual void FetchArgs();
    virtual void Execute();
    virtual void Save();

private:
    uint16_t offset_ = 0;

    std::map<opcode_t, ConditionalInstrExecutor> instr_executors_;

    // Contiotional branch instructions
    void Br();
    void Bne();
    void Beq();
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
    void Bcs();
};

