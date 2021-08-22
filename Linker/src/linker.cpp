# include "../h/linker.h"
# include "../h/inputreader.h"

# include <vector>
# include <map>

int Linker::readFiles(){
    for(std::string filename:files){
        reader.openFile(filename);
        header*h=reader.readHeader();
        std::vector<SectionsData> sections=reader.readSections(h->sectionsNum);
        std::vector<SymbolsData> symbols=reader.readSymbols(h->symbolsNum);
        std::vector<RelocationRecord> relocations=reader.readRelocations(h->relocsNum);
        std::map<std::string,char*> content=reader.readSectionsContent(&sections);
        reader.closeFile();
    }
}