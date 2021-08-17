#ifndef SYMBOLTABLE
#define SYMBOLTABLE

#include <string>
#include <map>


struct SymbolsData{
    //symbol value
    unsigned value; 

    //local/global
    bool global;

    //section name, absolute,undefined
    std::string section;

    //symbol name
    std::string name;

    //type - section or symbol
    bool isSection;

    //size - valid only for sections
    int size;
};

class SymbolTable{
    
    private:
        std::map <std::string,SymbolsData*>* table;
    
    public:
        SymbolTable(){
            table=new std::map<std::string,SymbolsData*>();
        }

        void addSymbol(std::string name, std::string section, int value);

        void addSection(std::string name);

        void setSectionSize(std::string name, int value);

        void addAbsoluteSymbol(std::string name, int value);

        void addUndefinedSymbol(std::string name);
        ~SymbolTable(){
            delete table;
        }


};

#endif