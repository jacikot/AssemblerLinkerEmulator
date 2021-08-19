#ifndef ASSEMBLER
#define ASSEMBLER

# include <vector>
# include <string>
# include "symboltable.h" 
# include "tokens.h"
# include "sectionmapper.h"
# include "relocationtable.h"


class Assembler{
    public:
        void addSymbol(std::string str);

        void addSection(std::string str);

        void addLine(tokens::Line line);

        void addToCounter(int size){
            counter+=size;
        }

        void setNewSection(std::string name);

        void addAbsoluteSymbol(std::string name, int value);

        void addUndefinedSymbol(std::string name);

        void setGlobalSymbol(std::string name);

        int secondPass();

        void skip(int size);

        void initLiteral(int value);

        void initSymbol(std::string name);

        void initInstr0(int opcode);

        void initInstr2REGREG(int opcode,std::string dst, std::string src);

        void initInstr2REGOP(int opcode,std::string reg,tokens::Operand op);

        void initOperand(tokens::Operand op, std::string dst, int addend);

        void initPcRel(std::string name);
    private:
        int getRegNo(std::string reg);
        std::vector<tokens::Line>lines;
        SymbolTable symbolTable;
        SectionMapper sections;
        RelocationTable relocations;
        int counter=0;
        std::string curSection="";
    
};

#endif