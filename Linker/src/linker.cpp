# include "../h/linker.h"
# include "../h/inputreader.h"

# include <vector>
# include <map>
# include <algorithm>
# include <iostream>


int Linker::readFiles(){
    int fileCnt=0;
    for(std::string filename:files){
        reader.openFile(filename);
        header*h=reader.readHeader();
        std::vector<SectionsData> sections=reader.readSections(h->sectionsNum);
        for(SectionsData data:sections){
            if(sectionMap.find(data.name)==sectionMap.end()){
                std::map<int,SectionsData> map;
                sectionMap.insert({data.name, new std::map<int,SectionsData*>()});
            }
            sectionMap.find(data.name)->second->insert({fileCnt,new SectionsData(data)});
        }
        std::vector<SymbolsData> symbols=reader.readSymbols(h->symbolsNum, fileCnt);
        for(SymbolsData& d:symbols){
            if(d.section!="UND"&&symbolsMap.find(d.name)!=symbolsMap.end()){
                //exception duplicate name
                return -2;
            }
            if(d.section!="UND")symbolsMap.insert({d.name,new SymbolsData(d)});
            else undefined.push_back(d);
        }
        std::vector<RelocationRecord> relocs=reader.readRelocations(h->relocsNum,fileCnt);
        for(RelocationRecord& r:relocs){
            relocations.push_back(r);
        }
        
        std::map<std::string,char*> content=reader.readSectionsContent(&sections);
        std::for_each(content.begin(),content.end(),[=](std::pair<std::string,char*>p){
            sectionMap.find(p.first)->second->find(fileCnt)->second->content=p.second;
        });
        reader.closeFile();
        fileCnt++;
    }
}

void Linker::resolveSectionOffsets(){
    int start=0;
    std::for_each(sectionMap.begin(),sectionMap.end(),[=, &start](std::pair<std::string,std::map<int,SectionsData*>*>p){//foreach section name
        int addr; //starting address
        if(hex && secAddr.find(p.first)!=secAddr.end()){
            addr=secAddr.find(p.first)->second;
        }
        else addr=start;
        std::for_each(p.second->begin(),p.second->end(),[&addr](std::pair<int,SectionsData*>d){
            d.second->value=addr;
            addr+=d.second->size;
        });
        if(hex)start=addr;
    });
}

Linker::~Linker(){
    std::for_each(sectionMap.begin(),sectionMap.end(),[](std::pair<std::string,std::map<int,SectionsData*>*>p){
        std::for_each(p.second->begin(),p.second->end(),[](std::pair<int,SectionsData*>d){
           delete d.second; 
        });
        delete p.second;
    });
    std::for_each(symbolsMap.begin(),symbolsMap.end(),[](std::pair<std::string,SymbolsData*>d){
        delete d.second; 
    });
}


bool Linker::checkUndefined(){
    if(linkable) return false;
    for(SymbolsData& s:undefined){
        if(symbolsMap.find(s.name)==symbolsMap.end()){
            return true;
        }
    }
    return false;
}

void Linker::resolveSymbolValues(){
    std::for_each(symbolsMap.begin(),symbolsMap.end(),[=](std::pair<std::string,SymbolsData*>d){
        if(d.second->section!="ABS"){
            d.second->value+=sectionMap.find(d.second->section)->second->find(d.second->file)->second->value;
        }
    });
}

void Linker::resolveRelocs(){
    if(hex){
        for(RelocationRecord&r:relocations){
            int value;
            if(symbolsMap.find(r.name)!=symbolsMap.end()){
                value=symbolsMap.find(r.name)->second->value;
            }
            else{
                value=sectionMap.find(r.name)->second->find(r.file)->second->value;
            }
            short*addr=(short*)(sectionMap.find(r.section)->second->find(r.file)->second->content+r.offset);
            if(r.type==RelocationType::R_386_16){
                *addr+=value; //testiraj ovo
            }
            else{
                *addr+=value-r.offset;
            }
            short x=*addr;
        }
    }
}