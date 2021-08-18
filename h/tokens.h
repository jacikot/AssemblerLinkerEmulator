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
        IMMED, PCREL, MEMDIR, REGDIR, REGIND, REGINDPOM
    };
    class Operand{
        public:
            Addressing adr;
            Initializer ini;
            std::string reg;
    };

    class Line{
        public:
            Expression* exp;
    };

    enum DirType{
        GLOBAL, EXTERN, SECTION, SKIP, WORD, EQU
    };

    enum InstructionType{
        HALT, INT, IRET, CALL, RET, JMP, JEQ, JNE, JGT, PUSH, POP, XCHG, ADD, SUB, MUL, DIV,CMP, NOT, AND, OR, XOR, TEST, SHL, SHR, LDR, STR, ERROR
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