# include "../inc/symbolstable.h"
# include <algorithm>
# include "../inc/sectiontable.h"
# include "../inc/exceptions.h"

int SymbolTable::insertSymbol(SymbolsData&d){
    if(d.section!="UND"&&exist(d.name)){
        throw LinkerException("Double definition of symbol "+d.name+" found!");
    }
    if(d.section!="UND"){
        symbolsMap.insert({d.name,new SymbolsData(d)});
    }
    else undefined.push_back(d);
    return 0;
}


bool SymbolTable::exist(std::string name){
    return symbolsMap.find(name)!=symbolsMap.end();
}

SymbolTable::~SymbolTable(){
    std::for_each(symbolsMap.begin(),symbolsMap.end(),[](std::pair<std::string,SymbolsData*>d){
        delete d.second; 
    });
}

bool SymbolTable::checkUndefined(){
    for(SymbolsData& s:undefined){
        if(symbolsMap.find(s.name)==symbolsMap.end()){
            throw LinkerException("Undefined symbol "+s.name+" found!");
        }
    }
    return false;
}

void SymbolTable::resolveSymbols(SectionTable& sectionMap){
    std::for_each(symbolsMap.begin(),symbolsMap.end(),[=, &sectionMap](std::pair<std::string,SymbolsData*>d){
        if(d.second->section!="ABS"){
            d.second->value+=sectionMap.getValue(d.second->section,d.second->file);
        }
    });
}

int SymbolTable::getValue(std::string name){
    return symbolsMap.find(name)->second->value;
}

std::vector<SymbolsData> SymbolTable::getAllSymbols(){
    std::vector<SymbolsData> data;
    std::for_each(symbolsMap.begin(),symbolsMap.end(),[&data](std::pair<std::string,SymbolsData*>d){
        data.push_back(*(d.second));
    });
    return data;
}