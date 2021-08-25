# ifndef EMULATOR
# define EMULATOR

# include <string>
# include "memory.h"
# include "inputreader.h"
# include "cpu.h"
# include "terminal.h"
# include <vector>
# include <map>

# define SP_START 0xFEFE


enum InstructionType{
    HALT=0b00000000, 
    INT=0b00010000, 
    IRET=0b00100000, 
    CALL=0b00110000, 
    RET=0b01000000, 
    JMP=0b01010000, 
    JEQ=0b01010001, 
    JNE=0b01010010, 
    JGT=0b01010011, 
    PUSH=0b10110000, 
    POP=0b10100000, 
    XCHG=0b01100000, 
    ADD=0b01110000, 
    SUB=0b01110001, 
    MUL=0b01110010, 
    DIV=0b01110011,
    CMP=0b01110100,
    NOT=0b10000000,
    AND=0b10000001, 
    OR=0b10000010, 
    XOR=0b10000011, 
    TEST=0b10000100, 
    SHL=0b10010000, 
    SHR=0b10010001, 
    LDR=0b10100000, 
    STR=0b10110000, 
    ERROR=0b11111111
};

enum Addressing{
    IMMED=0b0000, REGDIRPOM=0b0101, MEMDIR=0b0100, REGDIR=0b0001, REGIND=0b0010, REGINDPOM=0b0011
};

# define REGD(byte) (byte>>4)&0xF
# define REGS(byte) byte&0xF
# define ADDRH(byte) (byte>>4)&0xF
# define ADDRL(byte) byte&0xF


class Emulator{
    public:
        int emulate();

        int readInput();

        int init();
    public:
        std::string inputFile;
    private:
        InputReader reader;
        Memory memory;
        CPU cpu;
        bool finished=false;
        std::map<int,std::vector<char>>content;
        Terminal terminal;

    private:
        int getOperand(int addr, int regs);
        void storeToOperand(int addr, int regs);
        void pop(int regD);
        void push(int regD);
        void reset();
        void interrupts();
        

};


# endif