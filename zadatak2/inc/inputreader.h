# ifndef INREAD_H
# define INREAD_H

# include <fstream>
# include <vector>
# include <map>
struct header{
    int sectionsNum;
    int symbolsNum;
    int relocsNum;
};

struct SectionsData{
    //symbol value
    unsigned value; 

    //local/global
    char global;

    //symbol name
    std::string name;

    //size - valid only for sections
    int size;

    //content
    char* content;
};

struct SymbolsData{
    //symbol value
    unsigned value; 

    //local/global
    char global;

    //symbol name
    std::string name;

    //section name
    std::string section;

    //file id
    int file;
};

enum RelocationType{
    R_386_16, R_386_PC16
};
struct RelocationRecord{

        //section
        std::string section;

        //offset from beginning of the section
        int offset;

        //type
        RelocationType type;

        //symbol name
        std::string name;

        //file id
        int file;

};

class InputReader{
    public:
        void openFile(std::string name);

        void closeFile();

        header* readHeader();

        std::vector<SectionsData> readSections(int cntSec);

        std::vector<SymbolsData> readSymbols(int cntSym, int f);

        std::vector<RelocationRecord> readRelocations(int cntRel, int f);

        std::map<std::string,char*> readSectionsContent(std::vector<SectionsData>*secinfo);
    private:

        int readNum();
        std::ifstream file;
        bool open;


};


# endif