#ifndef ASSEMBLER
#define ASSEMBLER

# include <vector>
# include <string>
# include "symboltable.h" 
# include "tokens.h"
# include "sectionmapper.h"
# include "relocationtable.h"
# include "outputgenerator.h"


struct header{
    int hsize; //header size
    int shsize; //section header size
    int sectioncnt; //number of sections
    int srsize; //symbol record size
    int symbolcnt; //number of symbols
    int relsize; //reloc record size
    int relcnt; //number of relocations
};


class Assembler{
    public:
        void addSymbol(std::string str);

        void addSection(std::string str);

        void addLine(tokens::Line line);

        void addToCounter(int size);

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

        int output(std::string filename);
    private:
        int getRegNo(std::string reg);
        header getHeaderData();
        std::vector<tokens::Line>lines;
        SymbolTable symbolTable;
        SectionMapper sections;
        RelocationTable relocations;
        OutputGenerator generator;
        int counter=0;
        std::string curSection="";
        bool finished=false;
    
};

#endif