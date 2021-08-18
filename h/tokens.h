#ifndef TOKENS
#define TOKENS


#include <string>
#include <vector>
#include <map>

class Assembler;
namespace tokens{
    
    class Expression{
        public:
            virtual int secondPass(Assembler * asmb)=0;
    };

    class Initializer{
        public:
            bool symbol;
            std::string name;
            int value;
    };

    enum Addressing{
        IMMED=0b0000, REGDIRPOM=0b0101, MEMDIR=0b0100, REGDIR=0b0001, REGIND=0b0010, REGINDPOM=0b0011
    };
    class Operand{
        public:
            Addressing adr;
            Initializer ini;
            std::string reg;
            bool isPCREL=false;
            bool isSP=false;
    };

    class Line{
        public:
            Expression* exp;
    };

    enum DirType{
        GLOBAL, EXTERN, SECTION, SKIP, WORD, EQU
    };

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


    class Directive : public Expression{
        public:
            DirType type;
            std::vector<Initializer> symbols;
            std::string toInitialize;

            int secondPass(Assembler* asmb);
    };


    class Instruction : public Expression{
        public:
            static std::map<std::string,InstructionType> mnmMap;
            static bool initialized;
            static void initializeMap();

            Instruction(){
                if(!initialized) initializeMap();
            }
            std::string mnemonic;
            virtual int secondPass(Assembler * asmb)=0;
    };

    class Instr0 : public Instruction{
        public:
            int secondPass(Assembler* asmb);
    };

    class Instr1_op : public Instruction{
        public:
            Operand operand;
            int secondPass(Assembler* asmb);
    };

    class Instr1_reg : public Instruction{
        public:
            std::string reg;
            int secondPass(Assembler* asmb);
    };

    class Instr2_regreg : public Instruction{
        public:
            std::string regSRC;
            std::string regDST;
            int secondPass(Assembler* asmb);
    };

    class Instr2_regop : public Instruction{
        public:
            Operand operand;
            std::string reg;
            int secondPass(Assembler* asmb);
    };

    

}

#endif