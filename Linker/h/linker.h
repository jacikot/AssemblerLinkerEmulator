# ifndef LINKER_H
# define LINKER_H


# include <string>
# include <map>
# include <vector>
# include "inputreader.h"
# include "outputgenerator.h"
# include "sectiontable.h"
# include "symbolstable.h"

class Linker{
    public:
        int link();
        
        int readFiles(); 

        bool resolveSectionOffsets();

        bool checkUndefined();

        void resolveSymbolValues();

        void resolveRelocs();

        int generateOutput();

        header* getHeader();

        SectionTable& getSectionTable(){
            return sectionMap;
        }

        SymbolTable& getSymbolTable(){
            return symbolsMap;
        }

        std::vector<RelocationRecord>& getRelTable(){
            return relocations;
        }

    public:
        std::string outputFile="";
        bool hex=false;
        bool linkable=false;
        std::map<std::string,int> secAddr;
        std::vector<std::string> files;

    private:
        SectionTable sectionMap; 
        SymbolTable symbolsMap;
        std::vector<RelocationRecord> relocations;
        InputReader reader;
        OutputGenerator writer;


};


# endif
