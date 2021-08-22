# include "../h/inputreader.h"

# include <regex> 
# include <string> 
# include <iomanip>
# include <vector>
# include <algorithm>

void InputReader::openFile(std::string name){
    if(!open)file.open(name);
    open=true;
}

void InputReader::closeFile(){
    if(open)file.close();
    open=false;
}

int InputReader::readNum(){
    std::string line;
    std::getline(file,line);
    std::regex reg("[^0-9]*([0-9]+).*");
    std::smatch sm;
    std::regex_match(line,sm, reg);
    return stoi(sm[1]);
}

header* InputReader::readHeader(){
    header* h=new header();
    std::string line;
    std::getline(file,line);
    if(line!="#SCHOOL ELF HEADER:")return nullptr;
    std::getline(file,line);
    h->sectionsNum=readNum();
    h->symbolsNum=readNum();
    h->relocsNum=readNum();
    return h;
    
}

std::vector<SectionsData> InputReader::readSections(int cntSec){
    std::vector<SectionsData> sections;
    std::string line;
    std::getline(file,line);
    std::getline(file,line);
    if(line!="#SECTIONS"){
        //exception
        return sections;
    }
    std::getline(file,line);
    for(int i=0;i<cntSec;i++){
        SectionsData data;
        int number;
        std::getline(file,line);
        file>>number>>data.name>>std::hex>>data.value>>std::hex>>data.size>>data.global;
        sections.push_back(data);
    }
    std::getline(file,line);
    return sections;

}

std::vector<SymbolsData> InputReader::readSymbols(int cntSym){
    std::vector<SymbolsData> symbols;
    std::string line;
    std::getline(file,line);
    std::getline(file,line);
    if(line!="#SYMBOL TABLE"){
        //exception
        return symbols;
    }
    std::getline(file,line);
    for(int i=0;i<cntSym;i++){
        SymbolsData data;
        int number;
        std::getline(file,line);
        file>>number>>data.name>>std::hex>>data.value>>data.section>>data.global;
        symbols.push_back(data);
    }
    std::getline(file,line);
    return symbols;
}

std::vector<RelocationRecord> InputReader::readRelocations(int cntRel){
    std::vector<RelocationRecord> relocations;
    std::string line;
    std::getline(file,line);
    std::getline(file,line);
    if(line!="#RELOCATION TABLE"){
        //exception
        return relocations;
    }
    std::getline(file,line);
    for(int i=0;i<cntRel;i++){
        RelocationRecord data;
        std::string type;
        std::getline(file,line);
        file>>std::hex>>data.offset>>data.section>>type>>data.name;
        if(type=="R_386_16")data.type=RelocationType::R_386_16;
        else data.type=RelocationType::R_386_PC16;
        relocations.push_back(data);
    }
    std::getline(file,line);
    return relocations;
}


std::map<std::string,char*> InputReader::readSectionsContent(std::vector<SectionsData>*secinfo){
    std::map<std::string,char*> map;
    std::string line;
    
    for(int i=0;i<secinfo->size();i++){
        std::getline(file,line);
        std::getline(file,line);
        std::regex reg("#Content of the section ([a-zA-Z][a-zA-Z_0-9]*)");
        std::smatch sm;
        if(!std::regex_match(line,sm, reg)){
            //exception 
            return map;
        }
        std::string sec=sm[1];
        std::getline(file,line);
        int size;
        for(SectionsData d:*secinfo){
            if(d.name==sec){
                size=d.size;
            }
        }
        char*content=new char[size];
        int finished=0;
        std::string addr;
        while(finished<size){
            file>>addr;
            int i;
            for(i=0;(i<16)&&(i+finished<size);i++){
                int num;
                file>>std::hex>>num;
                content[i+finished]=((char*)(&num))[0];
            }
            finished+=i;
            
        }
        map.insert({sec,content});
        std::getline(file,line);
    }

    return map;

        
}