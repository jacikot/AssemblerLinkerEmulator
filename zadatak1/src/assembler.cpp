# include "../inc/assembler.h"
# include "../inc/tokens.h"
# include "../inc/exceptions.h"

# include <iostream>

void Assembler::addToCounter(int size){
    if(curSection==""){
         throw AssemblerException("line"+std::to_string(line)+": Section not defined!");
    }
    counter+=size;
    symbolTable.setSectionSize(curSection,counter);
}

void Assembler::addLine(tokens::Line line){
    lines.push_back(line);
}

void Assembler::addSymbol(std::string name){
    symbolTable.addSymbol(name,curSection,counter);
}

void Assembler::addSection(std::string name){
    symbolTable.addSection(name);
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
    line=0;
    for(tokens::Line& l:lines){
        line++;
        int i=l.exp->secondPass(this);
        if(i!=0)return i;
    }
    finished=true;
    return 0;
}

void Assembler::setGlobalSymbol(std::string name){
    symbolTable.setGlobalSymbol(name);
}

void Assembler::setNewSection(std::string name){
    counter=0;
    curSection=name;
    int size = symbolTable.getSectionSize(name);
    if(size == -1){
        throw AssemblerException("line"+std::to_string(line)+": Section "+curSection+" not defined!");
    }
    sections.newSectionContent(name,size);
}

void Assembler::skip(int size){
    if(curSection==""){
         throw AssemblerException("line"+std::to_string(line)+": Section not defined!");
         return;
    }
    sections.skip(curSection,size,counter);
    counter+=size;
}

void Assembler::initLiteral(int value){
    if(curSection==""){
         throw AssemblerException("line"+std::to_string(line)+": Section not defined!");
         return;
    }
    sections.init2(curSection,value,counter);
    counter+=2;   
}

void Assembler::initSymbol(std::string name){
    if(curSection==""){
         throw AssemblerException("line"+std::to_string(line)+": Section not defined!");
         return;
    }
    if(!symbolTable.exists(name)){
        throw AssemblerException("line"+std::to_string(line)+": Symbol "+name+" not declared!");
        return;
    }
    int offset=symbolTable.getValue(name);
    std::string section=symbolTable.getSection(name);

    if(symbolTable.isGlobal(name)&&(section!="ABS")){
        sections.skip(curSection,2,counter); //init 0
        relocations.addRecord(counter,RelocationType::R_386_16,name,curSection); //add record for symbol
    }
    else{
        sections.init2(curSection,offset,counter); //init with offset
        if(section!="ABS") relocations.addRecord(counter,RelocationType::R_386_16,section,curSection); //add record for section
    }
    counter+=2;
}

void Assembler::initInstr0(int opcode){
    if(curSection==""){
         throw AssemblerException("line"+std::to_string(line)+": Section not defined!");
         return;
    }
    sections.init1(curSection,opcode,counter);
    counter++;
}


int Assembler::getRegNo(std::string reg){
    if(reg=="r0")return 0b0000;
    if(reg=="r1")return 0b0001;
    if(reg=="r2")return 0b0010;
    if(reg=="r3")return 0b0011;
    if(reg=="r4")return 0b0100;
    if(reg=="r5")return 0b0101;
    if(reg=="r6")return 0b0110;
    if(reg=="r7")return 0b0111;
    if(reg=="sp")return 0b0110;
    if(reg=="pc")return 0b0111;
    if(reg=="psw")return 0b1000;
    if(reg=="UND")return 0b1111;
    return -1; 
}

void Assembler::initOperand(tokens::Operand op, std::string dst, int addend){
    switch (op.adr)
    {
    case tokens::Addressing::IMMED: 
        sections.init1(curSection,getRegNo("UND")|(getRegNo(dst)<<4),counter); //2. B
        sections.init1(curSection,tokens::Addressing::IMMED,counter+1); //3. B
        counter+=2;
        if(op.ini.symbol){
            initSymbol(op.ini.name); //4. i 5. B
        }
        else{
            initLiteral(op.ini.value); //4. i 5. B
        }
        break;
    case tokens::Addressing::REGDIR: 
        sections.init1(curSection,getRegNo(op.reg)|(getRegNo(dst)<<4),counter); //2. B
        sections.init1(curSection,tokens::Addressing::REGDIR,counter+1); //3. B
        counter+=2;
        break;
    case tokens::Addressing::REGIND:
        sections.init1(curSection,getRegNo(op.reg)|(getRegNo(dst)<<4),counter); //2. B
        sections.init1(curSection,tokens::Addressing::REGIND|(addend<<4),counter+1); //3. B, addend is +-2 for push and pop, else 0
        counter+=2;
        break;
    case tokens::Addressing::REGINDPOM:
        sections.init1(curSection,getRegNo(op.reg)|(getRegNo(dst)<<4),counter); //2. B
        sections.init1(curSection,tokens::Addressing::REGINDPOM,counter+1); //3. B
        counter+=2;
        if(op.isPCREL){
            initPcRel(op.ini.name);
        }
        else{
            if(op.ini.symbol){
                initSymbol(op.ini.name); //4. i 5. B
            }
            else{
                initLiteral(op.ini.value); //4. i 5. B
            }
        }
        
        break;
    case tokens::Addressing::MEMDIR: 
        sections.init1(curSection,getRegNo("UND")|(getRegNo(dst)<<4),counter); //2. B
        sections.init1(curSection,tokens::Addressing::MEMDIR,counter+1); //3. B
        counter+=2;
        if(op.ini.symbol){
            initSymbol(op.ini.name); //4. i 5. B
        }
        else{
            initLiteral(op.ini.value); //4. i 5. B
        }
        break;
    case tokens::Addressing::REGDIRPOM: 
        sections.init1(curSection,getRegNo(op.reg)|(getRegNo(dst)<<4),counter); //2.B
        sections.init1(curSection,tokens::Addressing::REGDIRPOM,counter+1); //3. B
        counter+=2;
        initPcRel(op.ini.name);
        break;

    }
}

void Assembler::initPcRel(std::string name){
    if(curSection==""){
         throw AssemblerException("line"+std::to_string(line)+": Section not defined!");
         return;
    }
    int offset=symbolTable.getValue(name);
    std::string section=symbolTable.getSection(name);
    if(symbolTable.isGlobal(name)&&(section!="ABS")){
        sections.init2(curSection,-2,counter);
        relocations.addRecord(counter,RelocationType::R_386_PC16,name,curSection); //add record for symbol
    }
    else{
        if((curSection==section)||section=="ABS"){
            sections.init2(curSection,offset-counter-2,counter); //no record
        }
        else{
            sections.init2(curSection,offset-2,counter);
            relocations.addRecord(counter,RelocationType::R_386_PC16,section,curSection); //add record for section
        }
    }
    counter+=2;
}


void Assembler::initInstr2REGREG(int opcode, std::string dst, std::string src){
    if(curSection==""){
         throw AssemblerException("line"+std::to_string(line)+": Section not defined!");
         return;
    }
    initInstr0(opcode);//1. B
    sections.init1(curSection,(getRegNo(dst)<<4)|getRegNo(src),counter);
    counter++;

}

void Assembler::initInstr2REGOP(int opcode,std::string reg,tokens::Operand op){
    if(curSection==""){
         throw AssemblerException("line"+std::to_string(line)+": Section not defined!");
         return;
    }
    initInstr0(opcode);//1. B
    initOperand(op,reg,op.addend);
}

int Assembler::output(std::string filename){
    generator.openFile(filename);
    header h=getHeaderData();
    generator.printHeader(h);
    generator.printSections(&symbolTable);
    generator.printSymbols(&symbolTable);
    generator.printRelocs(&relocations);
    generator.printSectionContent(&sections,&symbolTable);
    generator.closeFile();
    return 0;
}

header Assembler::getHeaderData(){
    header h;
    h.symbolcnt=symbolTable.getNumOfGlobalSymbols();
    h.sectioncnt=symbolTable.getNumOfSections();
    h.relcnt=relocations.getRecordCount();
    return h;
}