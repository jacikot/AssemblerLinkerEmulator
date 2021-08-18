# include "../h/symboltable.h"
# include <vector>
void SymbolTable::addSymbol(std::string name, std::string section, int value){
    if(table->find(name)!=table->end()){
        //handluje exception
        return;
    }
    SymbolsData* smb=new SymbolsData();
    smb->name=name;
    smb->section=section;
    smb->value=value;
    smb->global=false;
    smb->isSection=false;
    table->insert({name,smb});
    std::vector<int> x;
    
}

void SymbolTable::addSection(std::string name){
    if(table->find(name)!=table->end()){
        //handluje exception
        return;
    }
    SymbolsData* smb=new SymbolsData();
    smb->name=name;
    smb->section=name;
    smb->value=0;
    smb->global=false;
    smb->isSection=true;
    table->insert({name,smb});
}

void SymbolTable::setSectionSize(std::string name, int value){
    table->find(name)->second->size=value;
}

void SymbolTable::addAbsoluteSymbol(std::string name, int value){
    if(table->find(name)!=table->end()){
        //handluje exception
        return;
    }
    SymbolsData* smb=new SymbolsData();
    smb->name=name;
    smb->section="ABS";
    smb->value=value;
    smb->global=false;
    smb->isSection=false;
    table->insert({name,smb});
}

void SymbolTable::addUndefinedSymbol(std::string name){
    if(table->find(name)!=table->end()){
        //handluje exception
        return;
    }
    SymbolsData* smb=new SymbolsData();
    smb->name=name;
    smb->section="UND";
    smb->global=true;
    smb->isSection=false;
    table->insert({name,smb});
}

void SymbolTable::setGlobalSymbol(std::string name){
    if(table->find(name)==table->end()){
        //handluje exception
        return;
    }
    table->find(name)->second->global=true;

}

int SymbolTable::getSectionSize(std::string name){
    if(table->find(name)==table->end()||!table->find(name)->second->isSection){
        //handluje exception
        return -1;
    }
    return table->find(name)->second->size;
}

int SymbolTable::getValue(std::string name){
    if(table->find(name)==table->end()){
        //handluje exception
        return -1;
    }
    return table->find(name)->second->value;
}

bool SymbolTable::isGlobal(std::string name){
    if(table->find(name)==table->end()){
        //hendluj exception
        return false;
    }
    return table->find(name)->second->global;
}

std::string SymbolTable::getSection(std::string name){
    if(table->find(name)==table->end()){
        //hendluj exception
        return false;
    }
    return table->find(name)->second->section;
}