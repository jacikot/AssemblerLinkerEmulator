# ifndef SYMTAB_LIN
# define SYMTAB_LIN

# include <map>
# include "inputreader.h"
# include <string>
# include <vector>

class SectionTable;

class SymbolTable{
    public:
        bool exist(std::string name);

        int insertSymbol(SymbolsData&d);

        bool checkUndefined();

        void resolveSymbols(SectionTable&);

        int getValue(std::string name);

        int size(){
            return symbolsMap.size();
        }

        std::vector<SymbolsData> getAllSymbols();

        ~SymbolTable();

    private:
        std::map<std::string,SymbolsData*> symbolsMap;
        std::vector<SymbolsData> undefined;

};



# endif
