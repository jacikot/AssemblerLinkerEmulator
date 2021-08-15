#include <string>
namespace tokens{
    class Line{
        public:
            Expression exp;
    };

    class Expression{
    };
    class Directive : public Expression{

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

    };

}

