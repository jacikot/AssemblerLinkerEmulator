#include "../h/assembler.h"
#include "../h/tokens.h"

void Assembler::addLine(tokens::Line line){
    lines.push_back(line);
}

void Assembler::addSymbol(std::string name){
    symbolTable.addSymbol(name,curSection,counter);
}

void Assembler::addSection(std::string name){
    symbolTable.addSection(name);
    if(curSection!="")symbolTable.setSectionSize(curSection,counter);
    counter=0;
    curSection=name;
}

void Assembler::addAbsoluteSymbol(std::string name, int value){
    symbolTable.addAbsoluteSymbol(name,value);
}

void Assembler::addUndefinedSymbol(std::string name){
    symbolTable.addUndefinedSymbol(name);
}

int Assembler::secondPass(){
    for(tokens::Line l:lines){
        int i=l.exp->secondPass(this);
        if(i!=0)return i;
    }
    return 0;
}

void Assembler::setGlobalSymbol(std::string name){
    symbolTable.setGlobalSymbol(name);
}