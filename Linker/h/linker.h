# ifndef LINKER_H
# define LINKER_H


# include <string>
# include <map>
# include <vector>
# include "inputreader.h"

class Linker{
    public:
        int readFiles(); 

        void resolveSectionOffsets();

        bool checkUndefined();

        void resolveSymbolValues();

        void resolveRelocs();
    public:
        std::string outputFile="";
        bool hex=false;
        bool linkable=false;
        std::map<std::string,int> secAddr;
        std::vector<std::string> files;
        ~Linker();

    private:
        std::map<std::string,std::map<int,SectionsData*>*> sectionMap; 
        std::map<std::string,SymbolsData*> symbolsMap;
        std::vector<SymbolsData> undefined;
        std::vector<RelocationRecord> relocations;
        InputReader reader;


};


# endif
