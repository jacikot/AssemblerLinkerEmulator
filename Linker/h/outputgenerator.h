# ifndef OUT_LINK
# define OUT_LINK

# define MAXLEN 15

# include <string> 
# include <fstream>
# include <vector>

struct header;
class Linker;
struct RelocationRecord;
class SectionTable;
class SymbolTable;


class OutputGenerator{

    public:
        int open(std::string name);
        int close();
        void writeHex(Linker*);
        void writeLinkable(Linker*);
        

    private:
        void writeHeader(header*);
        void printSections(SectionTable& sectionMap);
        void printSymbols(SymbolTable& symbols);
        void printRelocs(std::vector<RelocationRecord>&rels);
        void printSectionContent(SectionTable&sections);
        void printAddress(int addr);
    private:
        std::ofstream file;
        bool opened;

    

};


# endif