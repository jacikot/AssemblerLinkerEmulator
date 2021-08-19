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

        bool exists(std::string name);

        void addSymbol(std::string name, std::string section, int value);

        void addSection(std::string name);

        void setSectionSize(std::string name, int value);

        void setGlobalSymbol(std::string name);

        void addAbsoluteSymbol(std::string name, int value);

        void addUndefinedSymbol(std::string name);

        int getSectionSize(std::string name);

        int getValue(std::string name);

        bool isGlobal(std::string name);

        std::string getSection(std::string name);

        ~SymbolTable(){
            delete table;
        }


};

#endif