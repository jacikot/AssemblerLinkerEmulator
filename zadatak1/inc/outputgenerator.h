#ifndef OUTPGEN
#define OUTPGEN

# define MAXLEN 15
# include <string>
# include <fstream>
# include <vector>
struct header;
class SymbolTable;
class RelocationTable;
class SectionMapper;

class OutputGenerator{
    public:
        void openFile(std::string name);

        void closeFile();

        void printHeader(header h);

        void printSections(SymbolTable*symbols);

        void printSymbols(SymbolTable*symbols);

        void printRelocs(RelocationTable*rels);

        void printSectionContent(SectionMapper*sections,SymbolTable*symbols);
    private:
        std::ofstream file;
        bool open=false;

        void printAddress(int addr);
};

struct sectiondata{
    int cnt;
    char name [MAXLEN];
    int value;
    int size;
    char global;
};


#endif