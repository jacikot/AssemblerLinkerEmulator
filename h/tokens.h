#include <string>
#include <vector>
namespace tokens{
    class Line{
        public:
            Expression* exp;
    };

    enum DirType{
        GLOBAL, EXTERN, SECTION, SKIP, WORD, EQU
    };


    class Expression{
        
    };

    class Directive : public Expression{
        public:
            DirType type;
            std::vector<Initializer> symbols;
            std::string toInitialize;
    };


    class Instruction : public Expression{
        public:
            std::string mnemonic;
    };

    class Instr0 : public Instruction{

    };

    class Instr1_op : public Instruction{
        public:
            Operand operand;
    };

    class Instr1_reg : public Instruction{
        public:
            std::string reg;
    };

    class Instr2_regreg : public Instruction{
        public:
            std::string regSRC;
            std::string regDST;
    };

    class Instr2_regop : public Instruction{
        public:
            Operand operand;
            std::string reg;
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

}

