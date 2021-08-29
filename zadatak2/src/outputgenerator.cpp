# include "../inc/outputgenerator.h"
# include "../inc/linker.h"
# include "../inc/sectiontable.h"
# include "../inc/symbolstable.h"
# include <algorithm>
# include <iomanip>

int OutputGenerator::open(std::string name){
    if(opened) return -1;
    file.open(name);
    opened=true;
    return 0;
}
int OutputGenerator::close(){
    if(!opened)return -1;
    file.close();
    opened=false;
    return 0;
}

void OutputGenerator::printAddress(int addr){
    if(addr<0x1000) file<<'0';
    if(addr<0x100) file<<'0';
    if(addr<0x10) file <<'0';
    file<<std::hex<<addr;
    file<<":";
}

void OutputGenerator::writeHex(Linker*linker){
    std::vector<SectionsData>sects=linker->getSectionTable().getLinkerData();
    for(SectionsData& sec:sects){
        file.setf(std::ios::right);
        char*content=sec.content;
        int finished=0;
        while(finished<sec.size){
            printAddress(finished+sec.value);
            int i=0;
            for(;(i<8)&&((i+finished)<sec.size);i++){
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
void OutputGenerator::writeLinkable(Linker*linker){
    header*h=linker->getHeader();
    writeHeader(h);
    printSections(linker->getSectionTable());
    printSymbols(linker->getSymbolTable());
    printRelocs(linker->getRelTable());
    printSectionContent(linker->getSectionTable());
}

void OutputGenerator::writeHeader(header*h){
    file<<"#SCHOOL ELF HEADER:\n"<<std::endl;;
    file<<" Number of sections:         "<<h->sectionsNum<<std::endl;
    file<<" Number of symbols:          "<<h->symbolsNum<<std::endl;
    file<<" Number of relocations:      "<<h->relocsNum<<std::endl;
}

void OutputGenerator::printSections(SectionTable& sectionMap){
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
    std::vector<SectionsData> data=sectionMap.getLinkerData();
    std::for_each(data.begin(),data.end(),[=, &i](SectionsData& d){
        file<<" ";
        file.width(MAXLEN);
        file<<(++i);
        file.width(MAXLEN);
        file<<d.name;
        file.width(MAXLEN);
        file<<std::hex<<d.value;
        file.width(MAXLEN);
        file<<d.size;
        file.width(MAXLEN);
        file<<((d.global)?"G":"L")<<std::endl;
    });
    
}


void OutputGenerator::printSymbols(SymbolTable&symbols){
    std::vector<SymbolsData>sections=symbols.getAllSymbols();
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


void OutputGenerator::printRelocs(std::vector<RelocationRecord>&relocations){
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


void OutputGenerator::printSectionContent(SectionTable&sections){
    std::vector<SectionsData>sects=sections.getLinkerData();
    for(SectionsData& sec:sects){
        file.setf(std::ios::right);
        file<<std::endl<<"#Content of the section "<<sec.name<<std::endl<<std::endl;
        char*content=sec.content;
        int finished=0;
        while(finished<sec.size){
            printAddress(finished);
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