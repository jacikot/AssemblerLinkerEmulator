# include "../h/outputgenerator.h"
# include "../h/assembler.h"
# include "../h/symboltable.h"
# include "../h/relocationtable.h"
# include <iomanip>
# include <iostream>
# include <printf.h>



void OutputGenerator::openFile(std::string name){
    if(!open)file.open(name);
    open=true;
}

void OutputGenerator::closeFile(){
    if(open)file.close();
    open=false;
}

void OutputGenerator::printHeader(header h){
    if(!open)return;
    h.shsize=sizeof(sectiondata);
    file<<"#SCHOOL ELF HEADER:\n"<<std::endl;;
    file<<" Number of sections:         "<<h.sectioncnt<<std::endl;
    file<<" Number of symbols:          "<<h.symbolcnt<<std::endl;
    file<<" Number of relocations:      "<<h.relcnt<<std::endl;
}


void OutputGenerator::printSections(SymbolTable*symbols){
    std::vector<SymbolsData>sections=symbols->getAllSections();
    file<<std::endl<<"#SECTIONS"<<std::endl<<std::endl;
    int i=0;
    file.setf(std::ios::left);
    file<<" ";
    file.width(MAXLEN);
    file<<"number";
    file.width(MAXLEN);
    file<<"name";
    file.width(MAXLEN);
    file<<"value";
    file.width(MAXLEN);
    file<<"size";
    file.width(MAXLEN);
    file<<"local/global"<<std::endl;
    for(SymbolsData sym:sections){
        file<<" ";
        file.width(MAXLEN);
        file<<(++i);
        file.width(MAXLEN);
        file<<sym.name;
        file.width(MAXLEN);
        file<<std::hex<<sym.value;
        file.width(MAXLEN);
        file<<sym.size;
        file.width(MAXLEN);
        file<<((sym.global)?"G":"L")<<std::endl;
    }
}

void OutputGenerator::printSymbols(SymbolTable*symbols){
    std::vector<SymbolsData>sections=symbols->getAllSymbols();
    file<<std::endl<<"#SYMBOL TABLE"<<std::endl<<std::endl;
    int i=0;
    file.setf(std::ios::left);
    file<<" ";
    file.width(MAXLEN);
    file<<"number";
    file.width(MAXLEN);
    file<<"name";
    file.width(MAXLEN);
    file<<"value";
    file.width(MAXLEN);
    file<<"section";
    file.width(MAXLEN);
    file<<"local/global"<<std::endl;
    for(SymbolsData sym:sections){
        file<<" ";
        file.width(MAXLEN);
        file<<(++i);
        file.width(MAXLEN);
        file<<sym.name;
        file.width(MAXLEN);
        file<<std::hex<<sym.value;
        file.width(MAXLEN);
        file<<sym.section;
        file.width(MAXLEN);
        file<<((sym.global)?"G":"L")<<std::endl;
    }
}


void OutputGenerator::printRelocs(RelocationTable*rels){
    std::vector<RelocationRecord> relocations=rels->getAllRecords();
    file<<std::endl<<"#RELOCATION TABLE"<<std::endl<<std::endl;
    file<<" ";
    file.width(MAXLEN);
    file<<"offset";
    file.width(MAXLEN);
    file<<"section";
    file.width(MAXLEN);
    file<<"type";
    file.width(MAXLEN);
    file<<"symbol"<<std::endl;
    for(RelocationRecord rec:relocations){
        file<<" ";
        file.width(MAXLEN);
        file<<std::hex<<rec.offset;
        file.width(MAXLEN);
        file<<rec.section;
        file.width(MAXLEN);
        file<<((rec.type==RelocationType::R_386_16)?"R_386_16":"R_386_PC16");
        file.width(MAXLEN);
        file<<rec.name<<std::endl;
    }
}

void OutputGenerator::printSectionContent(SectionMapper*sections,SymbolTable*symbols){
    std::vector<SymbolsData>sects=symbols->getAllSections();
    for(SymbolsData sec:sects){
        file.setf(std::ios::right);
        file<<std::endl<<"#Content of the section "<<sec.name<<std::endl<<std::endl;
        char*content=sections->getSectionContent(sec.name);
        int finished=0;
        while(finished<sec.size){
            file.width(4);
            file<<std::hex<<finished;
            file<<":";
            int i=0;
            for(;(i<16)&&((i+finished)<sec.size);i++){
                file<<" ";
                int num=(int)*(unsigned char*)(content+i+finished);
                if(num<16)file<<'0';
                file<<std::hex<<num;
            }
            finished+=i;
            file<<std::endl;
        }
    }
}