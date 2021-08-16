# include <vector>
# include <string>
# include "symboltable.h" 
# include "tokens.h"


class Assembler{
    public:
        void addSymbol(std::string str);
        void addSection(std::string str);
        void addLine(tokens::Line line);
        void addToCounter(int size){
            counter+=size;
        }
        void addAbsoluteSymbol(std::string name, int value);

    private:
        std::vector<tokens::Line>lines;
        SymbolTable symbolTable;
        int counter=0;
        std::string curSection="";
    
}
