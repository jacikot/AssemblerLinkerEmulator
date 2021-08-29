# include "../h/linker.h"
# include "../h/inputreader.h"
# include "../h/exceptions.h"

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
            sectionMap.insertSection(data,fileCnt);
        }
        std::vector<SymbolsData> symbols=reader.readSymbols(h->symbolsNum, fileCnt);
        for(SymbolsData& d:symbols){
            symbolsMap.insertSymbol(d);
        }
        std::vector<RelocationRecord> relocs=reader.readRelocations(h->relocsNum,fileCnt);
        for(RelocationRecord& r:relocs){
            relocations.push_back(r);
        }
        
        std::map<std::string,char*> content=reader.readSectionsContent(&sections);
        std::for_each(content.begin(),content.end(),[=](std::pair<std::string,char*>p){
            sectionMap.setContent(p.first,fileCnt,p.second);
        });
        reader.closeFile();
        fileCnt++;
    }
}

bool Linker::resolveSectionOffsets(){
    return sectionMap.resolveSectionOffsets(hex,secAddr);
}


bool Linker::checkUndefined(){
    if(linkable) return false;
    return symbolsMap.checkUndefined();
}

void Linker::resolveSymbolValues(){
    symbolsMap.resolveSymbols(sectionMap);
}

void Linker::resolveRelocs(){
    if(hex){
        for(RelocationRecord&r:relocations){
            int value;
            if(symbolsMap.exist(r.name)){
                value=symbolsMap.getValue(r.name);
            }
            else{
                value=sectionMap.getValue(r.name,r.file);
            }
            short*addr=(short*)sectionMap.getContent(r.section,r.file,r.offset);
            if(r.type==RelocationType::R_386_16){
                *addr+=value; //testiraj ovo
            }
            else{
                *addr+=value-r.offset-sectionMap.getValue(r.section,r.file);
            }
            short x=*addr;
        }
    }
    else{
        for(RelocationRecord&r:relocations){
            if(sectionMap.exist(r.name)){ //if it is section (local symbol)
                short*addr=(short*)sectionMap.getContent(r.section,r.file,r.offset);
                *addr+=sectionMap.getValue(r.name,r.file);
            }
            r.offset+=sectionMap.getValue(r.section,r.file);
        }
    }
}

int Linker::generateOutput(){
    if(writer.open(outputFile)<0)return -1;
    if(hex) writer.writeHex(this);
    else writer.writeLinkable(this);
    if(writer.close()<0)return -1;
    return 0;
}

header* Linker::getHeader(){
    header* h=new header();
    h->sectionsNum=sectionMap.size();
    h->symbolsNum=symbolsMap.size();
    h->relocsNum=relocations.size();
    return h;
}


int Linker::link(){
    if(!hex && !linkable || hex && linkable)return -1;
    readFiles();
    checkUndefined();
    resolveSectionOffsets();
    resolveSymbolValues();
    resolveRelocs();
    if(generateOutput()<0){
        throw LinkerException("Exception in output generation!");
    }
}