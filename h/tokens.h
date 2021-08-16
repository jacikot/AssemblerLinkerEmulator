#include <string>
#include <vector>
namespace tokens{
    class Line{
        public:
            Expression exp;
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

    };

    class Instr1_reg : public Instruction{

    };

    class Instr2_regreg : public Instruction{

    };

    class Instr2_regop : public Instruction{

    };

    class Initializer{
        public:
            bool symbol;
            std::string name;
            int value;
    };

}

